#pragma once

#include "terminal_writer.h"
#include "bars_component.h"

struct WindowData {
    int width, height;
};

class Screen {
public:
    Screen();
    ~Screen();
    void render();
private:
    TerminalWriter m_terminal_writer;
    BarsComponent* m_bars_component;
    WindowData m_window_data;

    bool set_window_size();
};
