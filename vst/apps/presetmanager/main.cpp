#include <QtWidgets>
#include <vst/bindings/portaudio/PortAudioPlayer.h>
#include <vst/bindings/qt/QtTimerFactory.h>
#include <vst/bindings/rtmidi/RtMidiInputSource.h>
#include <vst/bindings/qt/QtSplashScreenProgress.h>
#include <MainWindow.h>

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);

    QPixmap splashScreenImage(":/splash.jpg");
    QSplashScreen splashScreen(splashScreenImage);
    QtSplashScreenProgress progress(app, splashScreen);
    splashScreen.show();
    app.processEvents();

    QtTimerFactory timerFactory;
    VstAudioHost host(44100, 256, timerFactory);
    PortAudioPlayer player(44100, 256);
    PluginRegistry registry(host);
    RtMidiInputSource midiSource;

    registry.load(&progress);

    MainWindow mainWindow(host, player, registry, midiSource);
    mainWindow.show();
    splashScreen.finish(&mainWindow);

    return app.exec();
}
