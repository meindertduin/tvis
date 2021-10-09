#include <iostream>
#include "pulseaudio/PaSource.h"
#include <fftw3.h>

const uint32_t k_fps = 10;
const uint32_t sampling_frequency = 44100;
const uint32_t sample_size = 10;

int main() {
    auto frames_count = sampling_frequency / k_fps;
    uint32_t fftw_results = (sampling_frequency / 2) + 1;

    PaSource pa_source;

    for (;;) {
        for (auto i = 0u; i < k_fps; i++) {
            buffer_frame buffer[frames_count];
            pa_source.read(buffer, sizeof(buffer));


            double left[frames_count];
            for (int j = 0; j < frames_count; j++) {
                left[j] = buffer[j].l;
            }

            fftw_complex* output = static_cast<fftw_complex *>(fftw_malloc(sizeof(fftw_complex) * fftw_results));

            fftw_plan plan = fftw_plan_dft_r2c_1d(frames_count, left, output, FFTW_ESTIMATE);
            fftw_execute(plan);

            for (auto x : *output) {
                printf("%f\n", **output);
            }
        }
    }
}

