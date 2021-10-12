#pragma once

#include <string>
#include <vector>

using std::string;
using std::vector;

enum AnsiColor {
    FGBlack = 30,
    FGRed = 31,
    FGGreen = 32,
    FGYellow = 33,
    FGBlue = 34,
    FGMagenta = 35,
    FGCyan = 36,
    FGWhite = 37,
    FGBrightBlack = 90,
    FGBrightRed = 91,
    FGBrightGreen = 92,
    FGBrightYellow = 93,
    FGBrightBlue = 94,
    FGBrightMagenta = 95,
    FGBrightCyan = 96,
    FGBrightWhite = 97,

    BGBlack = 40,
    BGRed = 41,
    BGGreen = 42,
    BGYellow = 43,
    BGBlue = 44,
    BGMagenta = 45,
    BGCyan = 46,
    BGWhite = 47,
    BGBrightBlack = 100,
    BGBrightRed = 101,
    BGBrightGreen = 102,
    BGBrightYellow = 103,
    BGBrightBlue = 104,
    BGBrightMagenta = 105,
    BGBrightCyan = 106,
    BGBrightWhite = 107,
};

struct Character {
    char character;
    AnsiColor color;
};

class ComponentCharactersBuffer {
public:
    ComponentCharactersBuffer(int cols, int rows) : m_cols(cols), m_rows(rows) {
        for (int i = 0; i < rows; i++) {
            Character* row_ptr = (Character*) malloc((cols) * sizeof(Character));
            for (int j = 0; j < cols; j++) {
                row_ptr[j] = { ' ', AnsiColor::FGWhite };
            }
        }
    };

    ~ComponentCharactersBuffer() {
        for (auto character_row : m_character_rows) {
            free(character_row);
        }
    }
private:
    int m_cols, m_rows;
    vector<Character*> m_character_rows;
};
