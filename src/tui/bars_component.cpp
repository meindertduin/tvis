#include <math.h>

#include "bars_component.h"
#include "../constants.h"
#include "../bar_spectrum_data_tranformer.h"

BarsComponent::BarsComponent(ComponentData component_data) : Component(component_data) {
    m_source = new PaSource();
}

BarsComponent::~BarsComponent() {
    delete m_source;
}

void BarsComponent::render() {
    auto bars_amount = m_component_data.width / 4;

    BarSpectrumDataTransformer transformer{bars_amount};
    buffer_frame buffer[Constants::k_sample_size];

    auto bars = transformer.transform(buffer, sizeof(buffer));
    auto max = 8000;

    char output_buffer[10][bars_amount + 1];
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < bars_amount + 1; j++) {
            output_buffer[i][j] = ' ';
        }
    }

    auto x = output_buffer[1];

    int i = 0;
    for (auto &bar : bars) {
        if (bar > max) {
            bar = max;
        }

        auto bar_height = std::floor((static_cast<double>(bar) / static_cast<double>(max))
                * 10.0);
        int inverted_height = 10 - bar_height;
        for (auto j = 10; j > inverted_height; j--) {
            output_buffer[j][i] = 'x';
        }
        i++;
    }

    for (int i = 0; i < 10; i++) {
        output_buffer[i][bars_amount] = '\n';
    }

    for(int i = 0; i < 10; i++) {
        for (int j = 0; j < bars_amount + 1; j++) {
            printf("%c", output_buffer[i][j]);
        }
    }
}
