//
// Created by Hannes Widmoser on 03/09/15.
//

#include <vst/bindings/vst/vst.h>
#include <windows.h>
#include "VSTModuleWindows.h"

#include <QTextStream>
#include <QDebug>

VstModuleWindows::VstModuleWindows(const QFileInfo &pluginPath) : VSTModule(pluginPath) {
}

VstModuleWindows::~VstModuleWindows() {

}

AEffect *VstModuleWindows::open(audioMasterCallback host) throw(PluginInitializationException) {
    AEffect *plugin = NULL;
    wchar_t buffer[200];
    getPluginPath().absoluteFilePath().toWCharArray(buffer);

    HMODULE modulePtr = LoadLibraryW(buffer);
    if (modulePtr == NULL) {
        qWarning() << "Failed trying to load VST from '" << getPluginPath().absoluteFilePath() << "', error "
                   << GetLastError();
        throw PluginInitializationException(getPluginPath(), "");
    }

    vstPluginFuncPtr mainEntryPoint = (vstPluginFuncPtr) GetProcAddress(modulePtr, "VSTPluginMain");
    // Instantiate the plugin
    plugin = mainEntryPoint(host);
    return plugin;
}
