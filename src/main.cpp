#include <iostream>
#include "pulseaudio/PaSource.h"

const uint32_t k_fps = 10;
const uint32_t sampling_frequency = 441000;
const uint32_t bars = 10;

int main() {
    auto frame_size = sampling_frequency / k_fps;

    PaSource pa_source;

    for (auto i = 0u; i < k_fps; i++) {
        buffer_frame buffer[frame_size];
        pa_source.read(buffer);

        auto skip = frame_size / bars;

        for (auto j = 0u; j < bars; j++) {
            u_int32_t index = skip * j;
            printf("%d", buffer[index].l);
        }
        printf("\n");
    }
}

