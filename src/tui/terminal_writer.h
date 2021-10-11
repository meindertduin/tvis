#pragma once
#include <termios.h>
#include <unistd.h>
#include <stdlib.h>

class TerminalWriter {
public:
    TerminalWriter();
    void write();
    ~TerminalWriter();
private:
    static void disable_raw_mode();
    static void enter_raw_mode();
};

