//
// Created by Hannes Widmoser on 13/09/15.
//

#include <vst/third_party/pugixml/src/pugixml.hpp>
#include <vst/third_party/libb64/include/b64/encode.h>
#include <fstream>

#include "PluginStateFileParser.h"

AudioPlugin* PluginStateFileParser::read(AudioHost& host,
                                         const PluginRegistry& registry,
                                         std::istream& input) const {
//    input.seekg(std::ios::end);
//    auto size = input.tellg();
//    input.seekg(0);
//
//    auto bytes = new char[size];
//    input.read(bytes, size);
//
//    Data data;
//    data.copyFrom(bytes, size);
//
//    return new ChunkState(data, true, 1349793133);
    using namespace pugi;

    xml_document doc;
    doc.load(input);

    xml_node pluginElement = doc.document_element();
    int pluginId = pluginElement.attribute("plugin").as_int(0);

    const PluginRegistryEntry& entry = registry.getPluginInfo(pluginId);
    AudioPlugin* plugin = host.open(entry.path);

    plugin->setCurrentProgram(pluginElement.attribute("currentProgram").as_int(0));

    if (plugin->usesChunks()) {
        xml_node chunkElement = pluginElement.child("chunk");
        bool isPreset = chunkElement.attribute("isPreset").as_bool(false);
        xml_text text = chunkElement.text();
        const char* ch = text.get();
        Data d;
        d.copyFromBase64(std::string(ch));
        plugin->setChunkData(d, isPreset);
    }

    xml_node parametersElement = pluginElement.child("parameters");
    auto children = parametersElement.children();
    int index = 0;
    for (xml_node parameterElement : children) {
        plugin->setParameter(index++, parameterElement.attribute("value").as_float(0.0f));
    }

    return plugin;
}

void PluginStateFileParser::write(const AudioPlugin* plugin, std::ostream& output) const {
//    auto chunkState = dynamic_cast<const ChunkState*>(state);
//    output.write((const char*) chunkState->getChunk().getData(), chunkState->getChunk().getSize());

    using namespace pugi;

    xml_document doc;
    xml_node pluginElement = doc.append_child("state");

    pluginElement.append_attribute("plugin").set_value(plugin->getUID());
    pluginElement.append_attribute("currentProgram").set_value(plugin->getCurrentProgram());

    if (plugin->usesChunks()) {
        xml_node chunkElement = pluginElement.append_child("chunk");
        chunkElement.append_attribute("isPreset").set_value(true);
        base64::encoder e;
        Data chunk;
        plugin->getChunkData(chunk, true);
        std::string decoded((char*) chunk.getData(), chunk.getSize());
        std::stringstream decodedStream(decoded);
        std::stringstream encodedStream;
        e.encode(decodedStream, encodedStream);

        xml_text text = chunkElement.text();
        text.set(encodedStream.str().c_str());
    }

    xml_node parametersElement = pluginElement.append_child("parameters");
    for (int i = 0; i < plugin->getNumParameters(); ++i) {
        xml_node parameterElement = parametersElement.append_child("parameter");
        parameterElement.append_attribute("name").set_value(plugin->getParameterName(i).c_str());
        parameterElement.append_attribute("value").set_value(plugin->getParameter(i));
    }

    doc.save(output);
}

AudioPlugin* PluginStateFileParser::load(AudioHost& host,
                                         const PluginRegistry& registry,
                                         const std::string& filePath) const {
    std::ifstream input(filePath);
    AudioPlugin* result = read(host, registry, input);
    input.close();
    return result;
}

void PluginStateFileParser::save(const AudioPlugin* state, const std::string& filePath) const {
    std::ofstream output(filePath);
    write(state, output);
    output.close();
}
