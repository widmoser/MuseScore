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

#ifndef __VST_H__
#define __VST_H__

#include "synthesizer/synthesizer.h"
#include "synthesizer/event.h"
#include "synthesizer/midipatch.h"

#include "vst/lib/host/graph/SinglePluginGraph.h"
#include "vst/bindings/vst/VstAudioHost.h"
#include "vst/bindings/qt/QtTimerFactory.h"
#include "vst/lib/host/PluginRegistry.h"

class VstSynthesizer : public Ms::Synthesizer {
private:
    QtTimerFactory timerFactory;
    VstAudioHost audioHost;
    PluginRegistry pluginRegistry;
    SinglePluginGraph plugin;
    AudioSampleBuffer buffer;
    QList<Ms::MidiPatch *> _patchInfo;
public:
    VstSynthesizer();

    const char *name() const override;

    bool loadSoundFonts(const QStringList &list) override;

    QStringList soundFonts() const override;

    void process(unsigned int i, float *pDouble, float *pDouble1, float *pDouble2) override;

    void play(const Ms::PlayEvent &event) override;

    const QList<Ms::MidiPatch *> &getPatchInfo() const override;

    Ms::SynthesizerGroup state() const override;

    bool setState(const Ms::SynthesizerGroup &group) override;

    virtual Ms::SynthesizerGui* gui();
};


#endif //__VST_H__
