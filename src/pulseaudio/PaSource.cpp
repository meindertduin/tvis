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

void PaSource::read() {

    uint8_t buf[1024];
    int error;
    size_t buf_size = sizeof(buf);

   if (pa_simple_read(m_pa_simple, buf,buf_size, &error) < 0) {
        printf("error while reading bytes: %s \n", pa_strerror(error));
    }

    auto file = fopen("test.txt", "wb");

    fwrite(buf, 1, sizeof(buf), file);
    fclose(file);
}
