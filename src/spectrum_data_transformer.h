#include "source/pa_source.h"

#pragma once

class SpectrumDataTransformer {
public:
    SpectrumDataTransformer() {};
    virtual void transform(buffer_frame* buffer, size_t buffers_size) = 0;
};
