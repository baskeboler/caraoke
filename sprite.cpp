#include "sprite.hh"

Sprite::Sprite(int x, int y) : x(x), y(y), w(0), h(0) {}
Sprite::Sprite() : Sprite(0, 0) {}

int Sprite::get_x() const { return x; }

int Sprite::get_y() const { return y; }
int Sprite::get_w() const { return w; }
int Sprite::get_h() const { return h; }
void Sprite::set_x(int x) { this->x = x; }
void Sprite::set_y(int y) { this->y = y; }
void Sprite::set_w(int w) { this->w = w; }
void Sprite::set_h(int h) { this->h = h; }

Sprite::~Sprite() {}