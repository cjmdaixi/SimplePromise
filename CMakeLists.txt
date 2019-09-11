cmake_minimum_required(VERSION 3.5)

project(SimplePromise LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 COMPONENTS Core Quick ConCurrent REQUIRED)

add_executable(SimplePromise main.cpp fluxhub.cpp fluxhub.h simplepromise.cpp simplepromise.h qml.qrc)

target_compile_definitions(SimplePromise
  PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)
target_link_libraries(SimplePromise
  PRIVATE Qt5::Core Qt5::Quick Qt5::Concurrent)
