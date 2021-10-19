#include <cstdint>
#include <stdio.h>

#pragma once

struct buffer_frame {
    int16_t l;
    int16_t r;
};

class Source {
    virtual void read(buffer_frame *buffer, const size_t buffer_bytes) = 0;
};
