#include "screen.h"

void Screen::render() {
    m_terminal_writer.write_to_console();
}

