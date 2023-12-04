cmake_minimum_required(VERSION 3.21)
project(UntitledGame LANGUAGES CXX)

#### Setup Directories ####
#Main output directory
SET(OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/")
# Ouput all DLLs from all libs into main build folder
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_DIRECTORY})

#add_custom_target(copy_resources ALL COMMAND ${CMAKE_COMMAND}
#  -E copy_directory
#    "${PROJECT_SOURCE_DIR}/res"
#    ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/$<CONFIGURATION>/res
#)

file(COPY "${CMAKE_SOURCE_DIR}/res" DESTINATION "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")

#### Add External Dependencies ####
# SFML - graphics library
add_subdirectory("lib/sfml" EXCLUDE_FROM_ALL)
#include_directories("lib/sfml/include")
set(SFML_INCS "lib/sfml/include")
link_directories("${CMAKE_BINARY_DIR}/lib/sfml/lib")

# B2D - Box2D phyics library
add_subdirectory("lib/b2d/Box2D")
#include_directories("lib/b2d/Box2D/")
set(B2D_INCS "lib/b2d/Box2D/")
link_directories("${CMAKE_BINARY_DIR}/lib/sfml/lib")

#### Add Engine and our own library projects####

file(GLOB_RECURSE RESOURCE_FILES "res/*.*")
## Engine ##
file(GLOB_RECURSE SOURCE_FILES lib/engine/*.cpp lib/engine/*.h)
add_library(lib_engine STATIC ${SOURCE_FILES} ${RESOURCE_FILES})
target_include_directories(lib_engine INTERFACE "${CMAKE_SOURCE_DIR}/lib/engine/" PUBLIC SYSTEM ${B2D_INCS} )
target_link_libraries(lib_engine lib_tile_level_loader lib_maths lib_ecm Box2D sfml-graphics sfml-audio)

## Tile loader lib
file(GLOB_RECURSE SOURCE_FILES lib/lib_tile_level_loader/*.cpp lib/lib_tile_level_loader/*.h)
add_library(lib_tile_level_loader STATIC ${SOURCE_FILES})
target_include_directories(lib_tile_level_loader INTERFACE "${CMAKE_SOURCE_DIR}/lib/lib_tile_level_loader/" )
target_link_libraries(lib_tile_level_loader lib_maths sfml-graphics)

# Maths lib
add_library(lib_maths INTERFACE)
target_sources(lib_maths INTERFACE "${CMAKE_SOURCE_DIR}/lib/lib_maths/maths.h")
target_include_directories(lib_maths INTERFACE "${CMAKE_SOURCE_DIR}/lib/lib_maths" SYSTEM INTERFACE ${SFML_INCS})

## ECM lib
file(GLOB_RECURSE SOURCE_FILES lib/lib_ecm/*.cpp lib/lib_ecm/*.h)
add_library(lib_ecm STATIC ${SOURCE_FILES})
target_include_directories(lib_ecm INTERFACE "${CMAKE_SOURCE_DIR}/lib/lib_ecm" )
target_link_libraries(lib_ecm PRIVATE lib_maths)


################### Add Practicals Below ##########################

###### Drop-Pod #######

#file(GLOB_RECURSE SOURCES Drop-Pod/*.cpp Drop-Pod/*.h)
#file(GLOB_RECURSE CMPNTS Drop-Pod/components/*.cpp Drop-Pod/components/*.h)
#file(GLOB_RECURSE SCENES Drop-Pod/scenes/*.cpp Drop-Pod/scenes/*.h)
#add_executable(Drop_Pod ${SOURCES} ${RESOURCE_FILES})
#source_group("components" FILES ${CMPNTS})
#source_group("resources" FILES ${RESOURCE_FILES})
##target_include_directories(Drop_Pod SYSTEM PRIVATE ${SFML_INCS} ${B2D_INCS})
#target_link_libraries(Drop_Pod lib_engine)
#set(EXECUTABLES ${EXECUTABLES} Drop_Pod)

file(GLOB_RECURSE CMP src/components/*.cpp src/components/*.h)
file(GLOB_RECURSE SRC src/*.cpp src/*.h)
file(GLOB_RECURSE SCENE src/scene/*.cpp src/scene/*.h)
add_executable(UntitledGame ${CMP} ${SRC} ${SCENE})

target_link_libraries(UntitledGame PRIVATE sfml-graphics lib_engine sfml-system)
target_compile_features(UntitledGame PRIVATE cxx_std_17)


install(TARGETS UntitledGame)