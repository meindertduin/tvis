#include <sys/ioctl.h>
#include <termios.h>
#include <unistd.h>
#include <ctype.h>

#include "screen.h"

Screen::Screen() {
    if (!set_window_size()) {
        // TODO handle error
    }

    m_bars_component = std::unique_ptr<BarsComponent>(new BarsComponent({90, 20, 0, 0}));
}

Screen::~Screen() {}

void Screen::render() {
    auto component_buffer = m_bars_component->create_component_text_buffer();
    m_terminal_writer.clear_screen();
    m_terminal_writer.write_to_console(component_buffer->get_string());
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

