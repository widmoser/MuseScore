//
// Created by Hannes Widmoser on 08/09/15.
//

#ifndef ORCHESTRALINTERFACECMAKE_MIDIMESSAGEBUFFER_H
#define ORCHESTRALINTERFACECMAKE_MIDIMESSAGEBUFFER_H

#include <memory>
#include "MidiMessage.h"

class MidiMessageBuffer {
public:
    void addMessage(std::shared_ptr<const MidiMessage> msg);
    void clear();
    unsigned long size() const;

    const std::vector<std::shared_ptr<const MidiMessage>>& getMessages() const;
private:
    std::vector<std::shared_ptr<const MidiMessage>> messages;
};

#endif //ORCHESTRALINTERFACECMAKE_MIDIMESSAGEBUFFER_H
