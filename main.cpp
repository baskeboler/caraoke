#include "globals.hh"
#include "loader.hh"
#include "text.hh"
#include "texture.hh"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
// #include <pthread.h>
#include <stdio.h>
#include "sdl_utils.hh"
#include "audio.hh"
#include <iostream>
using std::cout, std::cerr, std::endl;
// Screen dimension constants
// extern const int SCREEN_WIDTH;
// extern const int SCREEN_HEIGHT;

// // The window we'll be rendering to
// extern SDL_Window *gWindow;
// extern SDL_Renderer *gRenderer;

// // The surface contained by the window
// extern SDL_Surface *gScreenSurface;
// extern SDL_Surface *gHelloWorld;
// extern TTF_Font *gFont;
// extern texture_t gTextTexture;
/**
 *
 *
 **/
int print_frame(TextFrame* f) {
  pthread_mutex_lock(&f->mutex);
  cout << "textframe(id=" << f->id << ", " << f->text << ", "<< f->progress << endl;
  pthread_mutex_unlock(&f->mutex);
  return 0;
}

/**
 *
 */
int  main(int argc, char **argv) {
  // text_frame_init();
  // for(int i = 0; i < 100; i++) {
  //   text_frame_t f = text_frame_create("algo de texto", 0);
  //   print_frame(f);
  // }

  vector<TextFrame> l = load_json("song.json");
  // for
  // debug_frames(l);
  // Initialize SDL
  if (!sdl_init()) {
    fprintf(stderr, "Failed to init SDL\n");
  } else {

    if (!loadMedia()) {
      fprintf(stderr, "Failed to load media\n");
    } else {
      loadMusic();
      Mix_PlayMusic(gSong, 1);
      // Apply the image
      bool quit = false;
      SDL_Event e;

      while (!quit) {
        while(SDL_PollEvent(&e) != 0) {
          switch (e.type) {
            case SDL_QUIT: {
              quit = true;
              break;
            }
            case SDL_KEYDOWN: {
              switch (e.key.keysym.sym) {
                case SDLK_q:{
                  quit=true;
                  break;
                }
                default: break;
              }
            }
            default: break;
          }
        }
        SDL_BlitSurface(gHelloWorld, NULL, gScreenSurface, NULL);
        gTextTexture->render(0, 0);
        SDL_UpdateWindowSurface(gWindow);
        SDL_RenderPresent(gRenderer);
      }
      // Update the surface

      // Wait two seconds
      // SDL_Delay(5000);
    }
  }
  // Free resources and close SDL
  cleanup();

}