#include <iostream>
#include "pulseaudio/PaSource.h"
#include <fftw3.h>
#include <math.h>
#include <vector>

const uint32_t k_fps = 10;
const uint32_t sampling_frequency = 44100;
const double k_high_cutoff = 22050;
const double k_low_cutoff = 30;
const uint32_t k_number_bars = 50;

int main() {
    auto frames_count = sampling_frequency / k_fps;
    uint32_t fftw_results = (sampling_frequency / 2) + 1;

    PaSource pa_source;

    auto freq_const =
        std::log10(
            static_cast<double>(k_low_cutoff) /
            static_cast<double>(k_high_cutoff)) /
        ((1.0 / (static_cast<double>(k_number_bars) + 1.0)) - 1.0);


    auto low_cutoff_frequencies = std::vector<uint32_t>(k_number_bars + 1);
    auto high_cutoff_frequencies = std::vector<uint32_t>(k_number_bars + 1);
    auto freqconst_per_bin = std::vector<double>(k_number_bars + 1);

    for (auto i = 0u; i <= k_number_bars; ++i)
    {
        freqconst_per_bin[i] = static_cast<double>(k_high_cutoff) *
            std::pow(10.0, (freq_const * -1) + (((i + 1.0) / (static_cast<double>(k_number_bars) + 1.0)) * freq_const));

        auto frequency = freqconst_per_bin[i] / (static_cast<double>(sampling_frequency) / 2.0);
        low_cutoff_frequencies[i] = static_cast<uint32_t>(std::floor(frequency * (static_cast<double>(frames_count) / 4.0)));
        printf("%d\n", low_cutoff_frequencies[i]);


        if (i > 0)
        {
            if (low_cutoff_frequencies[i] <= low_cutoff_frequencies[i - 1])
            {
                low_cutoff_frequencies[i] = low_cutoff_frequencies[i - 1] + 1;
            }
            high_cutoff_frequencies[i - 1] = low_cutoff_frequencies[i - 1];
        }
    }

    for (int i = 0u; i <= k_number_bars; i++) {
        auto low = low_cutoff_frequencies[i];
        auto high = high_cutoff_frequencies[i];
        auto freq = freqconst_per_bin[i];

        printf("%d %d %f \n", low, high, freq);
    }

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

            for (auto k = 0u; k < k_number_bars; k++) {
                double freq_magnitude = 0.0;
                 for (auto cutoff_freq = low_cutoff_frequencies[k]; cutoff_freq <= high_cutoff_frequencies[k]
                         && cutoff_freq < fftw_results; cutoff_freq++)
                 {
                    freq_magnitude += std::sqrt((output[cutoff_freq][0] * output[cutoff_freq][0]) + (output[cutoff_freq][1] * output[cutoff_freq][1]));
                 }
                 auto mag = freq_magnitude / (high_cutoff_frequencies[i] - low_cutoff_frequencies[i] + 1);
                 mag *= (std::log2(2 + i) * (100.0 / k_number_bars));
                 mag = std::pow(mag, 0.5);

                 printf("%ld : ", static_cast<uint64_t>(mag));
            }

            printf("\n");
        }
    }
}

