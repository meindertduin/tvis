#include <iostream>
#include "pulseaudio/PaSource.h"
#include <math.h>
#include <vector>

const uint32_t k_fps = 10;
const uint32_t sampling_frequency = 44100;
const uint32_t bars = 40;
const uint32_t sample_size = 70;

double get_max(std::vector<double> filtered_data);

int main() {
    auto frames_count = sampling_frequency / k_fps;

    PaSource pa_source;

    for (;;) {
        for (auto i = 0u; i < k_fps; i++) {
            buffer_frame buffer[frames_count];
            pa_source.read(buffer, sizeof(buffer));

            auto block_size = std::floor(frames_count / sample_size);

            std::vector<double> l_values;
            std::vector<double> r_values;

            for (auto j = 0u; j < sample_size; j++) {
                auto block_start = block_size * j;
                int64_t sum_l = 0;
                int64_t sum_r = 0;
                for (auto k = 0u; k < block_size; k++) {
                    uint32_t block_index = block_start + k;
                    sum_r += std::abs(buffer[block_index].r);
                    sum_l += std::abs(buffer[block_index].l);
                }

                auto r_filtered = sum_r / block_size;
                auto l_filtered = sum_l / block_size;

                printf("%f\n", l_filtered);
            }
        }
    }
}

double get_max(std::vector<double> filtered_data) {
    double max = 0;
    for (auto value : filtered_data) {
        if (value > max)
            max = value;
    }

    return max;
}


