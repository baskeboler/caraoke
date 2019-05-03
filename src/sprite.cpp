#include "sprite.hh"

Sprite::Sprite(int x, int y, int w, int h) :  w(w), h(h), angle(0), vel{0,0}, pos{x,y}, accel{0,0} {}
Sprite::Sprite() : Sprite(0, 0) {}

double Sprite::get_angle() const { return angle; }
int Sprite::get_x() const { return pos.x; }

int Sprite::get_y() const { return pos.y; }
int Sprite::get_w() const { return w; }
int Sprite::get_h() const { return h; }
void Sprite::set_x(int x) { this->pos.x = x; }
void Sprite::set_y(int y) { this->pos.y = y; }
void Sprite::set_w(int w) { this->w = w; }
void Sprite::set_h(int h) { this->h = h; }
void Sprite::set_angle(double a) { this->angle = a; }

Sprite::~Sprite() {}