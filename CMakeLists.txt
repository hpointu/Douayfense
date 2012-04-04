cmake_minimum_required(VERSION 2.6)
project(Douayfense)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")

set(CMAKE_CXX_FLAGS "-g -Wall")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

find_package(SFML REQUIRED)

include_directories(${SFML_INCLUDE_DIR})

set(mainLibs ${SFML_LIBRARY})

file(
	GLOB_RECURSE
	MAIN_SOURCES
	src/*
)

add_executable(Douayfense ${MAIN_SOURCES})

target_link_libraries(Douayfense ${mainLibs})

configure_file(res/default.map default.map COPYONLY)
configure_file(res/skel.png skel.png COPYONLY)
configure_file(res/tower.png tower.png COPYONLY)
configure_file(res/money.png money.png COPYONLY)
configure_file(res/bg.png bg.png COPYONLY)
