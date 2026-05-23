# Copyright (c) 2026 David A. Frischknecht
#
# SPDX-License-Identifier: Apache-2.0

# CMakeList.txt : CMake project for Minesweeper, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.10)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("Minesweeper")

find_package(wxWidgets REQUIRED net gl core base webview)
include(${wxWidgets_USE_FILE})

# Define common sources
set(MINESWEEPER_SOURCES "App.h" "App.cpp" "MainWindow.h" "MainWindow.cpp" "SevenSegmentDisplay.h" "SevenSegmentDisplay.cpp")

# Conditional add_executable for Windows
if(WIN32)
	add_executable(Minesweeper WIN32 "Minesweeper.rc" ${MINESWEEPER_SOURCES})
endif()

# Conditional add_executable for Linux
if(UNIX AND NOT WIN32)
	add_executable(Minesweeper ${MINESWEEPER_SOURCES})
endif()

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET Minesweeper PROPERTY CXX_STANDARD 20)
endif()

target_link_libraries(Minesweeper PRIVATE ${wxWidgets_LIBRARIES})
target_precompile_headers(Minesweeper PRIVATE <wx/wxprec.h>)

if (WIN32)
	add_custom_command(
		TARGET Minesweeper
		POST_BUILD
		COMMAND ${CMAKE_COMMAND} -E copy_if_different ${VCPKG_INSTALLED_DIR}/${VCPKG_TARGET_TRIPLET}/bin/Microsoft.Web.WebView2.Core.dll $<TARGET_FILE_DIR:Minesweeper>
	)
endif()