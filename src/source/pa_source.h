#include <stdio.h>
#include <pulse/simple.h>
#include <pulse/error.h>

#pragma once

#include "source.h"

class PaSource : Source {
public:
    PaSource();

    void read(buffer_frame *buffer, const size_t buffer_bytes);

    ~PaSource();
private:
    pa_simple* m_pa_simple;
};
