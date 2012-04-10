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
configure_file(res/map/level3.map map/level3.map COPYONLY)

configure_file(res/img/skel.png img/skel.png COPYONLY)
configure_file(res/img/goblin.png img/goblin.png COPYONLY)
configure_file(res/img/drake.png img/drake.png COPYONLY)

configure_file(res/img/tower.png img/tower.png COPYONLY)
configure_file(res/img/tower_up.png img/tower_up.png COPYONLY)
configure_file(res/img/freezer.png img/freezer.png COPYONLY)
configure_file(res/img/freezer_up.png img/freezer_up.png COPYONLY)
configure_file(res/img/poisoner.png img/poisoner.png COPYONLY)
configure_file(res/img/poisoner_up.png img/poisoner_up.png COPYONLY)

configure_file(res/img/money.png img/money.png COPYONLY)
configure_file(res/img/menubg.png img/menubg.png COPYONLY)
configure_file(res/img/bg.png img/bg.png COPYONLY)
configure_file(res/img/title.png img/title.png COPYONLY)

configure_file(res/img/grass.png img/grass.png COPYONLY)

configure_file(res/img/button.png img/button.png COPYONLY)
configure_file(res/img/dialog-information.png img/dialog-information.png COPYONLY)
configure_file(res/img/crown.png img/crown.png COPYONLY)
configure_file(res/img/skull.png img/skull.png COPYONLY)

configure_file(res/music/menu.ogg music/menu.ogg COPYONLY)
configure_file(res/music/ending.ogg music/ending.ogg COPYONLY)
configure_file(res/music/village.ogg music/village.ogg COPYONLY)
configure_file(res/music/ancients.ogg music/ancients.ogg COPYONLY)
configure_file(res/music/direnews.ogg music/direnews.ogg COPYONLY)
configure_file(res/music/dreaming.ogg music/dreaming.ogg COPYONLY)
configure_file(res/music/procession.ogg music/procession.ogg COPYONLY)

configure_file(res/snd/ding.ogg snd/ding.ogg COPYONLY)
configure_file(res/snd/dying.ogg snd/dying.ogg COPYONLY)
configure_file(res/snd/fire.ogg snd/fire.ogg COPYONLY)
configure_file(res/snd/build.ogg snd/build.ogg COPYONLY)
configure_file(res/snd/money.ogg snd/money.ogg COPYONLY)
