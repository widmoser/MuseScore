//
// Created by Hannes Widmoser on 29.12.17.
//

#ifndef ORCHESTRALINTERFACECMAKE_VSTAUDIOPLUGIN_H
#define ORCHESTRALINTERFACECMAKE_VSTAUDIOPLUGIN_H

#include <pluginterfaces/vst2.x/aeffect.h>
#include <audioeffectx.h>
#include <lib/plugin/AudioPlugin.h>

/**
 * Adapter to map the provided AudioPlugin implementation onto an AudioEffectX.
 */
class VSTAudioPlugin : public AudioEffectX {
public:
    VSTAudioPlugin(const audioMasterCallback& audioMaster, AudioPlugin* implementation);

    void processReplacing(float** inputs, float** outputs, VstInt32 sampleFrames) override;

    VstInt32 processEvents(VstEvents* events) override;

    bool getEffectName(char* name) override;

    bool getVendorString(char* text) override;

    bool getProductString(char* text) override;

    VstInt32 getVendorVersion() override;


private:
    void copy(const std::string& str, char* ptr);

    AudioPlugin* implementation;
    double sampleRate;
};

#endif //ORCHESTRALINTERFACECMAKE_VSTAUDIOPLUGIN_H
