cmake_minimum_required(VERSION 3.12 FATAL_ERROR)
project(game-of-life VERSION 0.1)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

if(NOT CMAKE_BUILD_TYPE)
  set(
    CMAKE_BUILD_TYPE Debug 
    CACHE STRING
    "Choose the type of build (Debug or Release)" 
    FORCE
  )
endif()

configure_file(config.h.in config.h)

find_package(
  SFML 2.5 
  COMPONENTS system window graphics network audio REQUIRED
)

file(COPY resources DESTINATION /)

execute_process(COMMAND python gen_tile_types.py
    WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR})

include_directories(src/inc)

set(SRC
  src/util.cpp
  src/tile_dirs.cpp
  src/sf_tile.cpp
  src/path_finding.cpp
  src/win.cpp
  src/main.cpp
)

add_executable(${PROJECT_NAME} ${SRC})

target_include_directories(
  ${PROJECT_NAME} 
  PRIVATE "${PROJECT_BINARY_DIR}"
)

target_link_libraries(${PROJECT_NAME} sfml-graphics)
install(TARGETS ${PROJECT_NAME} DESTINATION bin)