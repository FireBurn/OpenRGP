cmake_minimum_required(VERSION 3.16)
project(OpenRGP VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE RelWithDebInfo)
endif()

# ---- core (no Qt) ----
add_library(openrgp_core STATIC
  core/src/rgp_file.cpp
  core/src/sqtt_trace.cpp
  core/src/sqtt_decode.cpp
  core/src/rdf_file.cpp
  core/src/kernels.cpp
  core/src/code_object_db.cpp
  core/src/events.cpp
  core/src/stats.cpp
  core/src/export.cpp
  core/src/analysis.cpp
)
target_include_directories(openrgp_core PUBLIC core/include)
find_package(PkgConfig QUIET)
if(PkgConfig_FOUND)
  pkg_check_modules(ZSTD QUIET libzstd)
endif()
if(ZSTD_FOUND)
  target_compile_definitions(openrgp_core PRIVATE OPENRGP_HAVE_ZSTD)
  target_link_libraries(openrgp_core PUBLIC ${ZSTD_LIBRARIES})
  target_include_directories(openrgp_core PRIVATE ${ZSTD_INCLUDE_DIRS})
endif()

include(GNUInstallDirs)

# ---- CLI ----
add_executable(openrgp_cli cli/src/main.cpp)
target_link_libraries(openrgp_cli PRIVATE openrgp_core)

# ---- GUI (Qt6) ----
option(OPENRGP_GUI "Build the Qt6 GUI when Qt6 is available" ON)
if(OPENRGP_GUI)
  find_package(Qt6 COMPONENTS Widgets QUIET)
endif()
if(OPENRGP_GUI AND Qt6_FOUND)
  add_executable(openrgp_gui
    gui/src/main.cpp
    gui/src/MainWindow.cpp
    gui/MainWindow.h
  )
  target_link_libraries(openrgp_gui PRIVATE openrgp_core Qt6::Widgets)
  set_target_properties(openrgp_gui PROPERTIES
    AUTOMOC ON AUTORCC ON)
  target_include_directories(openrgp_gui PRIVATE gui)
  install(PROGRAMS $<TARGET_FILE:openrgp_gui> TYPE BIN RENAME openrgp-gui)
else()
  message(STATUS "GUI not built")
endif()
install(PROGRAMS $<TARGET_FILE:openrgp_cli> TYPE BIN RENAME openrgp)
install(FILES README.md TODO.md DESTINATION ${CMAKE_INSTALL_DOCDIR})

# ---- tests ----
enable_testing()
add_executable(openrgp_test test/test_main.cpp)
target_link_libraries(openrgp_test PRIVATE openrgp_core)
add_test(NAME container_walk COMMAND openrgp_test container)
add_executable(openrgp_decode_test test/decode_test.cpp)
target_link_libraries(openrgp_decode_test PRIVATE openrgp_core)
add_test(NAME sqtt_decode_rdna4 COMMAND openrgp_decode_test ${CMAKE_SOURCE_DIR}/test/data/radv_gfx12_decode.rgp 139 53109 80)
add_test(NAME sqtt_decode_rdna2 COMMAND openrgp_decode_test ${CMAKE_SOURCE_DIR}/test/data/radv_rdna2_vkcube.rgp 55 4016 4)
# RDNA3 capture is 44 MB: pass it explicitly, e.g. OPENRGP_TEST_RDNA3=/path/cap.rgp ctest (1275 waves, 10288640 instructions)
if(DEFINED ENV{OPENRGP_TEST_RDNA3})
  add_test(NAME sqtt_decode_rdna3 COMMAND openrgp_decode_test $ENV{OPENRGP_TEST_RDNA3} 1275 10288640 2)
endif()
