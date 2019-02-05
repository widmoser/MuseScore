//
// Created by Hannes Widmoser on 24.12.17.
//

#include "QPluginView.h"

QPluginView::QPluginView(QWidget* parent, Qt::WindowFlags flags)
    : QWidget(parent, flags) {
}

void QPluginView::update() {
    QWidget::update();
}

void QPluginView::setPosition(int left, int top) {
    move(left, top);
}

void QPluginView::setSize(int width, int height) {
    setFixedSize(width, height);
}

void* QPluginView::getNativeWindowHandle() {
    return (void*) winId();
}
