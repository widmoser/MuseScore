//
// Created by Hannes Widmoser on 03/09/15.
//

#include <stdio.h>
#include <bindings/vst/vst.h>

#include "VSTModuleOSX.h"

VSTModuleOSX::VSTModuleOSX(const std::string pluginPath) : VSTModule(pluginPath) {
}

VSTModuleOSX::~VSTModuleOSX() {
    CFBundleUnloadExecutable(bundle);
    CFRelease(bundle);
}

AEffect* VSTModuleOSX::open(audioMasterCallback host) throw(PluginInitializationException) {
    AEffect* plugin = NULL;

    // Create a path to the bundle
    CFStringRef pluginPathStringRef = CFStringCreateWithCString(NULL, getPluginPath().c_str(), kCFStringEncodingASCII);
    CFURLRef bundleUrl = CFURLCreateWithFileSystemPath(kCFAllocatorDefault, pluginPathStringRef, kCFURLPOSIXPathStyle,
                                                       true);
    if (bundleUrl == NULL) {
        throw PluginInitializationException(getPluginPath(), "Couldn't make URL reference for plugin");
    }

    // Open the bundle
    bundle = CFBundleCreate(kCFAllocatorDefault, bundleUrl);
    if (bundle == NULL) {
        CFRelease(pluginPathStringRef);
        CFRelease(bundleUrl);
        throw PluginInitializationException(getPluginPath(), "Couldn't create bundle reference");
    }

    vstPluginFuncPtr mainEntryPoint = NULL;
    mainEntryPoint = (vstPluginFuncPtr) CFBundleGetFunctionPointerForName(bundle,
                                                                          CFSTR("VSTPluginMain"));
    // VST plugins previous to the 2.4 SDK used main_macho for the entry point name
    if (mainEntryPoint == NULL) {
        mainEntryPoint = (vstPluginFuncPtr) CFBundleGetFunctionPointerForName(bundle,
                                                                              CFSTR("main_macho"));
    }

    if (mainEntryPoint == NULL) {
        CFBundleUnloadExecutable(bundle);
        CFRelease(bundle);
        throw PluginInitializationException(getPluginPath(), "Couldn't get a pointer to plugin's main()");
    }

    plugin = mainEntryPoint(host);
    if (plugin == NULL) {
        CFBundleUnloadExecutable(bundle);
        CFRelease(bundle);
        throw PluginInitializationException(getPluginPath(), "Plugin's main() returns null");
    }

    // Clean up
    CFRelease(pluginPathStringRef);
    CFRelease(bundleUrl);

    return plugin;
}
