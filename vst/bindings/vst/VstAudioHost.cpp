//
// Created by Hannes Widmoser on 11/09/15.
//

#include <string>
#include <iostream>
#include <QtCore/QFileInfo>
#include "VstAudioHost.h"

#ifdef WIN32
#include <windows/VSTModuleWindows.h>
#elif OSX
#include <bindings/vst/osx/VSTModuleOSX.h>
#endif

static int defaultSampleRate = 44100;
static int defaultFrameSize = 256;

std::string getOpCodeName(VstInt32 opcode) {
    switch (opcode) {
        case audioMasterAutomate:
            return "audioMasterAutomate";
        case audioMasterVersion:
            return "audioMasterVersion";
        case audioMasterCurrentId:
            return "audioMasterCurrentId";
        case audioMasterIdle:
            return "audioMasterIdle";
        case audioMasterPinConnected:
            return "audioMasterPinConnected";
        case audioMasterWantMidi:
            return "audioMasterWantMidi";
        case audioMasterGetTime:
            return "audioMasterGetTime";
        case audioMasterProcessEvents:
            return "audioMasterProcessEvents";
        case audioMasterSetTime:
            return "audioMasterSetTime";
        case audioMasterTempoAt:
            return "audioMasterTempoAt";
        case audioMasterGetNumAutomatableParameters:
            return "audioMasterGetNumAutomatableParameters";
        case audioMasterGetParameterQuantization:
            return "audioMasterGetParameterQuantization";
        case audioMasterIOChanged:
            return "audioMasterIOChanged";
        case audioMasterNeedIdle:
            return "audioMasterNeedIdle";
        case audioMasterSizeWindow:
            return "audioMasterSizeWindow";
        case audioMasterGetSampleRate:
            return "audioMasterGetSampleRate";
        case audioMasterGetBlockSize:
            return "audioMasterGetBlockSize";
        case audioMasterGetInputLatency:
            return "audioMasterGetInputLatency";
        case audioMasterGetOutputLatency:
            return "audioMasterGetOutputLatency";
        case audioMasterGetPreviousPlug:
            return "audioMasterGetPreviousPlug";
        case audioMasterGetNextPlug:
            return "audioMasterGetNextPlug";
        case audioMasterWillReplaceOrAccumulate:
            return "audioMasterWillReplaceOrAccumulate";
        case audioMasterGetCurrentProcessLevel:
            return "audioMasterGetCurrentProcessLevel";
        case audioMasterGetAutomationState:
            return "audioMasterGetAutomationState";
        case audioMasterOfflineStart:
            return "audioMasterOfflineStart";
        case audioMasterOfflineRead:
            return "audioMasterOfflineRead";
        case audioMasterOfflineWrite:
            return "audioMasterOfflineWrite";
        case audioMasterOfflineGetCurrentPass:
            return "audioMasterOfflineGetCurrentPass";
        case audioMasterOfflineGetCurrentMetaPass:
            return "audioMasterOfflineGetCurrentMetaPass";
        case audioMasterSetOutputSampleRate:
            return "audioMasterSetOutputSampleRate";
        case audioMasterGetOutputSpeakerArrangement:
            return "audioMasterGetOutputSpeakerArrangement";
        case audioMasterGetVendorString:
            return "audioMasterGetVendorString";
        case audioMasterGetProductString:
            return "audioMasterGetProductString";
        case audioMasterGetVendorVersion:
            return "audioMasterGetVendorVersion";
        case audioMasterVendorSpecific:
            return "audioMasterVendorSpecific";
        case audioMasterSetIcon:
            return "audioMasterSetIcon";
        case audioMasterCanDo:
            return "audioMasterCanDo";
        case audioMasterGetLanguage:
            return "audioMasterGetLanguage";
        case audioMasterOpenWindow:
            return "audioMasterOpenWindow";
        case audioMasterCloseWindow:
            return "audioMasterCloseWindow";
        case audioMasterGetDirectory:
            return "audioMasterGetDirectory";
        case audioMasterUpdateDisplay:
            return "audioMasterUpdateDisplay";
        case audioMasterBeginEdit:
            return "audioMasterBeginEdit";
        case audioMasterEndEdit:
            return "audioMasterEndEdit";
        case audioMasterOpenFileSelector:
            return "audioMasterOpenFileSelector";
        case audioMasterCloseFileSelector:
            return "audioMasterCloseFileSelector";
        case audioMasterEditFile:
            return "audioMasterEditFile";
        case audioMasterGetChunkFile:
            return "audioMasterGetChunkFile";
        case audioMasterGetInputSpeakerArrangement:
            return "audioMasterGetInputSpeakerArrangement";
        default:
            return "unknown";
    }
}

// handles non plugin-specific callbacks..
static VstIntPtr handleGeneralCallback(VstInt32 opcode, VstInt32 /*index*/, VstIntPtr /*value*/, void* ptr,
                                       float /*opt*/) {
    switch (opcode) {
        case audioMasterCanDo: {
            static const char* canDos[] = {"supplyIdle",
                                           "sendVstEvents",
                                           "sendVstMidiEvent",
                                           "sendVstTimeInfo",
                                           "receiveVstEvents",
                                           "receiveVstMidiEvent",
                                           "supportShell",
                                           "sizeWindow",
                                           "shellCategory"};

            for (int i = 0; i < 9; ++i)
                if (strcmp(canDos[i], (const char*) ptr) == 0)
                    return 1;

            return 0;
        }

        case audioMasterVersion:
            return 2400;
        case audioMasterCurrentId:
            return 0;
        case audioMasterGetNumAutomatableParameters:
            return 0;
        case audioMasterGetAutomationState:
            return 1;
        case audioMasterGetVendorVersion:
            return 0x0101;

        case audioMasterGetVendorString:
        case audioMasterGetProductString: {
            strcpy((char*) ptr, "Test Host");
            break;
        }

        case audioMasterGetSampleRate:
            return (VstIntPtr) defaultSampleRate;
        case audioMasterGetBlockSize:
            return (VstIntPtr) defaultFrameSize;

        default:
            printf("*** Unhandled VST Callback: %s\n", getOpCodeName(opcode).c_str());
            break;
    }

    return 0;
}

VstIntPtr VSTCALLBACK hostCallback(AEffect* effect, VstInt32 opcode,
                                   VstInt32 index, VstIntPtr value, void* ptr, float opt) {

//    if (opcode != audioMasterGetTime && opcode != audioMasterGetCurrentProcessLevel)
//        std::cout << "AudioMaster: " << getOpCodeName(opcode) << " (" << opcode << ")" << std::endl;

    if (effect != nullptr) {
        VstAudioHost* host = (VstAudioHost*) effect->resvd2;
        return host->handleCallback(effect, opcode, index, value, ptr, opt);
    }

    return handleGeneralCallback(opcode, index, value, ptr, opt);

}

VstAudioHost::VstAudioHost(double sampleRate, int frameSize, TimerFactory& timerFactory)
        : AudioHost(sampleRate, frameSize), timerFactory(timerFactory) {
    vstHostTime.tempo = 120.0;
    vstHostTime.timeSigNumerator = 4;
    vstHostTime.timeSigDenominator = 4;
    vstHostTime.sampleRate = sampleRate;
    vstHostTime.samplePos = 0;
    vstHostTime.flags = kVstNanosValid | kVstAutomationWriting | kVstAutomationReading;

#ifdef WIN32
    searchPaths.emplace_back("C:\\Program Files\\Steinberg\\Vstplugins");
    searchPaths.emplace_back("C:\\Program Files (x86)\\Steinberg\\Vstplugins");
    searchPaths.emplace_back("C:\\Program Files\\VSTPlugins");
    searchPaths.emplace_back("C:\\Program Files (x86)\\VSTPlugins");
    searchPaths.emplace_back("C:\\Program Files\\Common Files\\Steinberg\\VST2");
    searchPaths.emplace_back("C:\\Program Files (x86)\\Common Files\\Steinberg\\VST2");
    searchPaths.emplace_back("C:\\vstplugins");
    nameFilters.emplace_back("*.dll");
#elif OSX
    searchPaths.emplace_back("/Library/Audio/Plug-Ins/VST");
    searchPaths.emplace_back("/Users/hannes/Library/Audio/Plug-Ins/VST");
    nameFilters.emplace_back("*.vst");
#endif
}

VstIntPtr VstAudioHost::handleCallback(AEffect* effect, VstInt32 opcode, VstInt32 index, VstIntPtr value, void* ptr,
                                       float opt) {

    switch (opcode) {
        case audioMasterGetTime: {
            return (VstIntPtr) &vstHostTime;;
        }

        case audioMasterCanDo: {
            static const char* canDos[] = {"supplyIdle",
                                           "sendVstEvents",
                                           "sendVstMidiEvent",
                                           "sendVstTimeInfo",
                                           "receiveVstEvents",
                                           "receiveVstMidiEvent",
                                           "supportShell",
                                           "sizeWindow",
                                           "shellCategory"};

            for (int i = 0; i < 9; ++i)
                if (strcmp(canDos[i], (const char*) ptr) == 0)
                    return 1;

            return 0;
        }

        case audioMasterVersion:
            return 2400;
        case audioMasterCurrentId:
            return 0;
        case audioMasterGetAutomationState:
            return 1;
        case audioMasterGetVendorVersion:
            return 0x0101;

        case audioMasterGetVendorString:
        case audioMasterGetProductString: {
            strcpy((char*) ptr, "Test Host");
            break;
        }

        case audioMasterGetSampleRate:
            return (VstIntPtr) getSampleRate();
        case audioMasterGetBlockSize:
            return (VstIntPtr) getFrameSize();

        case audioMasterGetCurrentProcessLevel:
            return (VstIntPtr) kVstProcessLevelRealtime;

        case audioMasterUpdateDisplay: {
            // TODO: Implement
            return 0;
        }

        case audioMasterWantMidi:
            return 1;

        default:
            printf("*** Unhandled VST Callback: %s\n", getOpCodeName(opcode).c_str());
            break;
    }

    return 0;

}

void VstAudioHost::setHostTimeFrameRate(long frameRateIndex, double frameRate, double currentTime) noexcept {
    vstHostTime.flags |= kVstSmpteValid;
    vstHostTime.smpteFrameRate  = (VstInt32) frameRateIndex;
    vstHostTime.smpteOffset     = (VstInt32) (currentTime * 80.0 * frameRate + 0.5);
}

AudioPlugin* VstAudioHost::open(const QFileInfo& id) {
#ifdef WIN32
    return new VstAudioPluginProxy(new VstModuleWindows(id), this, timerFactory);
#elif OSX
    return new VstAudioPluginProxy(new VSTModuleOSX(id.c_str()), this, timerFactory);
#endif
}

VstAudioHost::~VstAudioHost() {
}

const std::vector<std::string>& VstAudioHost::getDefaultPluginSearchPaths() {
    return searchPaths;
}

const std::vector<std::string>& VstAudioHost::getNameFilters() {
    return nameFilters;
}
