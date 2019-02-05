//
// Created by Hannes Widmoser on 30.12.17.
//

#include "VstEditorProxy.h"

VstEditorProxy::VstEditorProxy(AEffect* effect)
    : VstEffectProxy(effect) {
}

const lib::Rect VstEditorProxy::getBounds() const {
    ERect* rect = nullptr;
    dispatcher(effEditGetRect, 0, 0, &rect, 0);
    return lib::Rect(rect->left, rect->top, rect->right, rect->bottom);
}

void VstEditorProxy::update() {
    dispatcher(effEditIdle, 0, 0, 0, 0);
}

void VstEditorProxy::open(void* nativeParentWindowHandle) {
    dispatcher(effEditOpen, 0, 0, nativeParentWindowHandle, 0);
    dispatcher(effGetProgram, 0, 0, 0, 0); // also in steinberg code
}

void VstEditorProxy::close() {
    dispatcher(effEditClose, 0, 0, 0, 0);
}
