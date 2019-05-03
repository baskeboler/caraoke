#include "sprite.hh"

Sprite::Sprite(double x, double y, double w, double h)
    : w(w), h(h),
      angle(0), vel{0, 0}, pos{x, y}, accel{0, 0}, last_update{0}, scale{1} {}
Sprite::Sprite() : Sprite(0, 0) {}

double Sprite::get_angle() const { return angle; }
double Sprite::get_x() const { return pos.x; }

double Sprite::get_y() const { return pos.y; }
double Sprite::get_w() const { return w; }
double Sprite::get_h() const { return h; }
double Sprite::get_scale() const { return scale; }
void Sprite::set_x(double x) { this->pos.x = x; }
void Sprite::set_y(double y) { this->pos.y = y; }
void Sprite::set_w(double w) { this->w = w; }
void Sprite::set_h(double h) { this->h = h; }
void Sprite::set_angle(double a) { this->angle = a; }
void Sprite::set_scale(double a) { this->scale = a; }

Sprite::~Sprite() {}