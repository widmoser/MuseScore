//
// Created by Hannes Widmoser on 03/09/15.
//

#ifndef ORCHESTRALINTERFACECMAKE_OSXAUDIOPLUGIN_H
#define ORCHESTRALINTERFACECMAKE_OSXAUDIOPLUGIN_H

#include <Carbon/Carbon.h>
#include <lib/host/AudioHost.h>
#include <bindings/vst/VstAudioPluginProxy.h>
#include <bindings/vst/VSTModule.h>

class VSTModuleOSX : public VSTModule {
public:
    VSTModuleOSX(const std::string pluginPath);
    virtual ~VSTModuleOSX();

    virtual AEffect* open(audioMasterCallback host) throw(PluginInitializationException) override;
private:
    CFBundleRef bundle;
};

#endif //ORCHESTRALINTERFACECMAKE_OSXAUDIOPLUGIN_H
