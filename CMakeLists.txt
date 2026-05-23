cmake_minimum_required(VERSION 3.16)

project(pr_1 VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

qt_add_executable(pr_1 WIN32
    main.cpp
    MainWindow.cpp
    MainWindow.h
    resources.qrc
)

target_link_libraries(pr_1 PRIVATE Qt6::Widgets)

set_target_properties(pr_1 PROPERTIES
    WIN32_EXECUTABLE TRUE
)

# -----------------------------
# Автоматический deployment Qt
# -----------------------------

if(WIN32)

    # Поиск windeployqt
    get_target_property(QT_QMAKE_EXECUTABLE Qt6::qmake IMPORTED_LOCATION)
    get_filename_component(QT_BIN_DIR "${QT_QMAKE_EXECUTABLE}" DIRECTORY)

    find_program(WINDEPLOYQT_EXECUTABLE
        windeployqt
        HINTS "${QT_BIN_DIR}"
    )

    add_custom_command(TARGET pr_1 POST_BUILD
        COMMAND "${WINDEPLOYQT_EXECUTABLE}"
                --no-translations
                --no-compiler-runtime
                $<TARGET_FILE:pr_1>

        COMMENT "Deploying Qt dependencies..."
    )

endif()