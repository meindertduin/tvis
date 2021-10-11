#include <stdint.h>
#include <vector>
#include "../source/pa_source.h"

#include "component.h"

#pragma once

using std::vector;

class BarsComponent : public Component {
public:
    BarsComponent(ComponentData component_data);
    void render();
    ~BarsComponent();
private:
    PaSource *m_source;
};
