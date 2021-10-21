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
            characters[i][j] = { ' ', AnsiColor::None };
        }
    }

    uint32_t i = 0;
    for (auto &bar : bars) {
        CurrentBarData current_bar_data = {
            .bar_index = i / m_bars_width,
            .first_decimal = static_cast<uint32_t>(bar * 10.0) % 10,
            .extra_height = 0,
            .bar_height = 0,
            .width_index = 0,
        };

        current_bar_data.first_decimal = static_cast<uint32_t>(bar * 10.0) % 10;

        if (current_bar_data.first_decimal > 2) {
            current_bar_data.extra_height = 1;
        } else {
            current_bar_data.extra_height = 0;
        }

        int inverted_height = m_col_height - std::floor(bar) - current_bar_data.extra_height;
        current_bar_data.bar_height = static_cast<uint32_t>(std::floor(bar));

        // add characters from the bottom to the top of the bar
        for (auto j = m_col_height; j > inverted_height; j--) {
            for (auto k = 0u; k < m_bars_width; k++) {
                current_bar_data.width_index = k;

                char bar_char;

                // if j == index of top bar_top
                if (j == inverted_height + 1) {
                    if (i > 0 && i < bars.size()) {
                        bar_char = get_bar_top_char(&bars, &current_bar_data);
                    } else {
                        bar_char = get_straight_top_block(current_bar_data.first_decimal);
                    }
                } else {
                    bar_char = get_bar_char_character_piece(BarCharacterPiece::FullBlock);
                }

                characters[j][i + k] = { bar_char, AnsiColor::FGBrightYellow };
            }
        }

        i += m_bars_width;
    }

    for (auto i = 0u; i < m_col_height; i++) {
        m_component_character_buffer->set_row(i, characters[i], total_width);
    }

    return m_component_character_buffer.get();
}

char BarsComponent::get_bar_top_char(vector<double> *bars, const CurrentBarData *current_bar_data) {
    auto left_bar_height = static_cast<uint32_t>((*bars)[current_bar_data->bar_index - 1]);
    auto right_bar_height = static_cast<uint32_t>(std::floor((*bars)[current_bar_data->bar_index + 1]));

    if (left_bar_height > current_bar_data->bar_height && right_bar_height < current_bar_data->bar_height) {
        // right corner
        if (current_bar_data->width_index == m_bars_width - 1) {
            return get_bar_char_character_piece(BarCharacterPiece::CornerRight);
        } else {
            return get_bar_char_character_piece(BarCharacterPiece::FullBlock);
        }
    }

    if (right_bar_height > current_bar_data->bar_height && left_bar_height < current_bar_data->bar_height) {
        if (current_bar_data->width_index == 0) {
            // left corner
            return get_bar_char_character_piece(BarCharacterPiece::CornerLeft);
        }
    }

    return get_straight_top_block(current_bar_data->first_decimal);
}

char BarsComponent::get_straight_top_block(int first_decimal) {
    if (first_decimal < 4) {
        return get_bar_char_character_piece(BarCharacterPiece::QuarterBlock);
    } else if (first_decimal < 7) {
        return get_bar_char_character_piece(BarCharacterPiece::HalfBlock);
    }

    return get_bar_char_character_piece(BarCharacterPiece::FullBlock);
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

char BarsComponent::get_bar_char_character_piece(BarCharacterPiece character_piece) {
    switch(character_piece) {
        case BarCharacterPiece::FullBlock:
            {
                char fullBlockValues[28] = "QWERUOPKHGDSAXZCBNM09876532";
                auto index = std::rand() % (28 - 1);
                return fullBlockValues[index];
            }
        case BarCharacterPiece::HalfBlock:
            {
                char halfBlockValues[22] = "=-><zxcvbnmgasewqryuo";
                auto index = std::rand() % (22 - 1);
                return halfBlockValues[index];
            }
        case BarCharacterPiece::QuarterBlock:
            {
                char quarterBlockValues[4] = ".,_";
                auto index = std::rand() % (4 - 1);
                return quarterBlockValues[index];
            }
        case BarCharacterPiece::CornerLeft:
            {
                char cornerLeftValues[3] = "/d";
                auto index = std::rand() % (3 - 1);
                return cornerLeftValues[index];
            }
        case BarCharacterPiece::CornerRight:
            {
                char cornerRightValues[3] = "\\b";
                auto index = std::rand() % (3 - 1);
                return cornerRightValues[index];
            }
    }

    // TODO: this value should not be able to be reached in the future
    return 'x';
}
