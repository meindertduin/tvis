#include <iostream>
#include <chrono>
#include <thread>


#include "tui/screen.h"

int main() {
    Screen screen;

    while (true) {
        screen.render();
    }
}

