/*
 * Copyright (C) 2020-2022 The opuntiaOS Project Authors.
 *  + Contributed by Nikita Melekhin <nimelehin@gmail.com>
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#pragma once
#include "ServerDecoder.h"
#include <libapi/window_server/Connections/WSConnection.h>
#include <libfoundation/EventReceiver.h>
#include <libipc/DoubleSidedConnection.h>
#include <libipc/ServerConnection.h>

namespace WinServer {

class Connection : public LFoundation::EventReceiver {
public:
    inline static Connection& the()
    {
        extern Connection* s_WinServer_Connection_the;
        return *s_WinServer_Connection_the;
    }

    Connection();

    inline void listen()
    {
        m_connection_with_clients.pump_messages();
    }

    inline bool send_async_message(const Message& msg) const { return m_connection_with_clients.send_message(msg); }
    inline int alloc_connection() { return ++m_connections_number; }
    void receive_event(std::unique_ptr<LFoundation::Event> event) override;

private:
    LIPC::DoubleSidedConnection m_connection;
    int m_connections_number { 0 };
    ServerConnection<WindowServerDecoder, BaseWindowClientDecoder> m_connection_with_clients;
    WindowServerDecoder m_server_decoder;
    BaseWindowClientDecoder m_client_decoder;
};

} // namespace WinServer