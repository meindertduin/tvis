#pragma once

#include <iostream>
#include <string>

#include "../common/point.h"

using std::string;

enum AnsiColor {
    None = 0,
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
    char character[4];
    AnsiColor color;
};

class ComponentCharactersBuffer {
public:
    ComponentCharactersBuffer(int cols, int rows);
    ~ComponentCharactersBuffer();

    void set_character(Point point, Character character);

    void set_row(int row, Character* characters, const unsigned int len);

    string get_string();
private:
    int m_cols, m_rows;
    Character** m_characters;
};
