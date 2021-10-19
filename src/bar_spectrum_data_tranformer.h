#pragma once

#include <vector>
#include <memory>

#include "source/pa_source.h"
#include "settings.h"

class BarSpectrumDataTransformer {
public:
    BarSpectrumDataTransformer(std::shared_ptr<SpectrumSettings> settings);
    std::vector<double> transform(buffer_frame* buffer, size_t buffers_size);

    ~BarSpectrumDataTransformer();
private:
    uint32_t m_bars_amount;
    std::shared_ptr<SpectrumSettings> m_settings;
    unsigned int m_counter;
    uint32_t m_fftw_results;

    std::vector<uint32_t> m_fading_bars;
    std::vector<double> m_smoothing_weights;
    std::vector<uint32_t>* m_low_cutoff_frequencies;
    std::vector<uint32_t>* m_high_cutoff_frequencies;

    void apply_smoothing(std::vector<uint32_t>* bars);
    void apply_fading_smoothing(std::vector<uint32_t>* bars);
    std::vector<double> set_bar_cols_heights(std::vector<uint32_t>* bars);

    void calculate_cutoff_frequencies();
};
