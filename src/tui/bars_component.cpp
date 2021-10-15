#include <math.h>

#include "bars_component.h"

BarsComponent::BarsComponent(ComponentData component_data) : Component(component_data) {
    set_spectrum_settings(&component_data);
    m_transformer = std::unique_ptr<BarSpectrumDataTransformer>(new BarSpectrumDataTransformer(m_settings));
    m_col_height = component_data.height;
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
    auto max = 4000;

    buffer_frame buffer[Constants::k_sample_size];
    m_source.read(buffer, sizeof(buffer));

    auto bars = m_transformer.get()->transform(buffer, sizeof(buffer));

    char output_buffer[m_col_height][total_width];
    Character characters[m_col_height][total_width];
    for (int i = 0; i < m_col_height; i++) {
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
                * static_cast<double>(m_col_height));
        int inverted_height = m_col_height - bar_height;

        for (auto j = m_col_height; j > inverted_height; j--) {
            for (auto k = 0u; k < m_bars_width; k++) {
                characters[j][i + k] = { '*', AnsiColor::FGRed };
            }
        }

        i += m_bars_width;
    }

    for (auto i = 0u; i < m_col_height; i++) {
        m_component_character_buffer->set_row(i, characters[i], total_width);
    }

    return m_component_character_buffer;
}


void BarsComponent::set_spectrum_settings(const ComponentData *component_data) {
    auto bars_amount = std::floor(component_data->width / Constants::k_bars_width);
    m_settings = std::shared_ptr<SpectrumSettings>(new SpectrumSettings {
        static_cast<uint32_t>(bars_amount),
        Constants::k_sampling_frequency,
        Constants::k_low_cutoff,
        Constants::k_high_cutoff,
        Constants::k_sample_size,
        Constants::k_smoothing_factor + ((std::log10(bars_amount) - 1) * 0.5),
        Constants::k_decrease_bars_counter
    });
}
