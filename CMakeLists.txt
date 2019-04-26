cmake_minimum_required(VERSION 3.14)

project(caraoke)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_BUILD_TYPE Debug)
set(SOURCES 
    main.cpp 
    text.cpp text.hh 
    loader.hh loader.cpp  
    texture.hh texture.cpp 
    globals.hh globals.cpp 
    common.hh
    sdl_utils.hh sdl_utils.cpp 
    audio.hh audio.cpp
    sprite.hh sprite.cpp
    karaoke_text_display.hh karaoke_text_display.cpp)
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
add_executable(main ${SOURCES})

target_link_libraries(main Threads::Threads 
    ${APR_LIBRARIES}
    ${JANSSON_LIBRARIES} 
    ${SDL_LIBRARIES} )
