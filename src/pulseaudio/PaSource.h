#include <stdio.h>
#include <pulse/simple.h>
#include <pulse/error.h>

struct buffer_frame {
    int16_t l;
    int16_t r;
};

class PaSource {
public:
    PaSource();

    void read(buffer_frame *buffer, const size_t buffer_bytes);

    ~PaSource();
private:
    pa_simple* m_pa_simple;
};
