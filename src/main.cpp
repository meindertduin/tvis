#include <iostream>
#include <chrono>
#include <thread>


#include "tui/screen.h"

#include "bar_spectrum_data_tranformer.h"
#include "constants.h"

int main() {
    //Screen screen;

    BarsComponent bars;
    for (;;) {
        BarSpectrumDataTransformer transformer{10};
        buffer_frame buffer[Constants::k_sample_size];

        transformer.transform(buffer, sizeof(buffer));
    }
}

