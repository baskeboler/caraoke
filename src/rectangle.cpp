#include "rectangle.hh"
#include "app.hh"

Rectangle::Rectangle(int x, int y, int w, int h)
    : Sprite{x, y, w, h}, border_color{0, 0, 0, 255}, fill_color{255, 0, 0,
                                                                 60} {}
void Rectangle::render() {
  auto app = App::get_instance();
  SDL_Rect rect{get_x(), get_y(), get_w(), get_h()};
  SDL_SetRenderDrawColor(app->get_renderer(), fill_color.r,fill_color.g,fill_color.b,fill_color.a);
  SDL_RenderFillRect(app->get_renderer(), &rect);
  SDL_SetRenderDrawColor(app->get_renderer(), border_color.r,border_color.g,border_color.b,border_color.a);
  SDL_RenderDrawRect(app->get_renderer(), &rect);
}

Rectangle::~Rectangle() {}