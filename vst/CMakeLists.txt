#=============================================================================
#  MuseScore
#  Music Composition & Notation
#
#  Copyright (C) 2013 Werner Schweer
#
#  This program is free software; you can redistribute it and/or modify
#  it under the terms of the GNU General Public License version 2
#  as published by the Free Software Foundation and appearing in
#  the file LICENCE.GPL
#=============================================================================

include(${PROJECT_SOURCE_DIR}/build/gch.cmake)

QT5_WRAP_UI(vstUi vst_gui.ui)

if (NOT MSVC)
    set(_all_h_file "${PROJECT_BINARY_DIR}/all.h")
else (NOT MSVC)
    set(_all_h_file "${PROJECT_SOURCE_DIR}/all.h")
endif (NOT MSVC)

add_library(vst STATIC
        ${vstUi}
        vst.cpp
        vstgui.cpp
        PluginFrame.cpp
        ${_all_h_file}
        ${PCH}
        ${INCS}
        )

subdirs(bindings/qt)
subdirs(bindings/vst)
subdirs(lib)
subdirs(third_party/libb64)
subdirs(third_party/pugixml)
subdirs(third_party/rtmidi)

target_link_libraries(vst oilib binding_host_vst binding_qt)

if (NOT MSVC)
    set_target_properties(
            vst
            PROPERTIES
            COMPILE_FLAGS "${PCH_INCLUDE} -g -Wall -Wextra -Winvalid-pch"
    )
else (NOT MSVC)
    set_target_properties(
            vst
            PROPERTIES
            COMPILE_FLAGS "${PCH_INCLUDE}"
    )
endif (NOT MSVC)

xcode_pch(vst all)

# Use MSVC pre-compiled headers
vstudio_pch(vst)

# MSVC does not depend on mops1 & mops2 for PCH
if (NOT MSVC)
    ADD_DEPENDENCIES(vst mops1)
    ADD_DEPENDENCIES(vst mops2)
endif (NOT MSVC)

