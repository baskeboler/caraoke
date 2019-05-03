#if !defined(SPRITE_H)
#define SPRITE_H
#include "common.hh"
class Sprite {
private:
  double  w, h;
  double scale;
  double angle;
  DVec2 pos;
  DVec2 vel;
  DVec2 accel;
  double last_update;
public:
  Sprite(double x, double y, double w = 0, double h = 0);
  Sprite();

  DVec2 get_pos() const { return pos; }
  DVec2 get_vel() const { return vel;}
  DVec2 get_accel() const {return accel; }

  void set_pos(DVec2 v) {pos = v;}
  void set_vel(DVec2 v) {vel = v;}

  void set_accel(DVec2 v) {accel = v;}

  void update_pos(double ts) {
    if (last_update == 0) {
      last_update = ts;
    } 
    pos.x += vel.x * (ts - last_update);
    pos.y += vel.y * (ts - last_update);
    vel = vel + accel*(ts - last_update);
    last_update = ts;
  }
  double get_x() const;
  double get_y() const;
  double get_w() const;
  double get_h() const;
  double get_angle() const;
  double get_scale() const;

  void set_x(double x);
  void set_y(double y);
  void set_w(double w);
  void set_h(double h);
  void set_angle(double a);
void set_scale(double a);

  virtual void render() = 0;

  virtual ~Sprite();
};


#endif // SPRITE_H
