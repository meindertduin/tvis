#pragma once

#include "spectrum_data_transformer.h"
#include "source/pa_source.h"
#include <vector>


class BarSpectrumDataTransformer : SpectrumDataTransformer {
public:
    BarSpectrumDataTransformer();
    void transform(buffer_frame* buffer, size_t buffers_size);

    ~BarSpectrumDataTransformer();
private:
    std::vector<uint32_t>* m_low_cutoff_frequencies;
    std::vector<uint32_t>* m_high_cutoff_frequencies;

    void calculate_cutoff_frequencies();
};
