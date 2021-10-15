#pragma once
#include <stdint.h>

struct SpectrumSettings {
    uint32_t bars_amount;
    uint32_t sampling_frequency;
    double low_cutoff_frequency, high_cutoff_frequency;
    uint32_t sample_size;
    double smoothing_factor;
    unsigned int decreate_bars_counter;
    unsigned int max_magnitude;
};

