//
// Created by Hannes Widmoser on 06/09/15.
//

#ifndef ORCHESTRALINTERFACECMAKE_MIDIMESSAGE_H
#define ORCHESTRALINTERFACECMAKE_MIDIMESSAGE_H


#include <vector>

class MidiMessage {
public:
    MidiMessage(double deltaTime, const std::vector<unsigned char> &data);
    const std::vector<unsigned char>& getData() const;
private:
    double deltaTime;
    std::vector<unsigned char> data;
};


#endif //ORCHESTRALINTERFACECMAKE_MIDIMESSAGE_H
