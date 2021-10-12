#include "component_characters_buffer.h"
#include <stdexcept>

ComponentCharactersBuffer::ComponentCharactersBuffer(int cols, int rows) : m_cols(cols), m_rows(rows) {
    m_characters = (Character**) malloc(rows * sizeof(Character));
    for (int i = 0; i < rows; i++) {
        m_characters[i] = (Character*) malloc((cols) * sizeof(Character));
        for (int j = 0; j < cols; j++) {
            m_characters[i][j] = { ' ', AnsiColor::FGWhite };
        }
    }
}

ComponentCharactersBuffer::~ComponentCharactersBuffer() {
    for (int i = 0u; i < m_rows; i++) {
        free(m_characters[i]);
    }

    free(m_characters);
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

    Character* previous_character = nullptr;

    value += "\x1b[" + std::to_string(31) + "m";

    for (auto i = 0u; i < m_rows; i++) {
        auto row_ptr = m_characters[i];

        for (auto j = 0u; j < m_cols; j++) {
            auto character = m_characters[i][j];

            if (previous_character != nullptr && previous_character->color != character.color) {
                // reset the coloring
                value += "\x1b[0m";

                value += "\x1b[" + std::to_string(character.color) + "m";
            }

            value += character.character;

            previous_character = &character;
        }

        value += "\n";
    }

    value += "\x1b[0m";

    return value;
}
