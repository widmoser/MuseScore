//
// Created by Hannes Widmoser on 11/09/15.
//

#ifndef ORCHESTRALINTERFACECMAKE_SINGLEPLUGINPLAYER_H
#define ORCHESTRALINTERFACECMAKE_SINGLEPLUGINPLAYER_H

#include <vst/lib/plugin/AudioPlugin.h>
#include <vst/lib/midi/MidiSource.h>

#include "AudioGraph.h"

class SinglePluginGraph : public AudioGraph, public MidiEventListener {
public:
    explicit SinglePluginGraph(AudioPlugin* plugin = nullptr);

    virtual void start() override;
    virtual void stop() override;

    virtual void resume() override;

    virtual void suspend() override;

    AudioPlugin* getPlugin();
    void setPlugin(AudioPlugin* plugin);

    void processAudio(AudioSampleBuffer& output) override;
    void onMidiEvent(std::shared_ptr<const MidiMessage> message) override;
private:
    AudioPlugin* plugin;
    bool isStarted;
    bool isResumed;
};

#endif //ORCHESTRALINTERFACECMAKE_SINGLEPLUGINPLAYER_H
