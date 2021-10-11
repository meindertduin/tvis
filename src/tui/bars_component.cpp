#include "bars_component.h"
#include "../constants.h"
#include "../bar_spectrum_data_tranformer.h"

BarsComponent::BarsComponent(ComponentData component_data) : Component(component_data) {
    m_source = new PaSource();
}

BarsComponent::~BarsComponent() {
    delete m_source;
}

void BarsComponent::render() {
    BarSpectrumDataTransformer transformer;
    buffer_frame buffer[Constants::k_sample_size];

    transformer.transform(buffer, sizeof(buffer));
}
