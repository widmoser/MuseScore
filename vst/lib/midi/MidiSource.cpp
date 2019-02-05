//
// Created by Hannes Widmoser on 23.12.17.
//

#include <algorithm>
#include "MidiSource.h"

void MidiSource::addListener(MidiEventListener* listener) {
    listeners.push_back(listener);
}

void MidiSource::removeListener(MidiEventListener* listener) {
    listeners.erase(std::find(listeners.begin(), listeners.end(), listener));
}

void MidiSource::notifyListeners(std::shared_ptr<const MidiMessage> message) {
    for (MidiEventListener* listener : listeners) {
        listener->onMidiEvent(message);
    }
}
