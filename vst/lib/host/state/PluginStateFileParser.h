//
// Created by Hannes Widmoser on 13/09/15.
//

#ifndef ORCHESTRALINTERFACECMAKE_PSXMLFILEPARSER_H
#define ORCHESTRALINTERFACECMAKE_PSXMLFILEPARSER_H

#include <vst/lib/host/PluginRegistry.h>

class PluginStateFileParser {
public:
    AudioPlugin* read(AudioHost& host, const PluginRegistry& registry, std::istream& input) const;
    AudioPlugin* load(AudioHost& host, const PluginRegistry& registry, const std::string& filePath) const;

    void write(const AudioPlugin* plugin, std::ostream& output) const;
    void save(const AudioPlugin* plugin, const std::string& filePath) const;
};

#endif //ORCHESTRALINTERFACECMAKE_PSXMLFILEPARSER_H
