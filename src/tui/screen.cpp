#include <sys/ioctl.h>
#include <termios.h>
#include <unistd.h>
#include <ctype.h>

#include "screen.h"

Screen::Screen() {
    if (!set_window_size()) {
        // TODO handle error
    }
    m_bars_component.set_component_data({ m_screen_data.width, m_screen_data.height, 0, 0});
}

Screen::~Screen() {

}

void Screen::render() {
    m_terminal_writer.write_to_console();
    m_bars_component.render();
}

bool Screen::set_window_size() {
    struct winsize ws;
    if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws) == -1) {
        return false;
    };

    m_screen_data.width = ws.ws_col;
    m_screen_data.height = ws.ws_row;

    return true;
}

