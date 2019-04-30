#if !defined(RECTANGLE_HH)
#define RECTANGLE_HH

#include "SDL2/SDL.h"
#include "sprite.hh"

class Rectangle : public Sprite {
  SDL_Color border_color, fill_color;

public:
  Rectangle(int x, int y, int w, int h);
  virtual ~Rectangle();

  void render() override;
};

#endif // RECTANGLE_HH
