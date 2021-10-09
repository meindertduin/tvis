#include <iostream>
#include "BarSpectrumDataTransformer.h"

int main() {
    PaSource pa_source;
    BarSpectrumDataTransformer transformer;

    for (;;) {
        for (auto i = 0u; i < 10; i++) {
            buffer_frame buffer[4410];
            pa_source.read(buffer, sizeof(buffer));

            transformer.transform(buffer, sizeof(buffer));
        }
    }
}

