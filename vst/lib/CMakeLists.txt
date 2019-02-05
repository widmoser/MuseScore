cmake_minimum_required(VERSION 3.8)
# version 3.8 is required for boost 1.64
project(OrchestralInterfaceCMake)
# Version Number
set(OI_VERSION_MAJOR 0)
set(OI_VERSION_MINOR 1)

#set(Boost_USE_STATIC_LIBS ON)
#find_package(Boost 1.64 REQUIRED filesystem)

set(SOURCE_FILES
        audio/AudioPlayer.cpp
        audio/AudioSampleBuffer.cpp
        host/AudioHost.cpp
        host/PluginRegistry.cpp
        host/exception/PluginInitializationException.cpp
        host/graph/AudioGraph.cpp
        host/graph/SinglePluginGraph.cpp
        host/state/PluginStateFileParser.cpp
        midi/MidiMessage.cpp
        midi/MidiMessageBuffer.cpp
        midi/MidiSource.cpp
        plugin/BaseAudioPlugin.cpp
        util/Data.cpp)


add_library(oilib ${SOURCE_FILES})
target_link_libraries(oilib pugixml base64 ${Boost_LIBRARIES})

target_include_directories(oilib PUBLIC ${Boost_INCLUDE_DIRS})