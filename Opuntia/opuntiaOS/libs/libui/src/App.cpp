/*
 * Copyright (C) 2020-2022 The opuntiaOS Project Authors.
 *  + Contributed by Nikita Melekhin <nimelehin@gmail.com>
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#include <libipc/DoubleSidedConnection.h>
#include <libui/App.h>
#include <memory>
#include <sys/socket.h>

namespace UI {

App* s_UI_App_the = nullptr;

App::App()
    : m_event_loop()
    , m_server_connection(LIPC::DoubleSidedConnection(socket(PF_LOCAL, 0, 0), socket(PF_LOCAL, 0, 0)))
{
    s_UI_App_the = this;
}

void App::receive_event(std::unique_ptr<LFoundation::Event> event)
{
    switch (event->type()) {
    case Event::Type::WindowCloseRequestEvent: {
        // TODO: Only 1 window is supported for now
        WindowCloseRequestEvent& own_event = *(WindowCloseRequestEvent*)event.get();
        auto message = DestroyWindowMessage(m_server_connection.key(), own_event.window_id());
        auto reply = m_server_connection.send_sync_message<DestroyWindowMessageReply>(message);
        m_event_loop.stop(reply->status());
        break;
    }
    }
}

} // namespace UI