cmake_minimum_required (VERSION 3.7 FATAL_ERROR)
project(Fortunes)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core Concurrent Network WebSockets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Concurrent Network WebSockets)

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
if (APPLE)
    target_link_libraries(FortunesApp PRIVATE ${CUTE_CLIENT_SDK_DIR}/CuteClientSdk.framework)
elseif (WIN32)
    target_include_directories(FortunesApp PRIVATE ${CUTE_CLIENT_SDK_DIR}/include)
    target_link_directories(FortunesApp PRIVATE ${CUTE_CLIENT_SDK_DIR}/lib)
    target_link_libraries(FortunesApp PRIVATE ${CUTE_CLIENT_SDK_DIR}/lib/CuteClientSdk$<$<CONFIG:Debug>:d>.lib)
else ()
    target_include_directories(FortunesApp PRIVATE ${CUTE_CLIENT_SDK_DIR}/include)
    target_link_directories(FortunesApp PRIVATE ${CUTE_CLIENT_SDK_DIR}/lib ${QT_SDK_DIR}/lib)
    target_link_libraries(FortunesApp PRIVATE -lCuteClientSdk)
endif ()
target_link_libraries(FortunesApp PRIVATE
                      Qt${QT_VERSION_MAJOR}::Core
                      Qt${QT_VERSION_MAJOR}::Concurrent
                      Qt${QT_VERSION_MAJOR}::Network
                      Qt${QT_VERSION_MAJOR}::WebSockets)
