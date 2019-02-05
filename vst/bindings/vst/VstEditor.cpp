//
// Created by Hannes Widmoser on 30.12.17.
//

#include "VstEditor.h"

VstEditor::VstEditor(const AudioPlugin* pluginImplementation)
    : implementation(pluginImplementation->getEditor()) {
}

bool VstEditor::getRect(ERect** rect) {
    *rect = new ERect();
    if (implementation != nullptr) {
        const lib::Rect bounds = implementation->getBounds();
        (*rect)->left = bounds.left;
        (*rect)->top = bounds.top;
        (*rect)->right = bounds.right;
        (*rect)->bottom = bounds.bottom;
    } else {
        (*rect)->left = 0;
        (*rect)->top = 0;
        (*rect)->right = 640;
        (*rect)->bottom = 480;
    }
    return true;
}

bool VstEditor::open(void* ptr) {
    AEffEditor::open(ptr);
    if (implementation != nullptr) {
        implementation->open(ptr);
    }
    return true;
}

void VstEditor::close() {
    if (implementation != nullptr) {
        implementation->close();
        implementation = nullptr;
    }
    AEffEditor::close();
}
