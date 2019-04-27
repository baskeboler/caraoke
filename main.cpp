#include "globals.hh"
#include "loader.hh"
#include "text.hh"
#include "texture.hh"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
// #include <pthread.h>
#include "app.hh"
#include "audio.hh"
#include "karaoke_text_display.hh"
#include "sdl_utils.hh"
#include <apr_time.h>
#include <iostream>
#include <stdio.h>
using std::cout, std::cerr, std::endl;

/**
 *
 *
 **/
int print_frame(TextFrame *f) {
  pthread_mutex_lock(&f->mutex);
  cout << "textframe(id=" << f->id << ", " << f->text << ", " << f->progress
       << endl;
  pthread_mutex_unlock(&f->mutex);
  return 0;
}

/**
 *
 */
int main(int argc, char **argv) {
  auto app = App::get_instance();
  {
    auto k = std::make_shared<KaraokeTextDisplay>();
    app->register_handler( k);
    // k->render();
    // delete k;
    app->unregister_handler(k);
  }
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
      SDL_Color textColor = {255, 255, 255, 255};

      loadMusic();
      Mix_PlayMusic(app->get_song(), 1);
      // Apply the image
      app->start_timer();
      auto kd = std::make_shared<KaraokeTextDisplay>(
          "The quick brown fox jumps over the lazy dog", textColor,
          app->get_font(), app->get_renderer());
      int x = (app->get_screen_width() / 2) - (kd->get_w() / 2),
          y = (app->get_screen_height() / 2) - (kd->get_h() / 2);
      kd->set_x(x);
      kd->set_y(y);
      app->set_text_display(std::make_shared<KaraokeTextDisplay>(*kd));
      app->register_handler( app->get_text_display());
      bool quit = false;
      SDL_Event e;
      auto usertype = SDL_RegisterEvents(1);
      cout << "usertype: " << usertype << endl;
      while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
          switch (e.type) {
          case SDL_QUIT: {
            quit = true;
            break;
          }
          case SDL_KEYDOWN: {
            switch (e.key.keysym.sym) {
            case SDLK_q: {
              quit = true;
              break;
            }
            default:
              break;
            }
            break;
          }
          default:
            break;
          }
          // cout << "event type: " << e.type << endl;
          // app->get_text_display()->update();
          // cout << "elapsed: " << app->elapsed_seconds() << endl;
          // SDL_SetRenderDrawColor(app->get_renderer(),128,64,32,255);
          // SDL_RenderClear(app->get_renderer());
          // SDL_BlitSurface(app->get_hello_world(), NULL,
          //     app->get_screen_surface(), NULL);
          app->handle_event(e);
          // app->get_text_display()->render();
          // SDL_UpdateWindowSurface(app->get_window());
          // SDL_RenderPresent(app->get_renderer());
        }
        // Update the surface
        // SDL_UpdateWindowSurface(app->get_window());
        // SDL_RenderPresent(app->get_renderer());
        // delete kd;
        // Wait two seconds
        // SDL_Delay(50);
        // if (!SDL_WaitEventTimeout(&e, 1000)) {
        //   cerr << "Error waiting event: " << SDL_GetError() << endl;
        //   // quit = true;
        // } else {
        //   SDL_PushEvent(&e);
        // }
        // SDL_PumpEvents();
        e.type = usertype;
        e.user.timestamp = SDL_GetTicks();
        SDL_Delay(17);
        SDL_PushEvent(&e);
      }
    }
    // Free resources and close SDL
    // cleanup();
  }
}
