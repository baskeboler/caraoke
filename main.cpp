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
#include "karaoke_text_display.hh"
#include "app.hh"
#include <iostream>
#include <apr_time.h>
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
      auto app = App::get_instance();
  auto k = new KaraokeTextDisplay();
  // k->render();
  delete k;
  FrameVec l = load_json("song.json");
  app->set_frames(std::move(l));
  // for
  // debug_frames(l);
  // Initialize SDL
  if (!sdl_init()) {
    fprintf(stderr, "Failed to init SDL\n");
  } else {

    if (!loadMedia()) {
      fprintf(stderr, "Failed to load media\n");
    } else {
      SDL_Color textColor = {255, 0, 0, 255};
    
      loadMusic();
      Mix_PlayMusic(app->get_song(), 1);
      // Apply the image
      app->start_timer();
      auto kd = new KaraokeTextDisplay("The quick brown fox jumps over the lazy dog",textColor, app->get_font(), app->get_renderer());
      int x = (app->get_screen_width() / 2) - (kd->get_w() / 2),
      y  = (app->get_screen_height() / 2) - (kd->get_h() / 2);
      kd->set_x(x);
      kd->set_y(y);
      app->set_text_display(std::make_shared<KaraokeTextDisplay>(*kd));
      
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
        app->update_frame();
        // cout << "elapsed: " << app->elapsed_seconds() << endl;
        SDL_SetRenderDrawColor(app->get_renderer(),128,128,128,255);
        SDL_RenderClear(app->get_renderer());
        SDL_BlitSurface(app->get_hello_world(), NULL, app->get_screen_surface(), NULL);
        app->get_text_display()->render();
        SDL_UpdateWindowSurface(app->get_window());
        SDL_RenderPresent(app->get_renderer());
      }
      // Update the surface
      delete kd;
      // Wait two seconds
      // SDL_Delay(5000);
    }
  }
  // Free resources and close SDL
  // cleanup();

}
