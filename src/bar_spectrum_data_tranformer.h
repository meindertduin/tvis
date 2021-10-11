#pragma once

#include "source/pa_source.h"
#include <vector>

class BarSpectrumDataTransformer {
public:
    BarSpectrumDataTransformer(int bars_amount);
    std::vector<uint32_t> transform(buffer_frame* buffer, size_t buffers_size);

    ~BarSpectrumDataTransformer();
private:
    int m_bars_amount;
    std::vector<uint32_t>* m_low_cutoff_frequencies;
    std::vector<uint32_t>* m_high_cutoff_frequencies;

    void calculate_cutoff_frequencies();
};
