//
// Created by Hannes Widmoser on 16/07/2017.
//

#include <fstream>
#include <iostream>
#include "PluginFrame.h"

PluginFrame::PluginFrame(QWidget* parent, AudioPlugin* plugin)
    : QWidget(parent, Qt::Window), plugin(plugin) {
    auto layout = new QVBoxLayout();

    auto menuBar = new QMenuBar(this);
    QMenu* fileMenu = menuBar->addMenu("&Plugin");

    QAction* savePreset = new QAction(tr("&Save Preset"), this);
    savePreset->setShortcuts(QKeySequence::Save);
    savePreset->setStatusTip(tr("Save the preset"));
    connect(savePreset, &QAction::triggered, this, &PluginFrame::savePreset);
    fileMenu->addAction(savePreset);

    pluginView = new QWidget(this);
    layout->addWidget(pluginView);
    layout->setMenuBar(menuBar);

    layout->setMargin(0);
    setLayout(layout);

    std::cerr << plugin->getCurrentProgramName() << std::endl;
    for (int i = 0; i < plugin->getNumParameters(); ++i) {
        std::cerr << plugin->getParameterName(i) << std::endl;
    }
    std::cerr << "Uses chunks: " << plugin->usesChunks() << std::endl;
}

void PluginFrame::showEvent(QShowEvent* event) {
    pluginEditor = plugin->getEditor();
    lib::Rect bounds = pluginEditor->getBounds();
    pluginView->move(bounds.left, bounds.top);
    pluginView->setFixedSize(bounds.width(), bounds.height());
    pluginEditor->open((void*) pluginView->winId());
    pluginEditor->update();
    adjustSize();
}

void PluginFrame::closeEvent(QCloseEvent* event) {
//    graph.setPlugin(nullptr);
    pluginEditor->close();
}

bool PluginFrame::event(QEvent* event) {
//    if (event->type() == QEvent::WindowActivate && isActiveWindow()) {
//        graph.setPlugin(plugin.get());
//    }
    return QWidget::event(event);
}

void PluginFrame::savePreset() {
    QString
        fileName = QFileDialog::getSaveFileName(this, tr("Save Preset"), "", tr("Preset (*.preset);;All Files (*)"));
    stateParser.save(plugin.get(), fileName.toStdString());
}


