//
// Created by Hannes Widmoser on 16/09/15.
//

#include <iostream>
#include <sys/stat.h>
#include <vst/third_party/pugixml/src/pugixml.hpp>
#include <host/exception/PluginInitializationException.h>
#include <QDebug>

#include "PluginRegistry.h"

using namespace pugi;

static const char* CacheFileName = "oipluginregistry.xml";

PluginRegistry::PluginRegistry(AudioHost& host)
    : host(host) {
    uidWhiteList.insert(1195463233); // Aria Player VST
    uidWhiteList.insert(1315524405); // Kontakt 5
    uidWhiteList.insert(1886151033); // Play
    uidWhiteList.insert(1349793133); // Pianoteq
    fileNameBlackList.insert("play_VST_x64.dll");
//    uidWhiteList.insert(1869180532); // OrchestralInterface
}

void PluginRegistry::load(Progress* progress) {
//    if (hasFile()) {
//        loadFromFile();
//    }
    scan(progress);
    saveToFile();
}

const PluginRegistryEntry& PluginRegistry::getPluginInfo(int uid) const {
    return uid2file.at(uid);
}

const PluginRegistryEntry& PluginRegistry::getPluginInfo(const QFileInfo& path) const {
    return file2uid.at(path.absoluteFilePath());
}

const std::vector<PluginRegistryEntry> PluginRegistry::getPluginInfos() const {
    // TODO: avoid copying
    std::vector<PluginRegistryEntry> plugins;
    for (const auto& entry : uid2file) {
        plugins.push_back(entry.second);
    }
    return plugins;
}

void PluginRegistry::scan(Progress* progress) {
    std::vector<QFileInfo> pathsToDelete;
    for (const auto& entry : file2uid) {
        pathsToDelete.push_back(entry.first);
    }

    for (const auto& searchPath : host.getDefaultPluginSearchPaths()) {
        QDir searchPathDir(QString::fromStdString(searchPath));
        if (searchPathDir.exists()) {
            scan(searchPathDir, pathsToDelete, progress);
        }
    }

    if (pathsToDelete.size() > 0) {
        // the cache contained paths that were not present during scanning: delete from cache:
        for (const auto& pathToDelete : pathsToDelete) {
            uid2file.erase(file2uid[pathToDelete.absoluteFilePath()].uid);
            file2uid.erase(pathToDelete.absoluteFilePath());
        }
    }
}

void PluginRegistry::scan(const QDir& dir,
                          std::vector<QFileInfo>& pathsToDelete,
                          Progress* progress) {
    std::cerr << "Scanning Dir: " << dir.absolutePath().toStdString() << std::endl;
    for (const auto& directoryEntry : dir.entryInfoList(QDir::Files)) {
        if (fileNameBlackList.find(directoryEntry.fileName()) != fileNameBlackList.end()) {
            qInfo() << "Ignoring " << directoryEntry.absoluteFilePath() << " due to blacklist";
            continue;
        }

        const auto& path = directoryEntry.absoluteFilePath();
        std::cerr << "File: " << path.toStdString() << std::endl;
        pathsToDelete.erase(std::remove(pathsToDelete.begin(), pathsToDelete.end(), path), pathsToDelete.end());

        if (file2uid.find(directoryEntry.absoluteFilePath()) == file2uid.end()) {
            try {
                PluginRegistryEntry entry;

                std::stringstream s;
                s << "Scanning " << path.toStdString() << "...";
                if (progress != nullptr) {
                    progress->message(s.str());
                }
;
                getInfo(path, entry);
                addEntry(entry);
            } catch (PluginInitializationException& e) {
                qWarning() << "Failed to load plugin from " << e.path.absoluteFilePath() << ": " << e.message;
            }
        }
    }
}

void PluginRegistry::loadFromFile() {
    xml_document document;
    document.load_file(CacheFileName);
    xml_node docElement = document.document_element();
    xml_object_range<xml_node_iterator> pluginElements = docElement.children();
    for (xml_node_iterator i = pluginElements.begin(); i != pluginElements.end(); ++i) {
        PluginRegistryEntry e;
        e.uid = i->attribute("uid").as_int(0);
//        e.path = i->attribute("path").as_string();
        e.productName = i->attribute("productName").as_string("");
        e.vendorName = i->attribute("vendorName").as_string("");
        e.vendorVersion = i->attribute("vendorVersion").as_int(0);
        addEntry(e);
    }
}

bool PluginRegistry::hasFile() {
    struct stat buffer;
    return (stat(CacheFileName, &buffer) == 0);
}

void PluginRegistry::saveToFile() {
    xml_document document;
    xml_node docElement = document.append_child("registry");
    for (const auto& file : file2uid) {
        const PluginRegistryEntry& entry = file.second;
        xml_node e = docElement.append_child("plugin");
        e.append_attribute("uid").set_value(entry.uid);
        e.append_attribute("path").set_value(entry.path.absoluteFilePath().toStdString().c_str());
        e.append_attribute("productName").set_value(entry.productName.c_str());
        e.append_attribute("vendorName").set_value(entry.vendorName.c_str());
        e.append_attribute("vendorVersion").set_value(entry.vendorVersion);
    }
    document.save_file(CacheFileName);
}

PluginRegistryEntry PluginRegistry::getInfo(const QFileInfo& filepath, PluginRegistryEntry& result) const {
    AudioPlugin* plugin = host.open(filepath);
    result.uid = plugin->getUID();
    result.path = filepath;
    result.productName = plugin->getProductName();
    result.vendorName = plugin->getVendorName();
    result.vendorVersion = plugin->getVendorVersion();
    delete plugin;
    return result;
}

void PluginRegistry::addEntry(PluginRegistryEntry& e) {
    file2uid[e.path.absoluteFilePath()] = e;
    uid2file[e.uid] = e;
//    if (uidWhiteList.find(e.uid) != uidWhiteList.end()) {
//        uid2file[e.uid] = e;
//    } else {
//        std::cout << "Ignoring plugin " << e.productName << " because its id " << e.uid << " is not whitelisted"
//                  << std::endl;
//    }
}
