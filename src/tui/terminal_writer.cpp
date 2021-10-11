#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <iostream>

#include "terminal_writer.h"

struct termios sm_original_state;

TerminalWriter::TerminalWriter() {
    enter_raw_mode();
}

void TerminalWriter::write_to_console(){
    clear_screen();
}

void TerminalWriter::enter_raw_mode() {
    tcgetattr(STDIN_FILENO, &sm_original_state);
    atexit(disable_raw_mode);

    auto raw = sm_original_state;
    raw.c_iflag &= ~(ICRNL | IXON | ISTRIP);
    raw.c_lflag &= ~(ECHO | ICANON | IEXTEN);
    raw.c_cflag |= (CS8);
    raw.c_cc[VMIN] = 0;
    raw.c_cc[VTIME] = 1;

    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}

void TerminalWriter::disable_raw_mode() {
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &sm_original_state);
}

void TerminalWriter::clear_screen() {
    write(STDOUT_FILENO, "\x1b[2J", 4);
    write(STDOUT_FILENO, "\x1b[H", 3);
    //write(STDOUT_FILENO, "\x1b[7m", 4);
    //write(STDOUT_FILENO, "\x1b[31m", 5);
    //printf("xxxx\n");
    //printf("xxxx\n");
    //write(STDOUT_FILENO, "\x1b[93m", 5);
    //printf("xxxx\n");
    //printf("xxxxxxxx\n");
    //write(STDOUT_FILENO, "\x1b[94m", 5);
    //printf("xxxxxxxx\n");
    //printf("xxxxxxxx\n");
    //write(STDOUT_FILENO, "\x1b[0m", 4);
}

TerminalWriter::~TerminalWriter() {
    disable_raw_mode();
}
