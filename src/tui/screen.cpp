#include <sys/ioctl.h>
#include <termios.h>
#include <unistd.h>
#include <ctype.h>

#include "screen.h"

Screen::Screen() {
    m_bars_component = new BarsComponent{{0, 0, 0, 0}};
    if (!set_window_size()) {
        // TODO handle error
    }
}

Screen::~Screen() {
    delete m_bars_component;
}

void Screen::render() {
    //m_bars_component->render();
    //m_terminal_writer.write_to_console();
}

bool Screen::set_window_size() {
    struct winsize ws;
    if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws) == -1) {
        return false;
    };

    m_window_data.width = ws.ws_col;
    m_window_data.height = ws.ws_row;

    return true;
}

