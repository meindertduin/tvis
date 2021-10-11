#include <iostream>

#include "bar_spectrum_data_tranformer.h"
#include "source/pa_source.h"
#include "constants.h"
#include "tui/screen.h"

int main() {
    PaSource pa_source;
    BarSpectrumDataTransformer transformer;
    Screen screen;

    screen.render();

    while(true) {

    }

    //
    //for (;;) {
    //    for (auto i = 0u; i < 10; i++) {
    //        buffer_frame buffer[Constants::k_sample_size];
    //        pa_source.read(buffer, sizeof(buffer));

    //        transformer.transform(buffer, sizeof(buffer));
    //    }
    //}
}

