cmake_minimum_required(VERSION 3.16)

project(CreditChartDemo LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets Charts)

set(SOURCES
    main.cpp
    mainwindow.cpp
)

set(HEADERS
    mainwindow.h
)

qt_add_executable(CreditChartDemo
    ${SOURCES}
    ${HEADERS}
)

target_link_libraries(CreditChartDemo PRIVATE Qt6::Core Qt6::Gui Qt6::Widgets Qt6::Charts)
