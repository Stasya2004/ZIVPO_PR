cmake_minimum_required(VERSION 3.16)

project(ZIVPO_PR VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

qt_add_executable(ZIVPO_PR
    main.cpp
    MainWindow.cpp
    MainWindow.h
    resources.qrc
)

target_link_libraries(ZIVPO_PR PRIVATE Qt6::Widgets)

set_target_properties(ZIVPO_PR PROPERTIES
    WIN32_EXECUTABLE TRUE
)