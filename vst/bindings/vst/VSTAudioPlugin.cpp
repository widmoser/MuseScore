//
// Created by Hannes Widmoser on 29.12.17.
//

#include <bindings/vst/VstEditor.h>
#include "VSTAudioPlugin.h"

VSTAudioPlugin::VSTAudioPlugin(const audioMasterCallback& audioMaster, AudioPlugin* implementation)
    : AudioEffectX(audioMaster, implementation->getNumPrograms(), implementation->getNumParameters()),
      implementation(implementation) {
    setNumInputs(2);
    setNumOutputs(2);
    setEditor(new VstEditor(implementation));
}

void VSTAudioPlugin::processReplacing(float** inputs, float** outputs, VstInt32 sampleFrames) {
    AudioSampleBuffer buffer(2, sampleFrames, inputs);
    implementation->processAudio(buffer);
    buffer.copy(outputs);
}

VstInt32 VSTAudioPlugin::processEvents(VstEvents* events) {
    for (int i = 0; i < events->numEvents; ++i) {
        VstEvent* event = events->events[i];
        if (event->type == kVstMidiType) {
            auto midiEvent = reinterpret_cast<VstMidiEvent*>(event);
            std::vector<unsigned char> data(4);
            std::copy(midiEvent->midiData, midiEvent->midiData + 4, data.begin());
            auto message = std::make_shared<const MidiMessage>(0.0, data);
            implementation->onMidiEvent(message);
        }
    }

    return 0; // Ignored.
}

bool VSTAudioPlugin::getEffectName(char* name) {
    copy(implementation->getProductName(), name);
    return true;
}

bool VSTAudioPlugin::getVendorString(char* text) {
    copy(implementation->getVendorName(), text);
    return true;
}

bool VSTAudioPlugin::getProductString(char* text) {
    copy(implementation->getProductName(), text);
    return true;
}

VstInt32 VSTAudioPlugin::getVendorVersion() {
    return implementation->getVendorVersion();
}

void VSTAudioPlugin::copy(const std::string& str, char* ptr) {
    str.copy(ptr, str.length());
    ptr[str.length()] = '\0';
}

extern AudioPlugin* createAudioPluginInstance();

AudioEffect* createEffectInstance(audioMasterCallback audioMaster) {
    return new VSTAudioPlugin(audioMaster, createAudioPluginInstance());
}