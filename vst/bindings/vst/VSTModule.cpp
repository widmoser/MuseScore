//
// Created by Hannes Widmoser on 15/09/15.
//

#include "VSTModule.h"

VSTModule::VSTModule(const QFileInfo& pluginPath) : pluginPath(pluginPath) {

}

const QFileInfo& VSTModule::getPluginPath() const {
    return pluginPath;
}
