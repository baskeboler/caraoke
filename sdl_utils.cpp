#include "sdl_utils.hh"
#include "texture.hh"
#include <iostream>
using std::cout, std::cerr, std::endl;

bool sdl_init() {
  // Initialization flag
  bool success = true;

  // Initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
    printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
    success = false;
  } else {
    // Initialize SDL_ttf
    if (TTF_Init() == -1) {
      printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n",
             TTF_GetError());
      success = false;
    } else {
      if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n",
               Mix_GetError());
        success = false;
      } else {
        if (IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_WEBP) < 0) {
          printf("SDL_image could not initialize! SDL_image Error: %s\n",
                 IMG_GetError());
          success = false;
        } else {

          // Create window
          SDL_Window * w; SDL_Renderer * renderer;
          SDL_CreateWindowAndRenderer(Globals::SCREEN_WIDTH, Globals::SCREEN_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE,
          &w, &renderer);
          Globals::gWindow=w;
          Globals::gRenderer=renderer;
        //    SDL_WINDOWPOS_UNDEFINED,
        //                              SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,
        //                              SCREEN_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
          if (Globals::gWindow == NULL) {
            cerr << "Window could not be created! SDL_Error: " <<
                   SDL_GetError() << endl;
            success = false;
          } else {
            // Get window surface
            
            Globals::gScreenSurface=SDL_GetWindowSurface(Globals::gWindow);
            // gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED|SDL_RENDERER_PRESENTVSYNC|SDL_RENDERER_TARGETTEXTURE);
          }
        }
      }
    }
  }

  return success;
}

bool loadMedia() {
  // Loading success flag
  bool success = true;

  Globals::gFont=TTF_OpenFont("Bangers-Regular.ttf", 28);

  if (Globals::gFont == nullptr) {
    printf("Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError());
    success = false;
  } else {
    // Render text
    SDL_Color textColor = {255, 0, 0, 255};
    Globals::gTextTexture.reset(new Texture(nullptr, Globals::gRenderer));//texture_init(100, 100);
    Globals::gTextTexture->init(100, 100);
    Globals::gTextTexture->load_from_rendered_text(
            "The quick brown fox jumps over the lazy dog",
            textColor, Globals::gFont);
    // if (STATUS_OK != gTextTexture->load_from_rendered_text(
    //         "The quick brown fox jumps over the lazy dog",
    //         textColor, gFont)) {
    //   printf("Failed to render text texture!\n");
    //   success = false;
    // }
  }
  // Load splash image
  Globals::gHelloWorld=      
    // SDL_LoadBMP("02_getting_an_image_on_the_screen/hello_world.bmp");
      IMG_Load("bg.jpeg");
  if (Globals::gHelloWorld == nullptr) {
    cerr << "Unable to load image bg.jpeg! SDL Error: " << 
           SDL_GetError() << endl;
    success = false;
  }

  return success;
}

void cleanup() {
  // Deallocate surface
  SDL_FreeSurface(Globals::gHelloWorld);
  Globals::gHelloWorld=nullptr;

  // Destroy window
  SDL_DestroyWindow(Globals::gWindow);
  Globals::gWindow=nullptr;

  // Quit SDL subsystems
  SDL_Quit();
}