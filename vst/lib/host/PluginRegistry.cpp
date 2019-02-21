//
// Created by Hannes Widmoser on 16/09/15.
//

#include <QDebug>
#include <QString>
#include <QFile>
#include <QXmlStreamReader>
#include <iostream>
#include <sys/stat.h>
#include <host/exception/PluginInitializationException.h>

#include "PluginRegistry.h"

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

void PluginRegistry::init(Progress* progress) {
    if (hasFile()) {
        loadFromFile();
        return;
    }
    rescan(progress);
}

void PluginRegistry::rescan(Progress* progress) {
    if (hasFile()) {
        loadFromFile();
    }
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

namespace Ms {
    extern QString dataPath;
}

bool PluginRegistry::hasFile() {
    QFile f(Ms::dataPath + "/vstplugins.xml");
    return f.exists();
}

void PluginRegistry::loadFromFile() {
    QFile f(Ms::dataPath + "/vstplugins.xml");

    if (!f.exists()) {
        return;
    }

    QXmlStreamReader xmlReader(&f);
    if (xmlReader.readNextStartElement()) {
        while (xmlReader.readNextStartElement()) {
            PluginRegistryEntry e;
            auto attributes = xmlReader.attributes();
            e.uid = attributes.value("uid").toInt();
            e.path = QFileInfo(attributes.value("path").toString());
            e.productName = attributes.value("productName").toString();
            e.vendorName = attributes.value("vendorName").toString();
            e.vendorVersion = attributes.value("vendorVersion").toInt();
            addEntry(e);
        } // <plugin>
    } // <plugins>
}

void PluginRegistry::saveToFile() {
    QFile f(Ms::dataPath + "/vstplugins.xml");
    QXmlStreamWriter xmlWriter(&f);

    xmlWriter.writeStartDocument();
    xmlWriter.writeStartElement("plugins");

    for (const auto& file : file2uid) {
        const PluginRegistryEntry& entry = file.second;
        xmlWriter.writeStartElement("plugin");
        xmlWriter.writeAttribute("uid", QString(entry.uid));
        xmlWriter.writeAttribute("path", entry.path.absoluteFilePath());
        xmlWriter.writeAttribute("productName", entry.productName);
        xmlWriter.writeAttribute("vendorName", entry.vendorName);
        xmlWriter.writeAttribute("vendorVersion", QString(entry.vendorVersion));
        xmlWriter.writeEndElement();
    }

    xmlWriter.writeEndElement();
    xmlWriter.writeEndDocument();
}

PluginRegistryEntry PluginRegistry::getInfo(const QFileInfo& filepath, PluginRegistryEntry& result) const {
    AudioPlugin* plugin = host.open(filepath);
    result.uid = plugin->getUID();
    result.path = filepath;
    result.productName = QString::fromStdString(plugin->getProductName());
    result.vendorName = QString::fromStdString(plugin->getVendorName());
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
