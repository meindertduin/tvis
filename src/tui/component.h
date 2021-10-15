#include <functional>
#include <memory>

#pragma once

#include "component_characters_buffer.h"

struct ComponentData {
    int width, height, x_pos, y_pos;
};

class Component {
public:
    Component() : m_component_data({0, 0, 0, 0}), m_component_character_buffer{nullptr} {};

    Component(ComponentData component_data) :
        m_component_data(component_data), m_component_character_buffer(new ComponentCharactersBuffer(component_data.width, component_data.height)) {
    };

    void set_component_data(ComponentData component_data) {
        if (m_component_data.height != component_data.height || m_component_data.width != component_data.width) {
            delete m_component_character_buffer;
            m_component_character_buffer = new ComponentCharactersBuffer(component_data.width, component_data.height);

            if (m_on_resize != nullptr) {
                // implementations can set the m_on_resize, to handle if the component boundries change
                m_on_resize(&component_data);
            }
        }

        m_component_data = component_data;
    }

    virtual ComponentCharactersBuffer* create_component_text_buffer() = 0;

    ~Component() {
        delete m_component_character_buffer;
    }
protected:
    ComponentData m_component_data;
    ComponentCharactersBuffer* m_component_character_buffer;
    std::function<void(const ComponentData*)> m_on_resize = nullptr;
};
