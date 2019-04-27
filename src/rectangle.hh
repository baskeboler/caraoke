#if !defined(RECTANGLE_HH)
#define RECTANGLE_HH

#include "sprite.hh"
#include "SDL2/SDL.h"

class Rectangle: public Sprite {
    SDL_Color border_color, fill_color;

    public:
    Rectangle(int x, int y, int w, int h);
    virtual ~Rectangle();

    void render() override;
};

#endif // RECTANGLE_HH
