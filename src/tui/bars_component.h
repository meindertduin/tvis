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

class BarsComponent : public Component {
public:
    BarsComponent();
    BarsComponent(ComponentData component_data);
    ComponentCharactersBuffer* create_component_text_buffer();
    ~BarsComponent();
private:
    PaSource m_source;

    void set_spectrum_settings();
    std::shared_ptr<SpectrumSettings> m_settings;
    std::unique_ptr<BarSpectrumDataTransformer> m_transformer;

    AnsiColor get_bar_section_color(int height);
};
