//
// Created by Hannes Widmoser on 08/09/15.
//

#include "MidiMessageBuffer.h"

void MidiMessageBuffer::addMessage(std::shared_ptr<const MidiMessage> msg) {
    messages.push_back(msg);
}

void MidiMessageBuffer::clear() {
    messages.clear();
}

unsigned long MidiMessageBuffer::size() const {
    return messages.size();
}

const std::vector<std::shared_ptr<const MidiMessage>>& MidiMessageBuffer::getMessages() const {
    return messages;
}
