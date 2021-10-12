#pragma once
#include <termios.h>
#include <string>

using std::string;

class TerminalWriter {
public:
    TerminalWriter();
    void write_to_buffer();
    void write_to_console();
    ~TerminalWriter();
private:
    static void disable_raw_mode();
    static void enter_raw_mode();
    void clear_screen();
};

