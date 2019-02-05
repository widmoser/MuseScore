//
// Created by Hannes Widmoser on 16/07/2017.
//

#include "QtSplashScreenProgress.h"

QtSplashScreenProgress::QtSplashScreenProgress(QApplication& app, QSplashScreen& splashScreen) : app(app), splashScreen(splashScreen) {

}

void QtSplashScreenProgress::message(const std::string& message) const {
    splashScreen.showMessage(QString::fromStdString(message), Qt::AlignBottom | Qt::AlignHCenter, Qt::white);
    app.processEvents();
}

void QtSplashScreenProgress::percent(float value) const {
    // ignored
}