#pragma once

#include <memory>

#include "terminal_writer.h"
#include "bars_component.h"

struct ScreenData {
    int width, height;
};

class Screen {
public:
    Screen();
    bool is_active();
    ~Screen();
    void render();
private:
    bool m_window_size_set;
    std::unique_ptr<BarsComponent> m_bars_component;
    TerminalWriter m_terminal_writer;
    ScreenData m_screen_data;

    bool set_window_size();
    void handle_terminal_resize();
};
