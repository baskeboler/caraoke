#if !defined(SPRITE_H)
#define SPRITE_H

class Sprite {
private:
  int x, y, w, h;

public:
  Sprite(int x, int y, int w = 0, int h = 0);
  Sprite();

  int get_x() const;
  int get_y() const;
  int get_w() const;
  int get_h() const;

  void set_x(int x);
  void set_y(int y);
  void set_w(int w);
  void set_h(int h);

  virtual void render() = 0;

  virtual ~Sprite();
};

#endif // SPRITE_H
