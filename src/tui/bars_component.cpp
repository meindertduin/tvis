#include <math.h>

#include "bars_component.h"
#include "../constants.h"
#include "../bar_spectrum_data_tranformer.h"

BarsComponent::BarsComponent() : Component() {}

BarsComponent::BarsComponent(ComponentData component_data) : Component(component_data) {}


BarsComponent::~BarsComponent() {
}

void BarsComponent::render() {
    auto bars_amount = 40;

    BarSpectrumDataTransformer transformer{bars_amount};
    buffer_frame buffer[Constants::k_sample_size];
    m_source.read(buffer, sizeof(buffer));

    auto bars = transformer.transform(buffer, sizeof(buffer));
    auto max = 8000;

    char output_buffer[10][bars_amount + 2];
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < bars_amount + 2; j++) {
            output_buffer[i][j] = ' ';
        }
    }

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
        output_buffer[i][bars_amount -1] = '\n';
        output_buffer[i][bars_amount] = '\0';
    }

    for (int i = 0; i < 10; i++) {
        printf("%s", output_buffer[i]);
    }
}
