/*
 * Copyright (C) 2020-2022 The opuntiaOS Project Authors.
 *  + Contributed by Nikita Melekhin <nimelehin@gmail.com>
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#pragma once

#include "../../Managers/Compositor.h"
#include "../../Managers/CursorManager.h"
#include <functional>
#include <libg/Color.h>
#include <libg/Context.h>
#include <string>
#include <vector>

namespace WinServer {

struct PopupItem {
    int id;
    std::string text;
    std::function<void(int)> callback;

    static const int InternalId = -1;
};
using PopupData = std::vector<PopupItem>;

class Popup {
public:
    inline static Popup& the()
    {
        extern Popup* s_WinServer_Popup_the;
        return *s_WinServer_Popup_the;
    }

    Popup();
    ~Popup() = default;

    constexpr int spacing() const { return 8; }
    constexpr size_t min_width() const { return 180u; }

    void set_preferred_origin(const LG::Point<int>& origin);

    inline LG::Rect& bounds() { return m_bounds; }
    inline const LG::Rect& bounds() const { return m_bounds; }

    inline LG::Rect draw_frame() const
    {
        const int shadow_spread = LG::Shading::SystemSpread;
        return LG::Rect(bounds().min_x() - shadow_spread, bounds().min_y() - shadow_spread, bounds().width() + 2 * shadow_spread, bounds().height() + 2 * shadow_spread);
    }

    inline void set_visible(bool vis)
    {
        if (m_visible != vis) {
            Compositor::the().invalidate(draw_frame());
        }
        m_visible = vis;
    }
    inline bool visible() const { return m_visible; }

    void show(const LG::Point<int>& origin, PopupData& data)
    {
        set_visible(false);
        set_data(data);
        set_preferred_origin(origin);
        set_visible(true);
    }

    void hide()
    {
        m_hovered_item = HoveredItem::No;
        set_visible(false);
    }

    void on_set_data();
    void set_data(const PopupData& data) { m_data = data, on_set_data(); }
    void set_data(PopupData&& data) { m_data = std::move(data), on_set_data(); }

    void on_mouse_move(const CursorManager& cursor_manager)
    {
        // A simple implemetation to get hover effect and clicks.
        if (!visible()) {
            return;
        }

        size_t data_size = m_data.size();
        const size_t line_height = (m_font.size() + 8);
        int prev_hovered_item = m_hovered_item;
        int rel_y = cursor_manager.y() - bounds().min_y();
        rel_y -= 4; // Offset of the first element;
        m_hovered_item = rel_y / line_height;

        if (m_hovered_item >= data_size) {
            m_hovered_item = HoveredItem::No;
        }

        if (m_hovered_item != prev_hovered_item && prev_hovered_item != HoveredItem::No) {
            Compositor::the().invalidate(LG::Rect(bounds().min_x(), bounds().min_y() + 4 + line_height * prev_hovered_item, bounds().width(), line_height));
        }

        if (m_hovered_item != prev_hovered_item && m_hovered_item != HoveredItem::No) {
            Compositor::the().invalidate(LG::Rect(bounds().min_x(), bounds().min_y() + 4 + line_height * m_hovered_item, bounds().width(), line_height));
        }
    }

    inline void on_mouse_status_change(const CursorManager& cursor_manager)
    {
        if (m_hovered_item == HoveredItem::No) {
            return;
        }

        if (!visible()) {
            return;
        }

        auto& data = m_data;
        if (cursor_manager.pressed<CursorManager::Params::LeftButton>()) {
            data[m_hovered_item].callback((int)data[m_hovered_item].id);
            hide();
        }
    }

    void on_mouse_leave(const CursorManager& cursor_manager)
    {
        if (m_hovered_item == HoveredItem::No) {
            return;
        }

        if (!visible()) {
            return;
        }

        const size_t line_height = (m_font.size() + 8);
        Compositor::the().invalidate(LG::Rect(bounds().min_x(), bounds().min_y() + 4 + line_height * m_hovered_item, bounds().width(), line_height));
        m_hovered_item = HoveredItem::No;
    }

    void draw(LG::Context& ctx);

private:
    enum HoveredItem {
        No = -1,
    };

    LG::Rect m_bounds { 0, 0, 0, 0 };
    bool m_visible { false };
    PopupData m_data;
    int m_hovered_item { HoveredItem::No };
    LG::Font& m_font { LG::Font::system_font() };
};

} // namespace WinServer