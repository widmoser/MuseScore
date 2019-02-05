//
// Created by Hannes Widmoser on 14/07/2017.
//
#include <PluginFrame.h>

#include "MainWindow.h"

MainWindow::MainWindow(AudioHost& host, AudioPlayer& player, PluginRegistry& registry, MidiSource& midiSource)
    : host(host), player(player),
      registry(registry) {
    auto menuBar = new QMenuBar();
    QMenu* fileMenu = menuBar->addMenu("&File");

    QAction* openPreset = new QAction(tr("&Open Preset"), this);
    openPreset->setShortcuts(QKeySequence::Open);
    openPreset->setStatusTip(tr("Open a preset"));
    connect(openPreset, &QAction::triggered, this, &MainWindow::onOpenPreset);
    fileMenu->addAction(openPreset);

    // TODO: add quit action

    setMenuBar(menuBar);

    auto listView = new QTreeWidget(this);
    listView->setColumnCount(5);
    QStringList headerLabels;
    headerLabels.push_back("Vendor");
    headerLabels.push_back("Product");
    headerLabels.push_back("Vendor Version");
    headerLabels.push_back("UID");
    headerLabels.push_back("Path");
    listView->setHeaderLabels(headerLabels);
    QList<QTreeWidgetItem*> items;
    for (const auto& entry: registry.getPluginInfos()) {
        QStringList columns;
        columns.push_back(QString::fromStdString(entry.vendorName));
        columns.push_back(QString::fromStdString(entry.productName));
        columns.push_back(QString::fromStdString(std::to_string(entry.vendorVersion)));
        columns.push_back(QString::fromStdString(std::to_string(entry.uid)));
        columns.push_back(QString::fromStdString(entry.path));
        items.push_back(new QTreeWidgetItem(listView, columns));
    }
    listView->insertTopLevelItems(0, items);
    for (int i = 0; i < listView->columnCount(); ++i) {
        listView->resizeColumnToContents(i);
    }

    connect(listView, &QTreeWidget::itemDoubleClicked, this, &MainWindow::onPluginDoubleClicked);

    setCentralWidget(listView);
    setFixedSize(640, 480);

    midiSource.addListener(&graph);
    player.setProcessor(&graph);
    player.start();
    player.resume();
}

void MainWindow::closeEvent(QCloseEvent* event) {
    player.suspend();
    player.stop();
}

void MainWindow::onPluginDoubleClicked(QTreeWidgetItem* item, int column) {
    int uid = item->data(3, Qt::DisplayRole).toString().toInt();
    const PluginRegistryEntry& entry = registry.getPluginInfo(uid);
    openPlugin(entry);
}

AudioPlugin* MainWindow::openPlugin(const PluginRegistryEntry& e) {
    AudioPlugin* audioPlugin = host.open(e.path);
    audioPlugin->start();
    PluginFrame* pluginFrame = new PluginFrame(this, audioPlugin, graph);
    pluginFrame->show();
    return audioPlugin;
}

void MainWindow::onOpenPreset() {
    QString fileName = QFileDialog::getOpenFileName(
        this,
        tr("Open Preset"), "",
        tr("Preset (*.preset);;All Files (*)"));
    openPreset(fileName.toStdString());
}

void MainWindow::openPreset(const std::string path) {
    AudioPlugin* audioPlugin = stateParser.load(host, registry, path);
    PluginFrame* pluginFrame = new PluginFrame(this, audioPlugin, graph);
    pluginFrame->show();
}

