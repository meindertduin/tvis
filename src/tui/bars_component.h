#include <stdint.h>
#include <vector>
#include "../source/pa_source.h"

#include "component.h"
#include "../bar_spectrum_data_tranformer.h"

#pragma once

using std::vector;

class BarsComponent : public Component {
public:
    BarsComponent();
    BarsComponent(ComponentData component_data);
    ComponentCharactersBuffer* create_component_text_buffer();
    ~BarsComponent();
private:
    PaSource m_source;

    BarSpectrumDataTransformer m_transformer;
    AnsiColor get_bar_section_color(int height);
};
