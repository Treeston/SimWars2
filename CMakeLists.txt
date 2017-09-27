cmake_minimum_required(VERSION 3.0)
project(SimWars2)

# don't mess up our git repo, please
set(CMAKE_DISABLE_SOURCE_CHANGES ON)
set(CMAKE_DISABLE_IN_SOURCE_BUILD ON)

option(TESTS "Build test binaries" 0)
set(WITH_SOURCE_TREE    "hierarchical" CACHE STRING "Build the source tree for IDE's.")
set_property(CACHE WITH_SOURCE_TREE PROPERTY STRINGS no flat hierarchical hierarchical-folders)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake-macros")
include(GroupSources)
include(AutoCollect)

if( TESTS )
  add_subdirectory(tests)
endif( TESTS )

add_subdirectory(src)

add_executable(SimWars2 main.cpp)
target_link_libraries(SimWars2
  PUBLIC
    logic)
