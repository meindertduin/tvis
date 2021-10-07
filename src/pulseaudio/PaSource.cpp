#include "PaSource.h"


PaSource::PaSource() {
    static const pa_sample_spec ss = {
        .format = PA_SAMPLE_S16LE,
        .rate = 44100,
        .channels = 2,
    };

    m_pa_simple =  pa_simple_new(NULL, "tvis", PA_STREAM_RECORD, NULL, "record", &ss, NULL, NULL, NULL);
}

PaSource::~PaSource() {
    if (m_pa_simple != nullptr) {
        pa_simple_free(m_pa_simple);
    }
}

void PaSource::read(buffer_frame *buffer) {
    size_t buf_size = sizeof(buffer);
    int error;

   if (pa_simple_read(m_pa_simple, buffer, buf_size, &error) < 0) {
        printf("error while reading bytes: %s \n", pa_strerror(error));
    }
}
