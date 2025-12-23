cmake_minimum_required(VERSION 3.10)
project(SnakeGame)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_BUILD_TYPE Debug)

find_package(SDL2 REQUIRED)
find_package(PkgConfig REQUIRED)
pkg_check_modules(SDL2_IMAGE REQUIRED SDL2_image)
pkg_check_modules(SDL2_TTF REQUIRED SDL2_ttf)
pkg_check_modules(SDL2_MIXER REQUIRED SDL2_mixer)

add_executable(SnakeGame
    main.cpp
    game.cpp
    input_handler.cpp
    playground.cpp
    fps_handler.cpp
    snake.cpp
    apple.cpp
    monitor.cpp
    state_manager.cpp
    play_state.cpp
    pause_state.cpp
    loss_state.cpp
    win_state.cpp
    start_menu_state.cpp
    help_state.cpp
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
    ${SDL2_TTF_INCLUDE_DIRS}
    ${SDL2_MIXER_INCLUDE_DIRS}
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(SnakeGame PRIVATE
    ${SDL2_LIBRARIES}
    ${SDL2_IMAGE_LIBRARIES}
    ${SDL2_TTF_LIBRARIES}
    ${SDL2_MIXER_LIBRARIES}
)
