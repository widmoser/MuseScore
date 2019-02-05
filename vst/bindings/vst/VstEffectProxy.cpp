//
// Created by Hannes Widmoser on 30.12.17.
//

#include "VstEffectProxy.h"

VstEffectProxy::VstEffectProxy(AEffect* effect)
    : effect(effect) {
}

VstIntPtr VstEffectProxy::dispatcher(VstInt32 opCode, VstInt32 index, VstInt32 value, void* ptr, float opt) const {
    return effect->dispatcher(effect, opCode, index, value, ptr, opt);
}
