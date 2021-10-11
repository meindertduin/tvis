#pragma once
#include <termios.h>

class TerminalWriter {
public:
    TerminalWriter();
    void write_to_console();
    ~TerminalWriter();
private:
    static void disable_raw_mode();
    static void enter_raw_mode();
};

