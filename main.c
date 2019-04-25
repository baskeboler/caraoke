#include "loader.h"
#include "text.h"
#include "texture.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <pthread.h>
#include <stdio.h>

// Screen dimension constants
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

// The window we'll be rendering to
SDL_Window *gWindow = NULL;
SDL_Renderer *gRenderer = NULL;

// The surface contained by the window
SDL_Surface *gScreenSurface = NULL;
SDL_Surface *gHelloWorld = NULL;
TTF_Font *gFont = NULL;
texture_t gTextTexture = NULL;
/**
 *
 *
 **/
int print_frame(text_frame_t f) {
  pthread_mutex_lock(&f->mutex);
  printf("textframe(id=%d, %s, %d)\n", f->id, f->text, f->progress);
  pthread_mutex_unlock(&f->mutex);
  return 0;
}

BOOL sdl_init() {
  // Initialization flag
  BOOL success = TRUE;

  // Initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
    success = FALSE;
  } else {
    // Initialize SDL_ttf
    if (TTF_Init() == -1) {
      printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n",
             TTF_GetError());
      success = FALSE;
    } else {
      // Create window
      gWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED,
                                 SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,
                                 SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
      if (gWindow == NULL) {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        success = FALSE;
      } else {
        // Get window surface
        gScreenSurface = SDL_GetWindowSurface(gWindow);
        gRenderer = SDL_GetRenderer(gWindow);
      }
    }
  }

  return success;
}

BOOL loadMedia() {
  // Loading success flag
  BOOL success = TRUE;

  gFont = TTF_OpenFont("Bangers-Regular.ttf", 28);

   if( gFont == NULL )
    {
        printf( "Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError() );
        success = FALSE;
    }
    else
    {
        //Render text
        SDL_Color textColor = { 0, 0, 0 };
        gTextTexture = texture_init(100, 100);

        if( !texture_load_from_rendered_text(gTextTexture, "The quick brown fox jumps over the lazy dog", textColor, gFont, gRenderer) )
        {
            printf( "Failed to render text texture!\n" );
            success = FALSE;
        } 
    }
  // Load splash image
  gHelloWorld =
      // SDL_LoadBMP("02_getting_an_image_on_the_screen/hello_world.bmp");
      IMG_Load("bg.jpeg");
  if (gHelloWorld == NULL) {
    printf("Unable to load image %s! SDL Error: %s\n", "bg.jpeg",
           SDL_GetError());
    success = FALSE;
  }

  return success;
}

void cleanup() {
  // Deallocate surface
  SDL_FreeSurface(gHelloWorld);
  gHelloWorld = NULL;

  // Destroy window
  SDL_DestroyWindow(gWindow);
  gWindow = NULL;

  // Quit SDL subsystems
  SDL_Quit();
}
/**
 *
 */
int main(int argc, char **argv) {
  printf("hello\n");
  text_frame_init();
  // for(int i = 0; i < 100; i++) {
  //   text_frame_t f = text_frame_create("algo de texto", 0);
  //   print_frame(f);
  // }

  list_t l = load_json("song.json");
  // for
  debug_frames(l);
  // Initialize SDL
  if (!sdl_init()) {
    fprintf(stderr, "Failed to init SDL\n");
    return 1;
  } else {

    if (!loadMedia()) {
      fprintf(stderr, "Failed to load media\n");
      return 1;
    } else {

      // Apply the image
      SDL_BlitSurface(gHelloWorld, NULL, gScreenSurface, NULL);
      // Update the surface
      SDL_UpdateWindowSurface(gWindow);

      // Wait two seconds
      SDL_Delay(2000);
    }
  }
  // Free resources and close SDL
  cleanup();

  list_destroy(&l);

  return 0;
}
