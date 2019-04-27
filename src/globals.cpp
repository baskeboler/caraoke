#include "globals.hh"


int Globals::SCREEN_WIDTH = 800;
int Globals::SCREEN_HEIGHT = 600;

// The window we'll be rendering to
SDL_Window *Globals::gWindow = nullptr;
SDL_Renderer *Globals::gRenderer = nullptr;

// The surface contained by the window
SDL_Surface *Globals::gScreenSurface = nullptr;
SDL_Surface *Globals::gHelloWorld = nullptr;
TTF_Font *Globals::gFont = nullptr;
shared_ptr<Texture> Globals::gTextTexture = nullptr;

Mix_Music *Globals::gSong = nullptr;
