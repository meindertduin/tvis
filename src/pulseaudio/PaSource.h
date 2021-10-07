#include <stdio.h>
#include <pulse/simple.h>
#include <pulse/error.h>

struct buffer_frame {
    int16_t l;
};

class PaSource {
public:
    PaSource();

    void read();

    ~PaSource();
private:
    pa_simple* m_pa_simple;
};
