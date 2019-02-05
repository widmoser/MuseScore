cmake_minimum_required(VERSION 3.8)
project(PresetManager)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        main.cpp
        MainWindow.cpp
        PluginFrame.cpp
        resources.qrc)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
find_package(Qt5Widgets REQUIRED)

add_executable(PresetManager ${SOURCE_FILES} ${CompiledResources})
target_link_libraries(PresetManager
        oilib
        oi_portaudio
        oi_rtmidi
        binding_host_vst
        binding_qt
        Qt5::Widgets)