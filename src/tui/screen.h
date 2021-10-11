#pragma once

#include "terminal_writer.h"

class Screen {
public:
    Screen() {};
    void render();
private:
    TerminalWriter m_terminal_writer;
    void enter_raw_mode();
};
