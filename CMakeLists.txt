cmake_minimum_required (VERSION 3.7 FATAL_ERROR)
project(Fortunes)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 REQUIRED COMPONENTS Core Concurrent Network WebSockets)

if (CMAKE_SYSTEM_NAME STREQUAL "Linux")
    add_library(RemoteObjectsLib SHARED
                Fortunes.cpp
                Fortunes.h)

    target_include_directories(RemoteObjectsLib PRIVATE ${CUTE_SERVER_SDK_DIR}/include)

    target_link_libraries(RemoteObjectsLib
                          ${CUTE_SERVER_SDK_DIR}/lib/libCuteServerSdk.so
                          Qt${QT_VERSION_MAJOR}::Core
                          Qt${QT_VERSION_MAJOR}::Concurrent
                          Qt${QT_VERSION_MAJOR}::Network
                          Qt${QT_VERSION_MAJOR}::WebSockets)
endif()

add_executable(FortunesApp
               FortunesClient.h
               Main.cpp)

target_include_directories(FortunesApp PRIVATE ${CUTE_CLIENT_SDK_DIR}/include)

target_link_libraries(FortunesApp
                      ${CUTE_CLIENT_SDK_DIR}/lib/libCuteClientSdk.so
                      Qt${QT_VERSION_MAJOR}::Core
                      Qt${QT_VERSION_MAJOR}::Concurrent
                      Qt${QT_VERSION_MAJOR}::Network
                      Qt${QT_VERSION_MAJOR}::WebSockets)
