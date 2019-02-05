//=============================================================================
//  Zerberus
//  Zample player
//
//  Copyright (C) 2013 Werner Schweer
//
//  This program is free software; you can redistribute it and/or modify
//  it under the terms of the GNU General Public License version 2
//  as published by the Free Software Foundation and appearing in
//  the file LICENCE.GPL
//=============================================================================

#include <lib/host/PluginRegistry.h>
#include "vst/PluginFrame.h"
#include "vstgui.h"

#include "mscore/preferences.h"
#include "mscore/extension.h"

//---------------------------------------------------------
//   SfzListDialog
//---------------------------------------------------------

PluginListDialog::PluginListDialog(PluginRegistry &pluginRegistry, QWidget *parent)
        : QDialog(parent), pluginRegistry(pluginRegistry) {
    setWindowTitle(tr("VST Plugins"));
    setWindowFlags(this->windowFlags() & ~Qt::WindowContextHelpButtonHint);
    list = new QListWidget;
    list->setSelectionMode(QAbstractItemView::ExtendedSelection);

    okButton = new QPushButton;
    cancelButton = new QPushButton;
    rescanButton = new QPushButton;
    okButton->setText(tr("Load"));
    cancelButton->setText(tr("Cancel"));
    rescanButton->setText(tr("Rescan"));

    QVBoxLayout *layout = new QVBoxLayout;
    buttonBox = new QDialogButtonBox;
    layout->addWidget(list);
    layout->addWidget(buttonBox);
    buttonBox->addButton(okButton, QDialogButtonBox::AcceptRole);
    buttonBox->addButton(cancelButton, QDialogButtonBox::RejectRole);
    buttonBox->addButton(rescanButton, QDialogButtonBox::ActionRole);
    setLayout(layout);
    connect(okButton, SIGNAL(clicked()), SLOT(okClicked()));
    connect(cancelButton, SIGNAL(clicked()), SLOT(cancelClicked()));
    connect(rescanButton, SIGNAL(clicked()), SLOT(rescanClicked()));
    connect(list, SIGNAL(itemDoubleClicked(QListWidgetItem * )), this, SLOT(itemDoubleClicked(QListWidgetItem * )));

}

//---------------------------------------------------------
//   add
//---------------------------------------------------------

void PluginListDialog::add(const PluginRegistryEntry &plugin) {
    QListWidgetItem *item = new QListWidgetItem;
    item->setText(QString::fromStdString(plugin.productName));
    item->setData(Qt::UserRole, plugin.uid);
    list->addItem(item);
}

//---------------------------------------------------------
//   okClicked
//---------------------------------------------------------

void PluginListDialog::okClicked() {
    for (auto item : list->selectedItems()) {
        selectedPlugins.push_back(pluginRegistry.getPluginInfo(item->data(Qt::UserRole).toString().toInt()));
    }
    accept();
}

//---------------------------------------------------------
//   cancelClicked
//---------------------------------------------------------

void PluginListDialog::cancelClicked() {
    reject();
}

//---------------------------------------------------------
//   rescanClicked
//---------------------------------------------------------

void PluginListDialog::rescanClicked() {
    pluginRegistry.load(nullptr);
    list->clear();
    for (auto &plugin : pluginRegistry.getPluginInfos()) {
        add(plugin);
    }
}

//---------------------------------------------------------
//   gui
//---------------------------------------------------------

Ms::SynthesizerGui *VstSynthesizer::gui() {
    if (_gui == 0)
        _gui = new VstSynthesizerGui(this, this->pluginRegistry, this->audioHost, this->plugin);
    return _gui;
}

//---------------------------------------------------------
//   VstSynthesizerGui
//---------------------------------------------------------

VstSynthesizerGui::VstSynthesizerGui(Ms::Synthesizer *s, PluginRegistry &pluginRegistry, AudioHost &pluginHost,
                                     SinglePluginGraph &processor)
        : SynthesizerGui(s), pluginRegistry(pluginRegistry), pluginHost(pluginHost), processor(processor) {
    setupUi(this);
    connect(soundFontUp, SIGNAL(clicked()), SLOT(soundFontUpClicked()));
    connect(soundFontDown, SIGNAL(clicked()), SLOT(soundFontDownClicked()));
    connect(soundFontAdd, SIGNAL(clicked()), SLOT(soundFontAddClicked()));
    connect(soundFontDelete, SIGNAL(clicked()), SLOT(soundFontDeleteClicked()));
    connect(files, SIGNAL(itemSelectionChanged()), this, SLOT(updateButtons()));
    connect(files, SIGNAL(itemDoubleClicked(QListWidgetItem * )), this, SLOT(itemDoubleClicked(QListWidgetItem * )));
    updateButtons();
}

//---------------------------------------------------------
//   soundFontUpClicked
//---------------------------------------------------------

void VstSynthesizerGui::soundFontUpClicked() {
}

//---------------------------------------------------------
//   soundFontDownClicked
//---------------------------------------------------------

void VstSynthesizerGui::soundFontDownClicked() {
}

//---------------------------------------------------------
//   addClicked
//---------------------------------------------------------

void VstSynthesizerGui::soundFontAddClicked() {
    PluginListDialog pluginListDialog(pluginRegistry, this);
    if (!pluginListDialog.exec())
        return;

    for (auto &plugin : pluginListDialog.getSelectedPlugins()) {
        QListWidgetItem *item = new QListWidgetItem;
        item->setText(QString::fromStdString(plugin.productName));
        item->setData(Qt::UserRole, plugin.uid);
        files->addItem(item);
    }

    // TODO: Support multiple plugins.
    if (pluginListDialog.getSelectedPlugins().size() > 0) {
        PluginRegistryEntry& first = pluginListDialog.getSelectedPlugins().front();
        processor.setPlugin(pluginHost.open(first.path));
    }
}

//---------------------------------------------------------
//   updateButtons
//---------------------------------------------------------

void VstSynthesizerGui::updateButtons() {
}

void VstSynthesizerGui::itemDoubleClicked(QListWidgetItem *item) {
//    const PluginRegistryEntry &plugin = pluginRegistry.getPluginInfo(item->data(Qt::UserRole).toString().toInt());
//    AudioPlugin *audioPlugin = pluginHost.open(plugin.path);
////    audioPlugin->start();
    // TODO: Support multiple plugins.
    PluginFrame *pluginFrame = new PluginFrame(this, processor.getPlugin());
    pluginFrame->show();
}

//---------------------------------------------------------
//   removeClicked
//---------------------------------------------------------

void VstSynthesizerGui::soundFontDeleteClicked() {
}

//---------------------------------------------------------
//   synthesizerChanged
//---------------------------------------------------------

void VstSynthesizerGui::synthesizerChanged() {
}
