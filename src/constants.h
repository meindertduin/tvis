#include <stdint.h>

namespace Constants {
static const uint32_t k_fps = 30;
static const uint32_t k_bars_width = 2;
static const uint32_t k_sampling_frequency = 44100;
static const double k_high_cutoff = 22050;
static const double k_low_cutoff = 30;
static const uint32_t k_sample_size = k_sampling_frequency / k_fps;
static const double k_smoothing_factor = 1.25;
static const unsigned int k_decrease_bars_counter = k_fps / 5;
};
