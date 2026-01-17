cmake_minimum_required(VERSION 4.0)
project(computer_game C)

set(CMAKE_C_STANDARD 11)

add_executable(computer_game game/src/main.c
        game/inc/main.h
        game/inc/instructions.h
        deps/raygui.h
        game/src/inst_drag.c
        game/inc/inst_drag.h
        game/inc/styles.h
        game/src/inst_list.c
        game/inc/inst_list.h
        game/src/inst_box.c
        game/inc/inst_box.h
        game/src/gen_inst.c
        game/inc/gen_inst.h
        game/src/screen_controls.c
        game/inc/screen_controls.h
        game/src/alu.c
        game/inc/alu.h
        game/src/comparator.c
        game/inc/comparator.h)

target_link_libraries(computer_game PUBLIC raylib m)
target_include_directories(computer_game PRIVATE game/inc deps)