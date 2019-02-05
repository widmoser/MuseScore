//
// Created by Hannes Widmoser on 30.12.17.
//

#ifndef ORCHESTRALINTERFACECMAKE_QEDITOR_H
#define ORCHESTRALINTERFACECMAKE_QEDITOR_H

#include <QtWidgets>
#include <vst/lib/plugin/Editor.h>

class QEditor : public Editor {
public:
    explicit QEditor(const lib::Rect bounds);
    const lib::Rect getBounds() const override;
    void update() override;
    void open(void* nativeParentWindowHandle) override;
    void close() override;
protected:
    virtual void onOpen(QWidget* parent) = 0;
private:
    lib::Rect bounds;
    QWidget* widget;
};

#endif //ORCHESTRALINTERFACECMAKE_QEDITOR_H
