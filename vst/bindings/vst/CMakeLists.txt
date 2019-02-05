cmake_minimum_required(VERSION 3.8)
# version 3.8 is required for boost 1.64
project(OrchestralInterfaceCMake)
# Version Number
set(OI_VERSION_MAJOR 0)
set(OI_VERSION_MINOR 1)

set(VST3SDK "$ENV{VST3SDK_HOME}")
set(VST2_PLUGIN_INCLUDE "${VST3SDK}/VST2_SDK/public.sdk/source/vst2.x")
set(VST2_INCLUDE "${VST3SDK}/VST2_SDK/pluginterfaces/vst2.x")

set(audioeffect.cpp ${VST2_PLUGIN_INCLUDE}/audioeffect.cpp)
set(audioeffectx.cpp ${VST2_PLUGIN_INCLUDE}/audioeffectx.cpp)

add_definitions(-DVST_2_4_EXTENSIONS=0)

#set(VST_SOURCE "${VST3SDK_SOURCE}/vst3stdsdk.cpp")
set(SOURCE_FILES_HOST
        VstAudioPluginProxy.cpp
        VstAudioHost.cpp
        VstEditorProxy.cpp
        VstEffectProxy.cpp
        VSTModule.cpp)

#set(SOURCE_FILES_PLUGIN
#        VSTAudioPlugin.cpp
#        VstEditor.cpp
#        audioeffect.cpp
#        audioeffectx.cpp)

if (WIN32)
    set(PLATFORM_SOURCE_FILES
            windows/VSTModuleWindows.cpp)
elseif (APPLE)
    set(PLATFORM_SOURCE_FILES
            osx/VSTModuleOSX.cpp)
    include_directories(/Developer/Headers/FlatCarbon)
    find_library(CORE_FOUNDATION CoreFoundation)
    mark_as_advanced(CORE_FOUNDATION)
    set(PLATFORM_LIBS ${CORE_FOUNDATION})
endif ()

add_library(binding_host_vst ${SOURCE_FILES_HOST} ${PLATFORM_SOURCE_FILES})
target_link_libraries(binding_host_vst oilib ${PLATFORM_LIBS})

if (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    target_compile_definitions(binding_host_vst PUBLIC osx)
elseif (${CMAKE_SYSTEM_NAME} MATCHES "windows")
    target_compile_definitions(binding_host_vst PUBLIC windows)
else ()
    target_compile_definitions(binding_host_vst PUBLIC LINUX)
endif ()

target_include_directories(binding_host_vst PUBLIC "${VST2_INCLUDE}")

#add_library(binding_plugin_vst ${SOURCE_FILES_PLUGIN})
#target_include_directories(binding_plugin_vst PUBLIC ${VST2_PLUGIN_INCLUDE} "${VST3SDK}/VST2_SDK")

#function(add_vst_plugin NAME IDENTIFIER VERSION COPYRIGHT)
#    set(VST3SDK "$ENV{VST3SDK_HOME}")
#    set(VST2_PLUGIN_INCLUDE "${VST3SDK}/VST2_SDK/public.sdk/source/vst2.x")
#    set(vstplugmain ${VST2_PLUGIN_INCLUDE}/vstplugmain.cpp)
#    add_library(${NAME} MODULE
#            vstplugmain
#            ${ARGN})
#    set_target_properties(${NAME} PROPERTIES
#            BUNDLE true
#            BUNDLE_EXTENSION vst
#            XCODE_ATTRIBUTE_WRAPPER_EXTENSION vst
#            MACOSX_BUNDLE_INFO_PLIST "${CMAKE_SOURCE_DIR}/src/bindings/vst/resources/Info.plist.in"
#            MACOSX_BUNDLE_BUNDLE_NAME ${NAME}
#            MACOSX_BUNDLE_GUI_IDENTIFIER ${IDENTIFIER}
#            MACOSX_BUNDLE_ICON_FILE ""
#            MACOSX_BUNDLE_SHORT_VERSION_STRING ${VERSION}
#            MACOSX_BUNDLE_COPYRIGHT ${COPYRIGHT})
#    if (APPLE)
#        set_target_properties(${NAME} PROPERTIES LIBRARY_OUTPUT_DIRECTORY "~/Library/Audio/Plug-Ins/VST")
#    elseif (WIN32)
#        set_target_properties(${NAME} PROPERTIES LIBRARY_OUTPUT_DIRECTORY "/Program Files (x86)/Common Files/VST3/")
#    elseif (UNIX AND NOT APPLE) #Linux
#        set_target_properties(${NAME} PROPERTIES LIBRARY_OUTPUT_DIRECTORY "/usr/lib/lxvst")
#    endif ()
#    # TODO: handle windows and linux
#endfunction(add_vst_plugin)