cmake_minimum_required(VERSION 3.14)

project(caraoke)
# set(CXX_STANDARD c++17)
set(CMAKE_CXX_STANDARD_REQUIRED 17)
add_compile_options(-std=c++17)
add_link_options(-std=c++17)
set(SOURCES 
src/app.hh            src/karaoke_text_display.hh  src/sprite.hh          src/app.cpp                   src/loader.cpp     src/sprite.cpp
src/audio.hh          src/loader.hh                src/text.hh            src/audio.cpp                 src/main.cpp       src/text.cpp
src/common.hh         src/common.cpp               src/rectangle.hh       src/texture.hh                src/event_handler.cpp         
src/rectangle.cpp     src/texture.cpp              src/event_handler.hh   src/scene.hh                  src/texture_sprite.hh  
src/globals.cpp       src/scene.cpp                src/texture_sprite.cpp
src/globals.hh        src/karaoke_text_display.cpp   
src/title_scene.hh src/title_scene.cpp src/sound_controller.hh src/sound_controller.cpp
src/text_sprite.hh src/text_sprite.cpp src/files.hh src/files.cpp
src/song_info.hh src/song_info.cpp src/karaoke_scene.hh src/karaoke_scene.cpp)

find_package(Threads REQUIRED)
find_package(Boost REQUIRED filesystem)
# find_package(SDL REQUIRED VERSION 2)
# find_package(SDL_sound REQUIRED)
# find_package(SDL_ttf REQUIRED)
# find_package(jansson REQUIRED)
# find_library(Jansson NAMES jansson Jansson)
set(SDL_LIBRARIES -lSDL2 -lSDL2_gfx -lSDL2_image -lSDL2_ttf -lSDL2_mixer)
find_path(APR_INCLUDE_DIR NAMES apr.h PATHS /usr/include/*)
find_path(JANSSON_INCLUDE_DIR NAMES jansson.h)
include_directories(${APR_INCLUDE_DIR} ${JANSSON_INCLUDE_DIR} ${Boost_INCLUDE_DIR})

set(APR_LIBRARIES -lapr-1)
set(JANSSON_LIBRARIES -ljansson)
add_executable(main ${SOURCES})

target_link_libraries(main Threads::Threads 
    ${APR_LIBRARIES}
    ${JANSSON_LIBRARIES} 
    ${SDL_LIBRARIES}  ${Boost_LIBRARIES})
