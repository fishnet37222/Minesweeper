# CMakeList.txt : CMake project for Minesweeper, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 4.0)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("Minesweeper")

find_package(wxWidgets REQUIRED net gl core base webview)
include(${wxWidgets_USE_FILE})

# Add source to this project's executable.
add_executable (Minesweeper "App.cpp" "App.h" "MainWindow.h" "MainWindow.cpp")

if (WIN32)
	set_target_properties(Minesweeper PROPERTIES WIN32_EXECUTABLE TRUE)
	target_sources(Minesweeper PRIVATE "Minesweeper.rc")
endif()

if (LINUX)
	set_target_properties(Minesweeper PROPERTIES OUTPUT_NAME "minesweeper")
endif()

target_link_libraries(Minesweeper PRIVATE ${wxWidgets_LIBRARIES})
target_precompile_headers(Minesweeper PRIVATE <wx/wxprec.h>)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET Minesweeper PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
