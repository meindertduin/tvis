#include <iostream>
#include "BarSpectrumDataTransformer.h"
#include "Constants.h"

int main() {
    PaSource pa_source;
    BarSpectrumDataTransformer transformer;

    for (;;) {
        for (auto i = 0u; i < 10; i++) {
            buffer_frame buffer[Constants::sampling_frequency];
            pa_source.read(buffer, sizeof(buffer));

            transformer.transform(buffer, sizeof(buffer));
        }
    }
}

