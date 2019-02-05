//
// Created by Hannes Widmoser on 24.12.17.
//

#ifndef ORCHESTRALINTERFACECMAKE_QTPLUGINWINDOW_H
#define ORCHESTRALINTERFACECMAKE_QTPLUGINWINDOW_H

#include <QtWidgets>
#include <vst/lib/host/PluginView.h>

class QPluginView : public QWidget, public PluginView {
public:
    QPluginView(QWidget* parent, Qt::WindowFlags flags = Qt::WindowFlags());

    void update() override;
    void setPosition(int left, int top) override;
    void setSize(int width, int height) override;
    void* getNativeWindowHandle() override;
};

#endif //ORCHESTRALINTERFACECMAKE_QTPLUGINWINDOW_H
