//
// Created by Hannes Widmoser on 30.12.17.
//

#ifndef ORCHESTRALINTERFACECMAKE_VSTEDITOR_H
#define ORCHESTRALINTERFACECMAKE_VSTEDITOR_H

#include <aeffeditor.h>
#include <lib/plugin/Editor.h>
#include "VSTAudioPlugin.h"

class VstEditor : public AEffEditor {
public:
    explicit VstEditor(const AudioPlugin* pluginImplementation);

    bool getRect(ERect** rect) override;
    bool open(void* ptr) override;
    void close() override;
private:
    Editor* implementation;
};

#endif //ORCHESTRALINTERFACECMAKE_VSTEDITOR_H
