cmake_minimum_required(VERSION 4.0)
project(computer_game C)

set(CMAKE_C_STANDARD 11)

if (EMSCRIPTEN)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -s USE_GLFW=3 -s ASSERTIONS=1 -s WASM=1 -s ASYNCIFY -s GL_ENABLE_GET_PROC_ADDRESS=1")
    set(CMAKE_EXECUTABLE_SUFFIX ".html") # This line is used to set your executable to build with the emscripten html template so that you can directly open it.
endif ()

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
        game/inc/comparator.h
        game/src/registers.c
        game/inc/registers.h
        game/src/decoder_bus.c
        game/inc/decoder_bus.h
        game/src/eval.c
        game/inc/eval.h
        game/src/draw_coins.c
        game/inc/draw_coins.h
        game/src/manual.c
        game/inc/manual.h
        game/inc/programs.h
        game/src/programs.c
        game/inc/text.h)

target_link_libraries(computer_game PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/deps/libraylib.a" m)
target_include_directories(computer_game PRIVATE game/inc deps ../../git-cache/raylib/src)