project(ui)
# Version Number
set(OI_VERSION_MAJOR 0)
set(OI_VERSION_MINOR 1)

set(SOURCE_FILES
        QEditor.cpp
        QPluginView.cpp
        QProgress.cpp
        QtTimerFactory.cpp
        QtSplashScreenProgress.cpp)

find_package(Qt5Widgets REQUIRED)

add_library(binding_qt ${SOURCE_FILES})
target_link_libraries(binding_qt Qt5::Widgets)