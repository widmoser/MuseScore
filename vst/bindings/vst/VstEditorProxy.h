//
// Created by Hannes Widmoser on 30.12.17.
//

#ifndef ORCHESTRALINTERFACECMAKE_VSTEDITORPROXY_H
#define ORCHESTRALINTERFACECMAKE_VSTEDITORPROXY_H

#include <aeffect.h>
#include <vst/lib/plugin/Editor.h>
#include "VstEffectProxy.h"

class VstEditorProxy : public Editor, public VstEffectProxy {
public:
    explicit VstEditorProxy(AEffect* vstEffect);

    const lib::Rect getBounds() const override;
    void update() override;
    void open(void* nativeParentWindowHandle) override;
    void close() override;
};

#endif //ORCHESTRALINTERFACECMAKE_VSTEDITORPROXY_H
