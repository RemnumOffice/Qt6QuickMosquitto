cmake_minimum_required(VERSION 3.16)

project(Qt6QuickMosquitto VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(QT_QML_OUTPUT_PLUGIN_DIRECTORY   ${CMAKE_PREFIX_PATH}/qml/QtQuick/Mosquitto)
set(QT_LIB_OUTPUT_DIRECTORY  ${CMAKE_PREFIX_PATH}/lib)


find_package(Qt6 6.2 REQUIRED COMPONENTS BuildInternals Core Gui Qml Quick )
add_subdirectory(mosquitto)

file(MAKE_DIRECTORY ${QT_QML_OUTPUT_PLUGIN_DIRECTORY})

qt_add_library(Qt6QuickMosquitto SHARED)


qt_add_qml_module(Qt6QuickMosquitto
    OUTPUT_DIRECTORY ${QT_QML_OUTPUT_PLUGIN_DIRECTORY}
    URI QtQuick.Mosquitto
    VERSION 1.0
    SOURCES
    qmosquitto.cpp
    qmosquitto.h
)

target_include_directories(Qt6QuickMosquitto PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    mosquitto/
)

target_compile_definitions(Qt6QuickMosquitto
    PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)

target_link_directories(Qt6QuickMosquitto
    PRIVATE ${CMAKE_PREFIX_PATH}/plugins/mosquitto)

target_link_libraries(Qt6QuickMosquitto
    PRIVATE Qt6::Quick mosquitto)



set_target_properties(Qt6QuickMosquitto PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY ${QT_LIB_OUTPUT_DIRECTORY}
)
