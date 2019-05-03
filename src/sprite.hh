#if !defined(SPRITE_H)
#define SPRITE_H
#include "common.hh"
class Sprite {
private:
  int  w, h;
  double angle;
  IVec2 pos;
  DVec2 vel;
  DVec2 accel;
public:
  Sprite(int x, int y, int w = 0, int h = 0);
  Sprite();

  IVec2 get_pos() const { return pos; }
  DVec2 get_vel() const { return vel;}
  DVec2 get_accel() const {return accel; }

  void set_pos(IVec2 v) {pos = v;}
  void set_vel(DVec2 v) {vel = v;}

  void set_accel(DVec2 v) {accel = v;}

  void update_pos() { 
    pos.x += vel.x;
    pos.y += vel.y;
    vel = vel + accel;
  }
  int get_x() const;
  int get_y() const;
  int get_w() const;
  int get_h() const;
  double get_angle() const;

  void set_x(int x);
  void set_y(int y);
  void set_w(int w);
  void set_h(int h);
  void set_angle(double a);

  virtual void render() = 0;

  virtual ~Sprite();
};

#endif // SPRITE_H
