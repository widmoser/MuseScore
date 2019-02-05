//
// Created by Hannes Widmoser on 03/09/15.
//

#include <stdio.h>
#include <iostream>
#include <vst/lib/midi/MidiMessageBuffer.h>
#include <vst/lib/host/AudioHost.h>
#include <vst.h>
#include <vst/lib/plugin/Editor.h>

#include "VstAudioPluginProxy.h"
#include "VstEditorProxy.h"

using namespace std::placeholders;

VstAudioPluginProxy::VstAudioPluginProxy(VSTModule* module, AudioHost* host, TimerFactory& timerFactory)
    : VstEffectProxy(module->open(hostCallback)),
      module(module),
      timerFactory(timerFactory),
      editor(new VstEditorProxy(effect)),
      editIdleTimer(0),
      idleTimer(0),
      sampleRate(host->getSampleRate()),
      frameSize(host->getFrameSize()) {
    // Check plugin's magic number
    // If incorrect, then the file either was not loaded properly, is not a
    // real VST plugin, or is otherwise corrupt.
    if (effect->magic != kEffectMagic) {
        throw PluginInitializationException(module->getPluginPath(), "Plugin's magic number is bad\n");
    }

    effect->resvd1 = (VstIntPtr) this;
    effect->resvd2 = (VstIntPtr) host;
}

VstAudioPluginProxy::~VstAudioPluginProxy() {
    stop();
    effect = nullptr;
    delete module;
}

void VstAudioPluginProxy::start() {

    dispatcher(effIdentify, 0, 0, 0, 0);

    dispatcher(effSetSampleRate, 0, 0, NULL, sampleRate);

    dispatcher(effSetBlockSize, 0, frameSize, NULL, 0.0f);

    dispatcher(effOpen, 0, 0, NULL, 0.0f);

    dispatcher(effSetProgram, 0, 0, 0, 0);

    for (int i = effect->numInputs; --i >= 0;)
        dispatcher(effConnectInput, i, 1, 0, 0);
    for (int i = effect->numOutputs; --i >= 0;)
        dispatcher(effConnectOutput, i, 1, 0, 0);

//    bool wantsMidiMessages = dispatcher(effCanDo, 0, 0, (void*) "receiveVstMidiEvent", 0) > 0;
//    bool usesCocoaNSView =
//            (dispatcher(effCanDo, 0, 0, (void*) "hasCockosViewAsConfig", 0) & (int) 0xffff0000) == 0xbeef0000;

    dispatcher(effStartProcess, 0, 0, 0, 0);

    idleTimer = timerFactory.startRepeatingTimer(50, std::bind(&VstAudioPluginProxy::onTimer, this, _1));

    resume();
}

void VstAudioPluginProxy::resume() {
    dispatcher(effMainsChanged, 0, 1, NULL, 0.0f);
}

void VstAudioPluginProxy::suspend() {
    dispatcher(effMainsChanged, 0, 0, NULL, 0.0f);
}

void VstAudioPluginProxy::stop() {
    suspend();

    timerFactory.cancelRepeatingTimer(idleTimer);

    dispatcher(effClose, 0, 0, NULL, 0.0f);
}

bool VstAudioPluginProxy::can(const char* ch) const {
    return (dispatcher(effCanDo, 0, 0, (void*) ch, 0.0f) > 0);
}

void VstAudioPluginProxy::processAudio(AudioSampleBuffer& outputBuffer) {
    outputBuffer.clear();

    outputBuffer.setNumChannels(effect->numOutputs);
    if ((effect->flags & effFlagsCanReplacing) != 0) {
        effect->processReplacing(effect,
                                 outputBuffer.getChannels(),
                                 outputBuffer.getChannels(),
                                 (VstInt32) outputBuffer.getFrameSize());
    } else {
        // TODO:
        effect->process(effect,
                        outputBuffer.getChannels(),
                        outputBuffer.getChannels(),
                        (VstInt32) outputBuffer.getFrameSize());
    }
}

void VstAudioPluginProxy::onMidiEvent(std::shared_ptr<const MidiMessage> message) {
    midiBuffer.addMessage(message);
    processMidi(midiBuffer);
    midiBuffer.clear();
}

void VstAudioPluginProxy::processMidi(const MidiMessageBuffer& msg) {
    auto events = (VstEvents*) malloc(sizeof(VstEvents) + sizeof(VstEvents*) * (msg.size() - 2));
    events->numEvents = msg.size();
    int i = 0;
    for (auto it = msg.getMessages().begin(); it != msg.getMessages().end(); ++it, ++i) {
        auto midiEvent = new VstMidiEvent();
        midiEvent->type = kVstMidiType;
        midiEvent->byteSize = sizeof(VstMidiEvent);
        midiEvent->noteLength = 0;
        midiEvent->noteOffset = 0;
        midiEvent->detune = 0;
        midiEvent->noteOffVelocity = 0;
        midiEvent->deltaFrames = 0; // TODO: frameOffset;
        memcpy(midiEvent->midiData, (*it)->getData().data(), (size_t) (*it)->getData().size());
        events->events[i] = reinterpret_cast<VstEvent*>(midiEvent);
    }

    dispatcher(effProcessEvents, 0, 0, events, 0.0f);
}

bool VstAudioPluginProxy::usesChunks() const noexcept {
    return (effect->flags & effFlagsProgramChunks) != 0;
}

bool VstAudioPluginProxy::getChunkData(Data& mb, bool isPreset, int maxSizeMB) const {
    if (usesChunks()) {
        void* data = nullptr;
        VstIntPtr bytes = dispatcher(effGetChunk, isPreset ? 1 : 0, 0, &data, 0.0f);

        if (data != nullptr && bytes <= (size_t) maxSizeMB * 1024 * 1024) {
            mb.setSize(bytes);
            mb.copyFrom(data, bytes);

            return true;
        }
    }

    return false;
}

bool VstAudioPluginProxy::setChunkData(const Data& data, bool isPreset) {
    if (data.getSize() > 0 && usesChunks()) {
        dispatcher(effSetChunk, isPreset ? 1 : 0, data.getSize(), (void*) data.getData(), 0.0f);
        return true;
    }
    return false;
}

int VstAudioPluginProxy::getNumPrograms() const {
    if (effect != nullptr) {
        if (effect->numPrograms > 0)
            return effect->numPrograms;
        else
            return 0;
    }
    return 0;
}

int VstAudioPluginProxy::getCurrentProgram() const {
    return (int) dispatcher(effGetProgram, 0, 0, 0, 0);
}

void VstAudioPluginProxy::setCurrentProgram(int program) {
    if (program < 0 || program > getNumPrograms() - 1) {
        std::cerr << "Invalid program number: " << program << std::endl;
    }

    if (getNumPrograms() > 0 && program != getCurrentProgram())
        dispatcher(effSetProgram, 0, program, 0, 0);
}

const std::string VstAudioPluginProxy::getCurrentProgramName() const {
    char name[256] = {0};
    dispatcher(effGetProgramName, 0, 0, name, 0);
    return std::string(name);
}

const std::string VstAudioPluginProxy::getProgramName(int program) const {
    if (program == getCurrentProgram())
        return getCurrentProgramName();

    char name[256] = {0};
    dispatcher(effGetProgramNameIndexed, program, -1, name, 0);
    return std::string(name);
}

void VstAudioPluginProxy::changeProgramName(int program, const std::string& name) {
    // TODO: create substring from name or check length (limited to kVstMaxProgNameLen);
    int currentProgram = program;
    if (getCurrentProgram() != program) {
        currentProgram = getCurrentProgram();
        setCurrentProgram(program);
    }
    dispatcher(effSetProgramName, 0, 0, (void*) name.c_str(), 0.0f);
    setCurrentProgram(currentProgram);
}

int VstAudioPluginProxy::getNumParameters() const {
    return effect->numParams;
}

float VstAudioPluginProxy::getParameter(int param) const {
    return effect->getParameter(effect, param);
}

void VstAudioPluginProxy::setParameter(int param, float value) {
    effect->setParameter(effect, param, value);
}

const std::string VstAudioPluginProxy::getParameterName(int param) const {
    return getTextForOpcode(param, effGetParamName);
}

const std::string VstAudioPluginProxy::getParameterText(int param) const {
    return getTextForOpcode(param, effGetParamDisplay);
}

const std::string VstAudioPluginProxy::getParameterLabel(int param) const {
    return getTextForOpcode(param, effGetParamLabel);
}

bool VstAudioPluginProxy::isParameterAutomatable(int param) const {
    return dispatcher(effCanBeAutomated, param, 0, 0, 0) != 0;
}

const std::string VstAudioPluginProxy::getTextForOpcode(const int index, const VstInt32 opcode) const {
    char text[256] = {0};
    dispatcher(opcode, index, 0, text, 0);
    return std::string(text);
}

int VstAudioPluginProxy::getUID() const {
    return effect->uniqueID;
}

int VstAudioPluginProxy::getVersionNumber() const {
    return effect->version;
}

const std::string VstAudioPluginProxy::getVendorName() const {
    return getTextForOpcode(0, effGetVendorString);
}

const std::string VstAudioPluginProxy::getProductName() const {
    return getTextForOpcode(0, effGetProductString);
}

int VstAudioPluginProxy::getVendorVersion() const {
    return (int) dispatcher(effGetVendorVersion, 0, 0, 0, 0.0f);
}

void VstAudioPluginProxy::onTimer(int timerId) {
    if (timerId == idleTimer) {
        dispatcher(effIdle, 0, 0, 0, 0);
    } else if (timerId == editIdleTimer) {
        dispatcher(effEditIdle, 0, 0, 0, 0);
    }
}

Editor* VstAudioPluginProxy::getEditor() const {
    return editor.get();
}
