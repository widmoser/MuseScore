//
// Created by Hannes Widmoser on 22.12.17.
//

#ifndef ORCHESTRALINTERFACECMAKE_MIDISOURCE_H
#define ORCHESTRALINTERFACECMAKE_MIDISOURCE_H

#include "MidiMessageBuffer.h"

class MidiEventListener {
public:
    virtual void onMidiEvent(std::shared_ptr<const MidiMessage> message) = 0;
};

/**
 * An source of midi commands.
 *
 * This will typically be a midi input port or a sequencer.
 */
class MidiSource {
public:
    void addListener(MidiEventListener* listener);
    void removeListener(MidiEventListener* listener);
protected:
    void notifyListeners(std::shared_ptr<const MidiMessage> message);
private:
    std::vector<MidiEventListener*> listeners;
};

#endif //ORCHESTRALINTERFACECMAKE_MIDISOURCE_H
