cmake_minimum_required(VERSION 2.6)
project(Douayfense)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")

set(CMAKE_CXX_FLAGS "-g -Wall")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

find_package(SFML 1.6 REQUIRED system window graphics network audio)

include_directories(${SFML_INCLUDE_DIR})

set(mainLibs ${SFML_LIBRARIES})

file(
	GLOB_RECURSE
	MAIN_SOURCES
	src/*
)

add_executable(Douayfense ${MAIN_SOURCES})

target_link_libraries(Douayfense ${mainLibs})

configure_file(res/map/level1.map map/level1.map COPYONLY)
configure_file(res/map/level2.map map/level2.map COPYONLY)

configure_file(res/img/skel.png img/skel.png COPYONLY)

configure_file(res/img/tower.png img/tower.png COPYONLY)
configure_file(res/img/tower_up.png img/tower_up.png COPYONLY)
configure_file(res/img/freezer.png img/freezer.png COPYONLY)
configure_file(res/img/freezer_up.png img/freezer_up.png COPYONLY)
configure_file(res/img/poisoner.png img/poisoner.png COPYONLY)
configure_file(res/img/poisoner_up.png img/poisoner_up.png COPYONLY)

configure_file(res/img/money.png img/money.png COPYONLY)
configure_file(res/img/bg.png img/bg.png COPYONLY)

configure_file(res/img/grass.png img/grass.png COPYONLY)
