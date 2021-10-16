#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <iostream>
#include <csignal>

#include "terminal_writer.h"

struct termios sm_original_state;

TerminalWriter::TerminalWriter() {
    enter_raw_mode();
}

void TerminalWriter::write_to_console(string value){
    printf("%s", value.c_str());
}

void TerminalWriter::enter_raw_mode() {
    tcgetattr(STDIN_FILENO, &sm_original_state);

    signal(SIGINT, disable_raw_mode);
    signal(SIGABRT, disable_raw_mode);
    signal(SIGTERM, disable_raw_mode);
    signal(SIGSEGV, disable_raw_mode);

    // hide the cursor
    printf("\x1b[?25l");

    auto raw = sm_original_state;
    raw.c_lflag &= ~(ECHO);
    raw.c_cflag |= (CS8);
    raw.c_cc[VMIN] = 0;
    raw.c_cc[VTIME] = 1;

    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}

void TerminalWriter::disable_raw_mode(int param) {
    // re-enable the cursor
    printf("\x1b[?25h");

    tcsetattr(STDIN_FILENO, TCSAFLUSH, &sm_original_state);
    exit(param);
}

void TerminalWriter::clear_screen() {
    write(STDOUT_FILENO, "\x1b[2J", 4);
    write(STDOUT_FILENO, "\x1b[H", 3);
}

TerminalWriter::~TerminalWriter() {
}
