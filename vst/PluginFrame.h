//
// Created by Hannes Widmoser on 16/07/2017.
//

#ifndef ORCHESTRALINTERFACECMAKE_PLUGINFRAME_H
#define ORCHESTRALINTERFACECMAKE_PLUGINFRAME_H

#include <QtWidgets>
#include <vst/lib/plugin/AudioPlugin.h>
#include <vst/lib/host/graph/SinglePluginGraph.h>
#include <vst/lib/host/PluginView.h>
#include <vst/bindings/qt/QPluginView.h>
#include <vst/lib/host/state/PluginStateFileParser.h>

class PluginFrame : public QWidget {
public:
    PluginFrame(QWidget* parent, AudioPlugin* plugin);
private slots:
    void savePreset();
private:
    void showEvent(QShowEvent* event) override;
    void closeEvent(QCloseEvent* event) override;
    bool event(QEvent* event) override;

    PluginStateFileParser stateParser;
    QWidget* pluginView;
    Editor* pluginEditor;
    std::unique_ptr<AudioPlugin> plugin;
};

#endif //ORCHESTRALINTERFACECMAKE_PLUGINFRAME_H
