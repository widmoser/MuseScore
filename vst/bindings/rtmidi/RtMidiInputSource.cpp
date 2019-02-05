//
// Created by Hannes Widmoser on 22.12.17.
//

#include <vst/lib/midi/MidiMessageBuffer.h>
#include "RtMidiInputSource.h"

RtMidiInputSource::RtMidiInputSource() : midiIn(new RtMidiIn()) {
    if (midiIn->getPortCount() > 0) {
        midiIn->openPort(0);
    } else {
        std::cerr << "MIDI Port Count: " << midiIn->getPortCount() << std::endl;
    }
    midiIn->setCallback(&RtMidiInputSource::onMidiMessageStaticWrapper, this);
}

void RtMidiInputSource::onMidiMessage(double timeStamp, std::vector<unsigned char>* message) {
    auto newMessage = std::make_shared<const MidiMessage>(timeStamp, *message);
    notifyListeners(newMessage);
}

void RtMidiInputSource::onMidiMessageStaticWrapper(double timeStamp,
                                                   std::vector<unsigned char>* message,
                                                   void* userData) {
    auto source = reinterpret_cast<RtMidiInputSource*>(userData);
    source->onMidiMessage(timeStamp, message);
}
