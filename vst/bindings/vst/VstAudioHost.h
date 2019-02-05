//
// Created by Hannes Widmoser on 11/09/15.
//

#ifndef ORCHESTRALINTERFACECMAKE_VSTAUDIOHOST_H
#define ORCHESTRALINTERFACECMAKE_VSTAUDIOHOST_H

#include <vst.h>
#include <vst/lib/host/AudioHost.h>
#include <vst/lib/host/TimerFactory.h>
#include <vst/lib/plugin/AudioPlugin.h>
#include <vector>
#include <QtCore/QFileInfo>
#include "aeffect.h"
#include "aeffectx.h"

class VstAudioHost : public AudioHost {
public:
    VstAudioHost(double sampleRate, int frameSize, TimerFactory& timerFactory);
    ~VstAudioHost();
    virtual AudioPlugin* open(const QFileInfo& id) override;

    const std::vector<std::string>& getDefaultPluginSearchPaths() override;
    const std::vector<std::string>& getNameFilters() override;

    VstIntPtr handleCallback(AEffect* effect, VstInt32 opcode, VstInt32 index, VstIntPtr value, void* ptr, float opt);
private:
    void setHostTimeFrameRate(long frameRateIndex, double frameRate, double currentTime) noexcept;
    VstTimeInfo vstHostTime;
    TimerFactory& timerFactory;

    std::vector<std::string> nameFilters;
    std::vector<std::string> searchPaths;
};


#endif //ORCHESTRALINTERFACECMAKE_VSTAUDIOHOST_H
