#pragma once

#include "terminal_writer.h"
#include "bars_component.h"

struct ScreenData {
    int width, height;
};

class Screen {
public:
    Screen();
    ~Screen();
    void render();
private:
    TerminalWriter m_terminal_writer;
    BarsComponent m_bars_component;
    ScreenData m_screen_data;

    bool set_window_size();
};
