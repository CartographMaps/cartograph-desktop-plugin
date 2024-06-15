cmake_minimum_required(VERSION 3.14)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

project(example_maplist_plugin_cmake VERSION "1.0.0" LANGUAGES CXX C)

find_package(Qt6 REQUIRED COMPONENTS Core Network)

qt_add_plugin(qtmaplistplugin
    CLASS_NAME QtMapListExamplePlugin
    qtmaplistplugin.cpp qtmaplistplugin.h
)

add_compile_definitions(qtmaplistplugin PRIVATE CARTOGRAPH_PLUGIN_COMPILE)

target_include_directories(qtmaplistplugin PUBLIC ${CMAKE_CURRENT_LIST_DIR})

target_link_libraries(qtmaplistplugin PRIVATE
    Qt6::Core
    Qt6::Network
)
