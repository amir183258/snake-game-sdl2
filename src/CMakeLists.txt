cmake_minimum_required(VERSION 3.10)
project(SnakeGame)

set(CMAKE_CXX_STANDARD 17)

find_package(SDL2 REQUIRED)
find_package(PkgConfig REQUIRED)
pkg_check_modules(SDL2_IMAGE REQUIRED SDL2_image)

add_executable(SnakeGame
    main.cpp
    game.cpp
    input_handler.cpp
    playground.cpp
    fps_handler.cpp
    snake.cpp
)

set(ASSETS_DIR ${CMAKE_SOURCE_DIR}/assets)

add_custom_command(
    TARGET SnakeGame POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${ASSETS_DIR} ${CMAKE_CURRENT_BINARY_DIR}/assets
)

target_include_directories(SnakeGame PRIVATE
    ${SDL2_INCLUDE_DIRS}
    ${SDL2_IMAGE_INCLUDE_DIRS}
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(SnakeGame PRIVATE
    ${SDL2_LIBRARIES}
    ${SDL2_IMAGE_LIBRARIES}
)
