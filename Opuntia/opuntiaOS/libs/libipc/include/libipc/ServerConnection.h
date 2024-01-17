/*
 * Copyright (C) 2020-2022 The opuntiaOS Project Authors.
 *  + Contributed by Nikita Melekhin <nimelehin@gmail.com>
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#pragma once
#include <cstdlib>
#include <libfoundation/Logger.h>
#include <libipc/DoubleSidedConnection.h>
#include <libipc/Message.h>
#include <libipc/MessageDecoder.h>
#include <vector>

template <typename ServerDecoder, typename ClientDecoder>
class ServerConnection {
public:
    ServerConnection(const LIPC::DoubleSidedConnection& connection, ServerDecoder& server_decoder, ClientDecoder& client_decoder)
        : m_connection(connection)
        , m_server_decoder(server_decoder)
        , m_client_decoder(client_decoder)
    {
    }

    bool send_message(const Message& msg) const
    {
        auto encoded_msg = msg.encode();
        int wrote = write(m_connection.s2c_fd(), encoded_msg.data(), encoded_msg.size());
        return wrote == encoded_msg.size();
    }

    void pump_messages()
    {
        std::vector<char> buf;

        char tmpbuf[1024];

        int read_cnt;
        while ((read_cnt = read(m_connection.c2s_fd(), tmpbuf, sizeof(tmpbuf)))) {
            if (read_cnt <= 0) {
                Logger::debug << getpid() << " :: ServerConnection read error" << std::endl;
                return;
            }
            size_t buf_size = buf.size();
            buf.resize(buf_size + read_cnt);
            memcpy(&buf.data()[buf_size], tmpbuf, read_cnt);
            if (read_cnt < sizeof(tmpbuf)) {
                break;
            }
        }

        size_t msg_len = 0;
        size_t buf_size = buf.size();
        for (int i = 0; i < buf_size; i += msg_len) {
            msg_len = 0;
            if (auto response = m_server_decoder.decode((buf.data() + i), read_cnt - i, msg_len)) {
                if (auto answer = m_server_decoder.handle(*response)) {
                    send_message(*answer);
                }
            } else if (auto response = m_client_decoder.decode((buf.data() + i), read_cnt - i, msg_len)) {

            } else {
                std::abort();
            }
        }
    }

private:
    LIPC::DoubleSidedConnection m_connection;
    ServerDecoder& m_server_decoder;
    ClientDecoder& m_client_decoder;
};