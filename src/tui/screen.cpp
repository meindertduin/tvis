#include <sys/ioctl.h>
#include <termios.h>
#include <unistd.h>
#include <ctype.h>

#include "screen.h"

Screen::Screen() {
    m_screen_data.width = 0;
    m_screen_data.height = 0;
    m_window_size_set = false;

    set_window_size();

    m_bars_component = std::unique_ptr<BarsComponent>(new BarsComponent({m_screen_data.width, 20, 0, 0}));
}

Screen::~Screen() {}

void Screen::render() {
    // poll for window size each render, to make sure the window hasn't resized
    set_window_size();

    auto component_buffer = m_bars_component->create_component_text_buffer();
    m_terminal_writer.clear_screen();
    m_terminal_writer.write_to_console(component_buffer->get_string());
}

bool Screen::set_window_size() {
    struct winsize ws;
    if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws) == -1) {
        return false;
    };

    if (m_screen_data.height != ws.ws_row || m_screen_data.width != ws.ws_col) {
        if (m_window_size_set) {
            handle_terminal_resize();
        }

        m_screen_data.width = ws.ws_col;
        m_screen_data.height = ws.ws_row;

        m_window_size_set = true;
    }

    return true;
}

void Screen::handle_terminal_resize() {
    m_bars_component->set_component_data({m_screen_data.width, 20, 0, 0});
}
