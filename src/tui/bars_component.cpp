#include <math.h>

#include "bars_component.h"
#include "../constants.h"
#include "../bar_spectrum_data_tranformer.h"

BarsComponent::BarsComponent() : Component() {}

BarsComponent::BarsComponent(ComponentData component_data) : Component(component_data) {}

BarsComponent::~BarsComponent() {}

ComponentCharactersBuffer* BarsComponent::get_component_buffer() {
    auto bars_amount = 40;
    auto bars_height = 20;

    BarSpectrumDataTransformer transformer{bars_amount};
    buffer_frame buffer[Constants::k_sample_size];
    m_source.read(buffer, sizeof(buffer));

    auto bars = transformer.transform(buffer, sizeof(buffer));
    auto max = 8000;

    char output_buffer[bars_height][bars_amount];
    for (int i = 0; i < bars_height; i++) {
        for (int j = 0; j < bars_amount; j++) {
            output_buffer[i][j] = ' ';
        }
    }

    int i = 0;
    for (auto &bar : bars) {
        if (bar > max) {
            bar = max;
        }

        auto bar_height = std::floor((static_cast<double>(bar) / static_cast<double>(max))
                * static_cast<double>(bars_height));
        int inverted_height = bars_height - bar_height;
        for (auto j = bars_height; j > inverted_height; j--) {
            output_buffer[j][i] = 'x';
        }
        i++;
    }

    for (auto i = 0u; i < bars_height; i++) {
        Character characters_row[bars_amount];

        auto row_color = get_bar_section_color(bars_height - i);
        for (auto j = 0u; j < bars_amount; j++) {
            characters_row[j] = { output_buffer[i][j], row_color };
        }

        m_component_character_buffer->set_row(i, characters_row, bars_amount);
    }

    return m_component_character_buffer;
}

AnsiColor BarsComponent::get_bar_section_color(int height) {
    if (height < 3) return AnsiColor::FGBlue;
    if (height < 6) return AnsiColor::FGYellow;

    return AnsiColor::FGRed;
}
