#include <stdint.h>

namespace Constants {
static const uint32_t k_fps = 10;
static const uint32_t k_sampling_frequency = 44100;
static const double k_high_cutoff = 22050;
static const double k_low_cutoff = 30;
static const uint32_t k_sample_size = k_sampling_frequency / k_fps;
static const uint32_t k_fftw_results = (k_sampling_frequency / 2) + 1;
static const double k_smoothing_factor = 1.30;
};
