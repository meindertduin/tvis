#include <iostream>
#include <chrono>
#include <thread>


#include "tui/screen.h"

int main() {
    Screen screen;
    for (;;) {
        screen.render();
        if (!screen.is_active()) {
            std::this_thread::sleep_for(std::chrono::milliseconds(300));
        }
    }
}

