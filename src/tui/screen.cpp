#include "screen.h"

Screen::~Screen() {
    delete m_bars_component;
}

void Screen::render() {
    m_bars_component->render();
    // m_terminal_writer.write_to_console();
}

