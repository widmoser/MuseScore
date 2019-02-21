//
// Created by Hannes Widmoser on 03/09/15.
//

#ifndef ORCHESTRALINTERFACECMAKE_VSTAUDIOPLUGIN_H
#define ORCHESTRALINTERFACECMAKE_VSTAUDIOPLUGIN_H


#include <aeffect.h>
#include <aeffectx.h>
#include <vst/lib/midi/MidiMessageBuffer.h>
#include <vst/lib/host/AudioHost.h>
#include <vst/lib/util/Data.h>
#include <vst/lib/host/TimerFactory.h>
#include <vst/lib/plugin/AudioPlugin.h>
#include <VSTModule.h>
#include <vst/lib/plugin/Editor.h>
#include "VstEffectProxy.h"

/**
 * A host side proxy for accessing a VST audio plugin.
 */
class VstAudioPluginProxy : public AudioPlugin, public VstEffectProxy {
public:
    VstAudioPluginProxy(VSTModule* module, AudioHost* host, TimerFactory& timerFactory);
    ~VstAudioPluginProxy() override;

    void start() override;
    void resume() override;
    void suspend() override;
    void stop() override;
    bool can(const char* ch) const override;

    const std::string getVendorName() const override;
    const std::string getProductName() const override;
    int getVendorVersion() const override;

    void onMidiEvent(std::shared_ptr<const MidiMessage> msg) override;
    void processAudio(AudioSampleBuffer& buffer) override;

    int getNumPrograms() const override;
    int getCurrentProgram() const override;
    void setCurrentProgram(int program) override;
    const std::string getCurrentProgramName() const override;
    const std::string getProgramName(int program) const override;
    void changeProgramName(int program, const std::string& name) override;

    int getNumParameters() const override;
    float getParameter(int param) const override;
    void setParameter(int param, float value) override;
    const std::string getParameterName(int param) const override;
    const std::string getParameterText(int param) const override;
    const std::string getParameterLabel(int param) const override;
    bool isParameterAutomatable(int param) const override;

    int getUID() const override;
    int getVersionNumber() const override;

    bool getChunkData(Data& mb, bool isPreset, int maxSizeMB) const override;
    bool setChunkData(const Data& data, bool isPreset) override;
    virtual bool usesChunks() const noexcept override;

    Editor* getEditor() const override;
private:
    const std::string getTextForOpcode (const int index, const VstInt32 opcode) const;


    void onTimer(int timerId);
    void processMidi(const MidiMessageBuffer& msg);

    VstEvents* vstMidiEvents;

    VSTModule* module;
    TimerFactory& timerFactory;
    std::unique_ptr<Editor> editor;
    MidiMessageBuffer midiBuffer;

    int editIdleTimer;
    int idleTimer;

    double sampleRate;
    int frameSize;
};


#endif //ORCHESTRALINTERFACECMAKE_VSTAUDIOPLUGIN_H
