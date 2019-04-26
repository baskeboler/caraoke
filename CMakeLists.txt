cmake_minimum_required(VERSION 3.14)

project(caraoke)
set(CMAKE_BUILD_TYPE Debug)
set(SOURCE main.c text.c)
find_package(Threads REQUIRED)
# find_package(SDL REQUIRED VERSION 2)
# find_package(SDL_sound REQUIRED)
# find_package(SDL_ttf REQUIRED)
# find_package(jansson REQUIRED)
# find_library(Jansson NAMES jansson Jansson)

set(SDL_LIBRARIES -lSDL2 -lSDL2_gfx -lSDL2_image -lSDL2_ttf -lSDL2_mixer)
find_path(APR_INCLUDE_DIR NAMES apr.h PATHS /usr/include/*)
find_path(JANSSON_INCLUDE_DIR NAMES jansson.h)
include_directories(${APR_INCLUDE_DIR} ${JANSSON_INCLUDE_DIR} )

set(APR_LIBRARIES -lapr-1)
set(JANSSON_LIBRARIES -ljansson)
add_executable(main main.c text.c text.h loader.h loader.c list.h list.c texture.h texture.c globals.h common.h
sdl_utils.h sdl_utils.c audio.h audio.c)

target_link_libraries(main Threads::Threads 
    ${APR_LIBRARIES}
    ${JANSSON_LIBRARIES} 
    ${SDL_LIBRARIES} )
