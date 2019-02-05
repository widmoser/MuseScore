//
// Created by Hannes Widmoser on 30.12.17.
//

#ifndef ORCHESTRALINTERFACECMAKE_VSTEFFECTPROXY_H
#define ORCHESTRALINTERFACECMAKE_VSTEFFECTPROXY_H

#include <aeffect.h>

class VstEffectProxy {
public:
    explicit VstEffectProxy(AEffect* effect);
protected:
    VstIntPtr dispatcher(VstInt32 opCode, VstInt32 index, VstInt32 value, void* ptr, float opt) const;
    AEffect* effect;
};

#endif //ORCHESTRALINTERFACECMAKE_VSTEFFECTPROXY_H
