//
// Created by Hannes Widmoser on 03/09/15.
//

#ifndef ORCHESTRALINTERFACECMAKE_AUDIOPLUGIN_H
#define ORCHESTRALINTERFACECMAKE_AUDIOPLUGIN_H

#include <vst/lib/midi/MidiMessage.h>
#include <vst/lib/midi/MidiMessageBuffer.h>
#include <vst/lib/util/Data.h>
#include <vst/lib/audio/AudioSampleBuffer.h>
#include <vst/lib/audio/AudioProcessor.h>
#include <vst/lib/host/PluginView.h>
#include <vst/lib/midi/MidiSource.h>
#include <vst/lib/plugin/Editor.h>

/**
 * Proxy to access an audio plugin on the host side.
 */
class AudioPlugin : public AudioProcessor, public MidiEventListener {
public:
    virtual ~AudioPlugin() = default;

    virtual bool can(const char* ch) const = 0;

    virtual const std::string getVendorName() const = 0;
    virtual const std::string getProductName() const = 0;
    virtual int getVendorVersion() const = 0;

    virtual int getNumPrograms() const = 0;
    virtual int getCurrentProgram() const = 0;
    virtual void setCurrentProgram(int program) = 0;
    virtual const std::string getCurrentProgramName() const = 0;
    virtual const std::string getProgramName(int program) const = 0;
    virtual void changeProgramName(int program, const std::string& name) = 0;

    virtual int getNumParameters() const = 0;
    virtual float getParameter(int param) const = 0;
    virtual void setParameter(int param, float value) = 0;
    virtual const std::string getParameterName(int param) const = 0;
    virtual const std::string getParameterText(int param) const = 0;
    virtual const std::string getParameterLabel(int param) const = 0;
    virtual bool isParameterAutomatable(int param) const = 0;

    virtual int getUID() const = 0;
    virtual int getVersionNumber() const = 0;

    virtual bool setChunkData(const Data& data, bool isPreset) = 0;
    virtual bool getChunkData(Data& mb, bool isPreset, int maxSizeMB = 128) const = 0;

    virtual bool usesChunks() const = 0;

    virtual Editor* getEditor() const = 0;
};

#endif //ORCHESTRALINTERFACECMAKE_AUDIOPLUGIN_H
