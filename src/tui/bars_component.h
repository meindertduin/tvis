#include <stdint.h>
#include <vector>
#include "../source/pa_source.h"

#include "component.h"

#pragma once

using std::vector;

class BarsComponent : public Component {
public:
    BarsComponent();
    BarsComponent(ComponentData component_data);
    ComponentCharactersBuffer* get_component_buffer();
    ~BarsComponent();
private:
    PaSource m_source;

    AnsiColor get_bar_section_color(int height);
};
