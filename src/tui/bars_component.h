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
    SteepLeft,
    SteepRight,
};

class BarsComponent : public Component {
public:
    BarsComponent(ComponentData component_data);
    ComponentCharactersBuffer* create_component_text_buffer();
    ~BarsComponent();
private:
    PaSource m_source;

    unsigned int m_col_height;
    unsigned int m_bars_width;

    void set_spectrum_settings(const ComponentData* component_data);
    char get_bar_char(BarCharacterPiece character_piece);

    std::shared_ptr<SpectrumSettings> m_settings;
    std::unique_ptr<BarSpectrumDataTransformer> m_transformer;
};
