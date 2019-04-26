#if !defined(KARAOKE_TEXT_DISPLAY_H)
#define KARAOKE_TEXT_DISPLAY_H

#include "sprite.hh"
#include "texture.hh"
#include "text.hh"
#include <memory>
#include <SDL2/SDL.h>

using std::shared_ptr;

class KaraokeTextDisplay: public Sprite {
    shared_ptr<TextFrame> text_frame;
    shared_ptr<Texture> texture; 
    SDL_Renderer *renderer;
    
    public:
    KaraokeTextDisplay();
    KaraokeTextDisplay(const char * text, SDL_Color color, TTF_Font* font, SDL_Renderer* renderer);
    virtual void render();
    virtual ~KaraokeTextDisplay();    
};
#endif // KARAOKE_TEXT_DISPLAY_H
