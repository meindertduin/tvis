
struct ComponentData {
    int width, height, x_pos, y_pos;
};

class Component {
public:
    Component(ComponentData component_data) : m_component_data(component_data) {};
    virtual void render() = 0;
protected:
    ComponentData m_component_data;
};
