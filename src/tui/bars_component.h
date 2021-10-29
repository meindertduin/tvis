#include <stdint.h>
#include <vector>
#include <memory>

#pragma once

#include "../source/pa_source.h"
#include "component.h"
#include "../bar_spectrum_data_tranformer.h"
#include "../settings.h"
#include "../constants.h"


using std::vector;

enum BarCharacterPiece {
    FullBlock,
    HalfBlock,
    QuarterBlock,
    CornerLeft,
    CornerRight,
};

class BarsComponent : public Component {
public:
    BarsComponent(ComponentData component_data);
    ComponentCharactersBuffer* create_component_text_buffer();
    ~BarsComponent();
private:
    struct CurrentBarData {
        uint32_t bar_index;
        uint32_t first_decimal;
        uint32_t extra_height;
        uint32_t bar_height;
        uint32_t width_index;
        uint32_t height_index;
        uint32_t inverted_height;
    };
    PaSource m_source;

    unsigned int m_col_height;
    unsigned int m_bars_width;
    unsigned int m_inactive_count = 0;

    const unsigned int km_max_inactive_count = 5;

    vector<double> get_bars();
    char get_bar_char(const CurrentBarData *current_bar_data, vector<double> *bars);
    char get_bar_top_char(vector<double> *bars, const CurrentBarData *current_bar_data);
    void set_spectrum_settings(const ComponentData* component_data);
    char get_bar_char_character_piece(BarCharacterPiece character_piece);
    char get_straight_top_block(int first_decimal);
    void set_is_active(bool value);

    std::shared_ptr<SpectrumSettings> m_settings;
    std::unique_ptr<BarSpectrumDataTransformer> m_transformer;
};
