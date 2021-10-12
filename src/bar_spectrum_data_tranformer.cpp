/*
 * Much of this code has been taken from the cli-visualizer project.
 * https://github.com/dpayne/cli-visualizer/blob/master/src/Transformer/SpectrumTransformer.cpp
 *
 * In the future i hope to provide my own DFT and bar generation code, but wanted to first make a working demo
*/


#include "bar_spectrum_data_tranformer.h"
#include <math.h>
#include <fftw3.h>
#include "constants.h"

BarSpectrumDataTransformer::BarSpectrumDataTransformer(int bars_amount)
    : m_bars_amount(bars_amount) {
    calculate_cutoff_frequencies();
}

std::vector<uint32_t> BarSpectrumDataTransformer::transform(buffer_frame* buffer, size_t buffers_size) {
    std::vector<uint> bars;

    double left[Constants::k_sample_size];
    for (int j = 0; j < Constants::k_sample_size; j++) {
        left[j] = buffer[j].l;
    }

    fftw_complex* output = static_cast<fftw_complex *>(fftw_malloc(sizeof(fftw_complex) * Constants::k_fftw_results));

    fftw_plan plan = fftw_plan_dft_r2c_1d(Constants::k_sample_size, left, output, FFTW_ESTIMATE);
    fftw_execute(plan);

    for (auto k = 0u; k < m_bars_amount; k++) {
        double freq_magnitude = 0.0;
        for (auto cutoff_freq = (*m_low_cutoff_frequencies)[k]; cutoff_freq <= (*m_high_cutoff_frequencies)[k]
                && cutoff_freq < Constants::k_fftw_results; cutoff_freq++)
        {
           freq_magnitude += std::sqrt((output[cutoff_freq][0] * output[cutoff_freq][0]) +
                   (output[cutoff_freq][1] * output[cutoff_freq][1]));
        }
        auto mag = freq_magnitude / ((*m_high_cutoff_frequencies)[k] - (*m_low_cutoff_frequencies)[k] + 1);
        mag *= (std::log2(2 + k) * (100.0 / m_bars_amount));
        mag = std::pow(mag, 0.5);

        bars.push_back(static_cast<uint32_t>(mag));
    }

    fftw_free(output);
    return bars;
}

void BarSpectrumDataTransformer::calculate_cutoff_frequencies() {
    auto freq_const_per_bin = std::vector<double>(m_bars_amount + 1);
    m_low_cutoff_frequencies = new std::vector<uint32_t>(m_bars_amount + 1);
    m_high_cutoff_frequencies = new std::vector<uint32_t>(m_bars_amount + 1);

    auto freq_const =std::log10(static_cast<double>(m_bars_amount) / static_cast<double>(Constants::k_high_cutoff)) /
        ((1.0 / (static_cast<double>(m_bars_amount) + 1.0)) - 1.0);

    for (auto i = 0u; i <= m_bars_amount; ++i) {
        freq_const_per_bin[i] = static_cast<double>(Constants::k_high_cutoff) *
            std::pow(10.0, (freq_const * -1) + (((i + 1.0) / (static_cast<double>(m_bars_amount) + 1.0)) * freq_const));

        auto frequency = freq_const_per_bin[i] / (static_cast<double>(Constants::k_sampling_frequency) / 2.0);
        (*m_low_cutoff_frequencies)[i] = static_cast<uint32_t>(std::floor(frequency *
                    (static_cast<double>(Constants::k_sample_size) / 4.0)));

        if (i > 0)
        {
            if ((*m_low_cutoff_frequencies)[i] <= (*m_low_cutoff_frequencies)[i - 1])
            {
                (*m_low_cutoff_frequencies)[i] = (*m_low_cutoff_frequencies)[i - 1] + 1;
            }
            (*m_high_cutoff_frequencies)[i - 1] = (*m_low_cutoff_frequencies)[i - 1];
        }
    }
}

BarSpectrumDataTransformer::~BarSpectrumDataTransformer() {
    delete m_low_cutoff_frequencies;
    delete m_high_cutoff_frequencies;
}
