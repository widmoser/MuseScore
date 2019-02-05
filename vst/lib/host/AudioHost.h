//
// Created by Hannes Widmoser on 11/09/15.
//

#ifndef ORCHESTRALINTERFACECMAKE_AUDIOHOST_H
#define ORCHESTRALINTERFACECMAKE_AUDIOHOST_H


#include <vst/lib/plugin/AudioPlugin.h>
#include <QtCore/QFileInfo>

class AudioHost {
public:
    AudioHost(double sampleRate, int frameSize);
    virtual ~AudioHost();
    virtual AudioPlugin* open(const QFileInfo& id) = 0;

    virtual const std::vector<std::string>& getDefaultPluginSearchPaths() = 0;
    virtual const std::vector<std::string>& getNameFilters() = 0;

    double getSampleRate() const;
    int getFrameSize() const;
private:
    double sampleRate;
    int frameSize;
};


#endif //ORCHESTRALINTERFACECMAKE_AUDIOHOST_H
