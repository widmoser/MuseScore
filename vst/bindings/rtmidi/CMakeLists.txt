cmake_minimum_required(VERSION 3.8)
project(RtMidi)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(SOURCE_FILES RtMidiInputSource.cpp)

add_library(oi_rtmidi ${SOURCE_FILES})
target_link_libraries(oi_rtmidi rtmidi)

target_include_directories(oi_rtmidi PUBLIC .)

include_directories(../../oilib/src ..)