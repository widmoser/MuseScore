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

#ifndef __VSTGUI_H__
#define __VSTGUI_H__

#include "synthesizer/synthesizergui.h"
#include "ui_vst_gui.h"
#include "vst.h"
#include "vst/lib/host/PluginRegistry.h"
#include <QDialogButtonBox>

//---------------------------------------------------------
//   VstListDialog
//---------------------------------------------------------

class PluginListDialog : public QDialog {
Q_OBJECT
    int _idx = -1;
    std::vector<PluginRegistryEntry> selectedPlugins;
    PluginRegistry &pluginRegistry;
    QListWidget *list;
    QDialogButtonBox *buttonBox;
    QPushButton *okButton;
    QPushButton *cancelButton;
    QPushButton *rescanButton;

private slots:

    void okClicked();

    void cancelClicked();

    void rescanClicked();

public:
    PluginListDialog(PluginRegistry &pluginRegistry, QWidget *parent = 0);

    std::vector<PluginRegistryEntry> &getSelectedPlugins() { return selectedPlugins; }

    void add(const PluginRegistryEntry &plugin);
};

//---------------------------------------------------------
//   VstSynthesizerGui
//---------------------------------------------------------

class VstSynthesizerGui : public Ms::SynthesizerGui, Ui::VstGui {
Q_OBJECT
    PluginRegistry &pluginRegistry;
    AudioHost& pluginHost;
    SinglePluginGraph& processor;

private slots:

    void soundFontUpClicked();

    void soundFontDownClicked();

    void soundFontAddClicked();

    void soundFontDeleteClicked();

    void updateButtons();

    void itemDoubleClicked(QListWidgetItem* item);

public slots:

    virtual void synthesizerChanged();

public:
    VstSynthesizerGui(Ms::Synthesizer *synthesizer, PluginRegistry &pluginRegistry, AudioHost& pluginHost, SinglePluginGraph& processor);

    VstSynthesizer *vstSynthesizer() { return static_cast<VstSynthesizer *>(synthesizer()); }
};

#endif

