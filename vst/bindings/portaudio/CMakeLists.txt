cmake_minimum_required(VERSION 3.8)
project(portaudio)

set(PORTAUDIO "$ENV{PORTAUDIO_HOME}")
link_directories("${PORTAUDIO}/lib")

set(SOURCE_FILES PortAudioPlayer.cpp)

if (${CMAKE_SYSTEM_NAME} MATCHES "Windows")
elseif (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    find_library(AUDIO_TOOLBOX AudioToolbox)
    mark_as_advanced(AUDIO_TOOLBOX)
    set(PLATFORM_LIBS ${AUDIO_TOOLBOX})

    find_library(CORE_AUDIO CoreAudio)
    mark_as_advanced(CORE_AUDIO)
    set(PLATFORM_LIBS ${CORE_AUDIO})

    find_library(CORE_SERVICES CoreServices)
    mark_as_advanced(CORE_SERVICES)
    set(PLATFORM_LIBS ${CORE_SERVICES})

    find_library(CORE_FOUNDATION CoreFoundation)
    mark_as_advanced(CORE_FOUNDATION)
    set(PLATFORM_LIBS ${CORE_FOUNDATION})

    find_library(AUDIO_UNIT AudioUnit)
    mark_as_advanced(AUDIO_UNIT)
    set(PLATFORM_LIBS ${AUDIO_UNIT})
endif ()

add_library(oi_portaudio ${SOURCE_FILES})
target_link_libraries(oi_portaudio "${PORTAUDIO}/lib/libportaudio.a" ${AUDIO_TOOLBOX} ${CORE_AUDIO} ${CORE_SERVICES} ${CORE_FOUNDATION} ${AUDIO_UNIT})

target_include_directories(oi_portaudio PUBLIC ${PORTAUDIO}/include)