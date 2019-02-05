//
// Created by Hannes Widmoser on 03/09/15.
//

#ifndef ORCHESTRALINTERFACECMAKE_WINDOWSAUDIOPLUGIN_H
#define ORCHESTRALINTERFACECMAKE_WINDOWSAUDIOPLUGIN_H

#include "vst/bindings/vst/VSTModule.h"
#include "VstAudioPluginProxy.h"
#include <QtCore/QFileInfo>

class VstModuleWindows : public VSTModule {
public:
    VstModuleWindows(const QFileInfo& pluginPath);
    virtual ~VstModuleWindows();

    virtual AEffect* open(audioMasterCallback host) throw(PluginInitializationException) override;
};


#endif //ORCHESTRALINTERFACECMAKE_WINDOWSAUDIOPLUGIN_H
