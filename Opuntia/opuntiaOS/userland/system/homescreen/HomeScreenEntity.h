#pragma once
#include <libg/PixelBitmap.h>

class HomeScreenEntity {
public:
    HomeScreenEntity() = default;

    HomeScreenEntity(int window_id)
        : m_window_id(window_id)
    {
    }

    bool operator==(const HomeScreenEntity& other) const { return m_window_id == other.m_window_id; }
    bool operator!=(const HomeScreenEntity& other) const { return m_window_id != other.m_window_id; }

    int window_id() const { return m_window_id; }
    void set_icon(LG::PixelBitmap&& icon) { m_icon = std::move(icon); }
    const LG::PixelBitmap& icon() const { return m_icon; }

private:
    int m_window_id { 0 };
    LG::PixelBitmap m_icon;
    int m_window_status { 0 };
};