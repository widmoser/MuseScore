//
// Created by Hannes Widmoser on 16/07/2017.
//

#ifndef ORCHESTRALINTERFACECMAKE_SPLASHSCREENPROGRESS_H
#define ORCHESTRALINTERFACECMAKE_SPLASHSCREENPROGRESS_H

#include <QtWidgets>
#include <vst/lib/util/progress/Progress.h>

class QtSplashScreenProgress : public Progress {
public:
    QtSplashScreenProgress(QApplication& app, QSplashScreen& splashScreen);
    virtual void message(const std::string& message) const;
    virtual void percent(float value) const;
private:
    QApplication& app;
    QSplashScreen& splashScreen;
};


#endif //ORCHESTRALINTERFACECMAKE_SPLASHSCREENPROGRESS_H
