//
// Created by Hannes Widmoser on 06/09/15.
//

#include "MidiMessage.h"

MidiMessage::MidiMessage(double deltaTime, const std::vector<unsigned char> &data) : deltaTime(deltaTime), data(data) {
}

const std::vector<unsigned char> &MidiMessage::getData() const {
    return data;
}
