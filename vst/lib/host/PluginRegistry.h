//
// Created by Hannes Widmoser on 16/09/15.
//

#ifndef ORCHESTRALINTERFACECMAKE_PLUGINREGISTRY_H
#define ORCHESTRALINTERFACECMAKE_PLUGINREGISTRY_H

#include <vector>
#include <string>
#include <map>
#include <unordered_set>
#include <vst/lib/host/AudioHost.h>
#include <vst/lib/util/progress/Progress.h>
#include <QtCore/QDir>
#include <set>

class PluginRegistryEntry {
public:
    QFileInfo path;
    int uid;
    int vendorVersion;
    QString vendorName;
    QString productName;
};

class PluginRegistry {
public:
    PluginRegistry(AudioHost& host);
    void init(Progress* progress = nullptr);
    void rescan(Progress* progress = nullptr);

    const PluginRegistryEntry& getPluginInfo(int uid) const;
    const PluginRegistryEntry& getPluginInfo(const QFileInfo& path) const;
    const std::vector<PluginRegistryEntry> getPluginInfos() const;
private:
    void scan(Progress* progress);
    void loadFromFile();
    bool hasFile();
    void saveToFile();

    void scan(const QDir& dir, std::vector<QFileInfo>& pathsToDelete, Progress* progress);

    void addEntry(PluginRegistryEntry& e);

    PluginRegistryEntry getInfo(const QFileInfo& filepath, PluginRegistryEntry& result) const;

    std::map<QString, PluginRegistryEntry> file2uid;
    std::map<int, PluginRegistryEntry> uid2file;

    std::unordered_set<int> uidWhiteList;
    std::set<QString> fileNameBlackList;

    AudioHost& host;
};


#endif //ORCHESTRALINTERFACECMAKE_PLUGINREGISTRY_H
