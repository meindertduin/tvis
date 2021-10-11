#pragma once

#include "terminal_writer.h"
#include "bars_component.h"

class Screen {
public:
    Screen() {
        m_bars_component = new BarsComponent{{0, 0, 0, 0}};
    };
    ~Screen();
    void render();
private:
    TerminalWriter m_terminal_writer;
    BarsComponent* m_bars_component;
};
