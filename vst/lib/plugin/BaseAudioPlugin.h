//
// Created by Hannes Widmoser on 30.12.17.
//

#ifndef ORCHESTRALINTERFACECMAKE_BASEAUDIOPLUGIN_H
#define ORCHESTRALINTERFACECMAKE_BASEAUDIOPLUGIN_H

#include <plugin/AudioPlugin.h>

class BaseAudioPlugin : public AudioPlugin {
    void start() override;
    void resume() override;
    void suspend() override;
    void stop() override;
    void processAudio(AudioSampleBuffer& buffer) override;
    bool can(const char* ch) const override;
    const std::string getVendorName() const override;
    const std::string getProductName() const override;
    int getVendorVersion() const override;
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
    bool setChunkData(const Data& data, bool isPreset) override;
    bool getChunkData(Data& mb, bool isPreset, int maxSizeMB) const override;
    bool usesChunks() const override;
    void onMidiEvent(std::shared_ptr<const MidiMessage> message) override;
    Editor* getEditor() const override;
};

#endif //ORCHESTRALINTERFACECMAKE_BASEAUDIOPLUGIN_H
