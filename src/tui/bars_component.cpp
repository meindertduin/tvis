#include <math.h>

#include "bars_component.h"
#include "../constants.h"
#include "../bar_spectrum_data_tranformer.h"

BarsComponent::BarsComponent() : Component() {}

BarsComponent::BarsComponent(ComponentData component_data) : Component(component_data) {}

BarsComponent::~BarsComponent() {}

ComponentCharactersBuffer* BarsComponent::get_component_buffer() {
    auto bars_amount = 30;
    auto col_height = 20;
    auto bars_width = 3;
    auto total_width = bars_width * bars_amount;
    auto max = 8000;

    BarSpectrumDataTransformer transformer{bars_amount};
    buffer_frame buffer[Constants::k_sample_size];
    m_source.read(buffer, sizeof(buffer));

    auto bars = transformer.transform(buffer, sizeof(buffer));

    char output_buffer[col_height][total_width];
    for (int i = 0; i < col_height; i++) {
        for (int j = 0; j < total_width; j++) {
            output_buffer[i][j] = ' ';
        }
    }

    int i = 0;
    for (auto &bar : bars) {
        if (bar > max) {
            bar = max;
        }

        auto bar_height = std::floor((static_cast<double>(bar) / static_cast<double>(max))
                * static_cast<double>(col_height));
        int inverted_height = col_height - bar_height;

        for (auto j = col_height; j > inverted_height; j--) {
            for (auto k = 0u; k < bars_width; k++) {
                output_buffer[j][i + k] = 'x';
            }
        }

        i += bars_width;
    }

    for (auto i = 0u; i < col_height; i++) {
        Character characters_row[total_width];

        auto row_color = get_bar_section_color(col_height - i);
        for (auto j = 0u; j < total_width; j++) {
            characters_row[j] = { output_buffer[i][j], row_color };
        }

        m_component_character_buffer->set_row(i, characters_row, total_width);
    }

    return m_component_character_buffer;
}

AnsiColor BarsComponent::get_bar_section_color(int height) {
    if (height < 6) return AnsiColor::FGBlue;
    if (height < 12) return AnsiColor::FGYellow;

    return AnsiColor::FGRed;
}
