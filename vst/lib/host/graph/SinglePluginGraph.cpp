//
// Created by Hannes Widmoser on 11/09/15.
//

#include "SinglePluginGraph.h"

SinglePluginGraph::SinglePluginGraph(AudioPlugin* plugin) :
    plugin(plugin), isStarted(false), isResumed(false) {

}

void SinglePluginGraph::processAudio(AudioSampleBuffer& output) {
    if (plugin != nullptr) {
        plugin->processAudio(output);
    } else {
        output.clear();
    }
}

void SinglePluginGraph::onMidiEvent(std::shared_ptr<const MidiMessage> message) {
    if (plugin != nullptr) {
        plugin->onMidiEvent(message);
    }
}

AudioPlugin* SinglePluginGraph::getPlugin() {
    return plugin;
}

void SinglePluginGraph::setPlugin(AudioPlugin* plugin) {
    AudioPlugin* oldPlugin = this->plugin;
    this->plugin = nullptr; // don't call process audio on the plugin while changing
    // stop old plugin:
    if (oldPlugin != nullptr) {
        oldPlugin->suspend();
    }
    // set new plugin:
    this->plugin = plugin;
    if (this->plugin != nullptr) {
        if (isStarted) {
            this->plugin->start();
        }
        if (isResumed) {
            this->plugin->resume();
        }
    }
}

void SinglePluginGraph::start() {
    isStarted = true;
    if (plugin != nullptr) {
        plugin->start();
    }
}

void SinglePluginGraph::stop() {
    isStarted = false;
    if (plugin != nullptr) {
        plugin->stop();
    }
}

void SinglePluginGraph::resume() {
    isResumed = true;
    if (plugin != nullptr) {
        plugin->resume();
    }
}

void SinglePluginGraph::suspend() {
    isResumed = false;
    if (plugin != nullptr) {
        plugin->suspend();
    }
}
