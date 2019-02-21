//=============================================================================
//  Vst
//  Vst based synthesizer
//
//  Copyright (C) 2013 Werner Schweer
//
//  This program is free software; you can redistribute it and/or modify
//  it under the terms of the GNU General Public License version 2
//  as published by the Free Software Foundation and appearing in
//  the file LICENCE.GPL
//=============================================================================

#include "vst.h"
#include <iostream>

Ms::Synthesizer *createVstSynthesizer() {
    return new VstSynthesizer();
}

VstSynthesizer::VstSynthesizer()
        : Synthesizer(), audioHost(44100, 256, timerFactory), pluginRegistry(audioHost), buffer(2, 1024) {
    Ms::MidiPatch *patch = new Ms::MidiPatch();
    patch->bank = 0;
    patch->prog = 0;
    patch->name = "Piano (VST)";
    patch->synti = "vst";
    _patchInfo.append(patch);
    pluginRegistry.init();
}

const char *VstSynthesizer::name() const {
    std::cout << "VstSynthesizer::name" << std::endl;
    return "vst";
}

bool VstSynthesizer::loadSoundFonts(const QStringList &list) {
    std::cout << "VstSynthesizer::loadSoundFonts" << std::endl;
    return false;
}

QStringList VstSynthesizer::soundFonts() const {
    std::cout << "VstSynthesizer::soundFonts" << std::endl;
    return QStringList();
}

void VstSynthesizer::process(unsigned int numFrames, float *audioData, float *effect1, float *effect2) {
    float *o = (float *) audioData;
    AudioSampleBuffer buffer(2, numFrames, this->buffer.getChannels());
    plugin.processAudio(buffer);
    for (int i = 0; i < numFrames; ++i) {
        *o++ = buffer.get(0, i);
        *o++ = buffer.get(1, i);
    }
}

void VstSynthesizer::play(const Ms::PlayEvent &event) {
    std::vector<unsigned char> data;
    data.push_back(event.type());
    data.push_back(event.channel());
    data.push_back(event.dataA());
    data.push_back(event.dataB());
    auto midiMessage = std::make_shared<const MidiMessage>(0, data);
    plugin.onMidiEvent(midiMessage);
}

const QList<Ms::MidiPatch *> &VstSynthesizer::getPatchInfo() const {
    std::cout << "VstSynthesizer::getPatchInfo" << std::endl;
    return _patchInfo;
}

Ms::SynthesizerGroup VstSynthesizer::state() const {
    std::cout << "VstSynthesizer::state" << std::endl;
    return Ms::SynthesizerGroup();
}

bool VstSynthesizer::setState(const Ms::SynthesizerGroup &group) {
    std::cout << "VstSynthesizer::setState" << std::endl;
    return false;
}
