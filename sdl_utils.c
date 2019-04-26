#include "sdl_utils.h"

BOOL sdl_init() {
  // Initialization flag
  BOOL success = TRUE;

  // Initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
    printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
    success = FALSE;
  } else {
    // Initialize SDL_ttf
    if (TTF_Init() == -1) {
      printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n",
             TTF_GetError());
      success = FALSE;
    } else {
      if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n",
               Mix_GetError());
        success = FALSE;
      } else {
        if (IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_WEBP) < 0) {
          printf("SDL_image could not initialize! SDL_image Error: %s\n",
                 IMG_GetError());
          success = FALSE;
        } else {

          // Create window
          SDL_CreateWindowAndRenderer(SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE,
          &gWindow, &gRenderer);
        //    SDL_WINDOWPOS_UNDEFINED,
        //                              SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,
        //                              SCREEN_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
          if (gWindow == NULL) {
            printf("Window could not be created! SDL_Error: %s\n",
                   SDL_GetError());
            success = FALSE;
          } else {
            // Get window surface
            gScreenSurface = SDL_GetWindowSurface(gWindow);
            // gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED|SDL_RENDERER_PRESENTVSYNC|SDL_RENDERER_TARGETTEXTURE);
          }
        }
      }
    }
  }

  return success;
}

BOOL loadMedia() {
  // Loading success flag
  BOOL success = TRUE;

  gFont = TTF_OpenFont("Bangers-Regular.ttf", 28);

  if (gFont == NULL) {
    printf("Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError());
    success = FALSE;
  } else {
    // Render text
    SDL_Color textColor = {255, 0, 0, 255};
    gTextTexture = texture_init(100, 100);

    if (STATUS_OK != texture_load_from_rendered_text(
            gTextTexture, "The quick brown fox jumps over the lazy dog",
            textColor, gFont, gRenderer)) {
      printf("Failed to render text texture!\n");
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