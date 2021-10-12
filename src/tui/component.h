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
        m_component_data = component_data;
        m_component_character_buffer = new ComponentCharactersBuffer(component_data.width, component_data.height);
    }

    virtual ComponentCharactersBuffer* get_component_buffer() = 0;

    ~Component() {
        delete m_component_character_buffer;
    }
protected:
    ComponentData m_component_data;
    ComponentCharactersBuffer* m_component_character_buffer;
};
