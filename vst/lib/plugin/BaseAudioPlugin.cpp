//
// Created by Hannes Widmoser on 30.12.17.
//

#include "BaseAudioPlugin.h"

void BaseAudioPlugin::start() {
}

void BaseAudioPlugin::resume() {
}

void BaseAudioPlugin::suspend() {
}

void BaseAudioPlugin::stop() {
}

void BaseAudioPlugin::processAudio(AudioSampleBuffer& buffer) {
}

bool BaseAudioPlugin::can(const char* ch) const {
    return false;
}

const std::string BaseAudioPlugin::getVendorName() const {
    return "";
}

const std::string BaseAudioPlugin::getProductName() const {
    return "";
}

int BaseAudioPlugin::getVendorVersion() const {
    return 0;
}

int BaseAudioPlugin::getNumPrograms() const {
    return 0;
}

int BaseAudioPlugin::getCurrentProgram() const {
    return 0;
}

void BaseAudioPlugin::setCurrentProgram(int program) {
}

const std::string BaseAudioPlugin::getCurrentProgramName() const {
    return nullptr;
}

const std::string BaseAudioPlugin::getProgramName(int program) const {
    return nullptr;
}

void BaseAudioPlugin::changeProgramName(int program, const std::string& name) {
}

int BaseAudioPlugin::getNumParameters() const {
    return 0;
}

float BaseAudioPlugin::getParameter(int param) const {
    return 0;
}

void BaseAudioPlugin::setParameter(int param, float value) {
}

const std::string BaseAudioPlugin::getParameterName(int param) const {
    return "";
}

const std::string BaseAudioPlugin::getParameterText(int param) const {
    return "";
}

const std::string BaseAudioPlugin::getParameterLabel(int param) const {
    return "";
}

bool BaseAudioPlugin::isParameterAutomatable(int param) const {
    return false;
}

int BaseAudioPlugin::getUID() const {
    return 0;
}

int BaseAudioPlugin::getVersionNumber() const {
    return 0;
}

bool BaseAudioPlugin::setChunkData(const Data& data, bool isPreset) {
    return false;
}

bool BaseAudioPlugin::getChunkData(Data& mb, bool isPreset, int maxSizeMB) const {
    return false;
}

bool BaseAudioPlugin::usesChunks() const {
    return false;
}

void BaseAudioPlugin::onMidiEvent(std::shared_ptr<const MidiMessage> message) {
}

Editor* BaseAudioPlugin::getEditor() const {
    return nullptr;
}
