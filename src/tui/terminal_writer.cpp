#include <stdio.h>

#include "terminal_writer.h"
#include <unistd.h>
#include <stdlib.h>
#include <iostream>

struct termios sm_original_state;

TerminalWriter::TerminalWriter() {
    enter_raw_mode();
}

void TerminalWriter::write_to_console(){
    write(STDIN_FILENO, "\x1b[2J", 4);
}

void TerminalWriter::enter_raw_mode() {
    tcgetattr(STDIN_FILENO, &sm_original_state);
    atexit(disable_raw_mode);

    auto raw = sm_original_state;
    raw.c_lflag &= ~(ECHO | ICANON | IEXTEN);

    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}

void TerminalWriter::disable_raw_mode() {
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &sm_original_state);
}

TerminalWriter::~TerminalWriter() {
    disable_raw_mode();
}
