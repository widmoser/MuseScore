//
// Created by Hannes Widmoser on 22.12.17.
//

#ifndef ORCHESTRALINTERFACECMAKE_RTMIDIINPUTSOURCE_H
#define ORCHESTRALINTERFACECMAKE_RTMIDIINPUTSOURCE_H

#include <vst/third_party/rtmidi/RtMidi.h>
#include <vst/lib/midi/MidiSource.h>
#include <vst/lib/midi/MidiMessageBuffer.h>

class RtMidiInputSource : public MidiSource {
public:
    RtMidiInputSource();

private:
    std::unique_ptr<RtMidiIn> midiIn;

    void onMidiMessage(double timeStamp, std::vector<unsigned char>* message);
    static void onMidiMessageStaticWrapper(double timeStamp, std::vector<unsigned char>* message, void* userData);
};

#endif //ORCHESTRALINTERFACECMAKE_RTMIDIINPUTSOURCE_H
