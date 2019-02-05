//
// Created by Hannes Widmoser on 15/09/15.
//

#ifndef ORCHESTRALINTERFACECMAKE_VSTMODULE_H
#define ORCHESTRALINTERFACECMAKE_VSTMODULE_H


#include <aeffect.h>
#include <vst/lib/host/exception/PluginInitializationException.h>
#include <QtCore/QFileInfo>

class VSTModule {
public:
    explicit VSTModule(const QFileInfo& pluginPath);
    virtual ~VSTModule() = default;

    const QFileInfo& getPluginPath() const;

    virtual AEffect* open(audioMasterCallback host) = 0;
private:
    const QFileInfo pluginPath;
};


#endif //ORCHESTRALINTERFACECMAKE_VSTMODULE_H
