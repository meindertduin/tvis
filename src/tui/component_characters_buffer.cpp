#include "component_characters_buffer.h"
#include <stdexcept>

ComponentCharactersBuffer::ComponentCharactersBuffer(int cols, int rows) : m_cols(cols), m_rows(rows) {
    m_characters = (Character**) new Character[rows];
    for (int i = 0; i < rows; i++) {
        m_characters[i] = new Character[cols];
        for (int j = 0; j < cols; j++) {
            m_characters[i][j] = { ' ', AnsiColor::FGWhite };
        }
    }
}

ComponentCharactersBuffer::~ComponentCharactersBuffer() {
    for (int i = 0u; i < m_rows; i++) {
        delete m_characters[i];
    }

    delete m_characters;
}

void ComponentCharactersBuffer::set_character(Point point, Character character) {
    if (point.x_pos > m_cols || point.x_pos < 0 || point.y_pos > m_rows || point.y_pos < 0) {
        throw std::range_error("Point values are out of range");
    }

    m_characters[point.x_pos][point.y_pos] = character;
}

void ComponentCharactersBuffer::set_row(int row, Character *characters, const unsigned int len) {
    if (row > m_rows || row < 0) {
        throw std::range_error("Point values are out of range");
    }

    if (m_cols < len) {
        throw std::range_error("characters length is to long to fit in buffer row");
    }

    auto row_ptr = m_characters[row];
    for (auto i = 0u; i < m_cols; i++) {
        if (i >= len) {
            row_ptr[i] = { ' ', AnsiColor::FGWhite };
        } else {
            row_ptr[i] = characters[i];
        }
    }
}

string ComponentCharactersBuffer::get_string() {
    string value;

    AnsiColor previous_color = AnsiColor::FGWhite;

    value += "\x1b[" + std::to_string(m_characters[0][0].color) + "m";

    for (auto i = 0u; i < m_rows; i++) {
        auto row_ptr = m_characters[i];

        for (auto j = 0u; j < m_cols; j++) {
            auto character = m_characters[i][j];

            if (previous_color != character.color) {
                // reset the coloring
                value += "\x1b[0m";
                if (character.color != AnsiColor::None) {
                    value += "\x1b[" + std::to_string(character.color) + "m";
                }
            }

            value += character.character;

            previous_color = character.color;
        }

       value += "\n";
    }

    value += "\x1b[0m";

    // add another new-line to avoid background color flickering
    value += '\n';

    return value;
}
