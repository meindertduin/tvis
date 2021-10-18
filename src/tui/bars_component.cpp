#include <math.h>

#include "bars_component.h"

BarsComponent::BarsComponent(ComponentData component_data) : Component(component_data) {
    m_col_height = component_data.height;
    set_spectrum_settings(&component_data);
    m_transformer = std::unique_ptr<BarSpectrumDataTransformer>(new BarSpectrumDataTransformer(m_settings));
    m_bars_width = 2;


    m_on_resize = [this](const ComponentData *new_component_data) {
        set_spectrum_settings(new_component_data);
        m_transformer.reset(new BarSpectrumDataTransformer(m_settings));
    };
}

BarsComponent::~BarsComponent() {
}

ComponentCharactersBuffer* BarsComponent::create_component_text_buffer() {
    auto total_width = Constants::k_bars_width * m_settings->bars_amount;

    buffer_frame buffer[Constants::k_sample_size];
    m_source.read(buffer, sizeof(buffer));

    auto bars = m_transformer.get()->transform(buffer, sizeof(buffer));

    char output_buffer[m_col_height][total_width];
    Character characters[m_col_height][total_width];
    for (int i = 0; i < m_col_height; i++) {
        for (int j = 0; j < total_width; j++) {
            characters[i][j] = { " ", AnsiColor::None };
        }
    }

    int i = 0;
    for (auto &bar : bars) {
        auto first_decimal = static_cast<int>(bar * 10.0) % 10;

        int extra_height = 0;
        if (first_decimal > 2) {
            extra_height = 1;
        }

        int inverted_height = m_col_height - std::floor(bar) - extra_height;

        // add characters from the bottom to the top of the bar
        for (auto j = m_col_height; j > inverted_height; j--) {
            for (auto k = 0u; k < m_bars_width; k++) {
                characters[j][i + k] = { "X", AnsiColor::FGBrightYellow };
            }
        }

        i += m_bars_width;
    }

    for (auto i = 0u; i < m_col_height; i++) {
        m_component_character_buffer->set_row(i, characters[i], total_width);
    }

    return m_component_character_buffer.get();
}


void BarsComponent::set_spectrum_settings(const ComponentData *component_data) {
    auto bars_amount = std::floor(component_data->width / Constants::k_bars_width);

    // set the max lower when there are more bars, since the maginitude is higher per bar, when there are less bars
    auto max = 20000 / std::pow(std::log10(bars_amount), 2);

    m_settings = std::shared_ptr<SpectrumSettings>(new SpectrumSettings {
        static_cast<uint32_t>(bars_amount),
        m_col_height,
        Constants::k_sampling_frequency,
        Constants::k_low_cutoff,
        Constants::k_high_cutoff,
        Constants::k_sample_size,
        Constants::k_smoothing_factor,
        Constants::k_decrease_bars_counter,
        static_cast<uint32_t>(std::floor(max))
    });
}
