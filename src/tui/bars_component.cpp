#include <math.h>

#include "bars_component.h"

BarsComponent::BarsComponent() : Component(), m_transformer{30} {}

BarsComponent::BarsComponent(ComponentData component_data) : Component(component_data), m_transformer{30} {}

BarsComponent::~BarsComponent() {}

ComponentCharactersBuffer* BarsComponent::create_component_text_buffer() {
    auto bars_amount = 45;
    auto col_height = 20;
    auto bars_width = 2;
    auto total_width = bars_width * bars_amount;
    auto max = 16000;

    buffer_frame buffer[Constants::k_sample_size];
    m_source.read(buffer, sizeof(buffer));

    auto bars = m_transformer.transform(buffer, sizeof(buffer));

    char output_buffer[col_height][total_width];
    Character characters[col_height][total_width];
    for (int i = 0; i < col_height; i++) {
        for (int j = 0; j < total_width; j++) {
            characters[i][j] = { ' ', AnsiColor::None };
        }
    }

    int i = 0;
    for (auto &bar : bars) {
        if (bar > max) {
            bar = max;
        }

        auto bar_height = std::round((static_cast<double>(bar) / static_cast<double>(max))
                * static_cast<double>(col_height));
        int inverted_height = col_height - bar_height;

        for (auto j = col_height; j > inverted_height; j--) {
            for (auto k = 0u; k < bars_width; k++) {
                characters[j][i + k] = { ' ', AnsiColor::BGRed };
            }
        }

        i += bars_width;
    }

    for (auto i = 0u; i < col_height; i++) {
        m_component_character_buffer->set_row(i, characters[i], total_width);
    }

    return m_component_character_buffer;
}

AnsiColor BarsComponent::get_bar_section_color(int height) {
    if (height < 6) return AnsiColor::FGBlue;
    if (height < 12) return AnsiColor::FGYellow;

    return AnsiColor::FGRed;
}
