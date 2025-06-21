cmake_minimum_required(VERSION 3.10)
project(TowerDefense VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(libs/SDL)

file(GLOB_RECURSE GAME_SOURCES "src/*.cpp")

include_directories(
    src
    src/Game
    src/Core
    src/Entities
    src/Physics
    src/Utils
)

add_executable(${PROJECT_NAME} ${GAME_SOURCES})

target_link_libraries(${PROJECT_NAME} SDL3::SDL3)

install(TARGETS ${PROJECT_NAME} DESTINATION bin)
install(DIRECTORY ${PROJECT_SOURCE_DIR}/assets/ DESTINATION assets)