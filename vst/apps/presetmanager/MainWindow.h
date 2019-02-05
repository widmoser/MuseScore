//
// Created by Hannes Widmoser on 14/07/2017.
//

#ifndef ORCHESTRALINTERFACECMAKE_MAINWINDOW_H
#define ORCHESTRALINTERFACECMAKE_MAINWINDOW_H

#include <QtWidgets>
#include <vst/bindings/vst/VstAudioHost.h>
#include <vst/lib/midi/MidiSource.h>
#include <vst/lib/host/graph/SinglePluginGraph.h>
#include <vst/lib/audio/AudioPlayer.h>
#include <vst/lib/host/PluginRegistry.h>
#include <vst/lib/host/state/PluginStateFileParser.h>

class MainWindow : public QMainWindow {
public:
    MainWindow(AudioHost& host, AudioPlayer& player, PluginRegistry& registry, MidiSource& midiSource);
public slots:
    void onPluginDoubleClicked(QTreeWidgetItem* item, int column);
    void onOpenPreset();
private:
    void closeEvent(QCloseEvent* event) override;
    AudioPlugin* openPlugin(const PluginRegistryEntry& entry);
    void openPreset(const std::string path);

    AudioHost& host;
    AudioPlayer& player;
    PluginRegistry& registry;

    PluginStateFileParser stateParser;
    SinglePluginGraph graph;
};

#endif //ORCHESTRALINTERFACECMAKE_MAINWINDOW_H
