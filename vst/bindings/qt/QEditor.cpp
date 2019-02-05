//
// Created by Hannes Widmoser on 30.12.17.
//

#include "QEditor.h"

QEditor::QEditor(const lib::Rect bounds) : bounds(bounds) {
}

const lib::Rect QEditor::getBounds() const {
    return bounds;
}

void QEditor::update() {
    widget->update();
}

void QEditor::open(void* nativeParentWindowHandle) {
    widget = QWidget::find((WId) nativeParentWindowHandle);
    widget->setFixedSize(bounds.width(), bounds.height());
    onOpen(widget);
}

void QEditor::close() {
    widget = nullptr;
}
