#if !defined(COMMON_H)
#define COMMON_H
#include <memory>

typedef int BOOL;
#define TRUE 1;
#define FALSE 0;

typedef int status_t;
#define STATUS_OK 0
#define STATUS_ERROR_LIST_EMPTY 1
#define STATUS_ERROR_TEXTURE_LOAD 2
#define STATUS_ERROR_TEXTURE_CREATE 3

template <typename T> struct Vec2 {
  T x, y;
  Vec2(T a, T b) : x(a), y(b) {}
  Vec2(Vec2 &o) : x(o.x), y(o.y) {}
  Vec2(Vec2 &&o) : x(o.x), y(o.y) {}
  Vec2(const Vec2 &o) : x(o.x), y(o.y) {}
  Vec2(const Vec2 &&o) : x(o.x), y(o.y) {}

  Vec2 &operator+(Vec2 &other) {
    Vec2 *n = new Vec2(*this);
    n->x += other.x;
    n->y += other.y;
    return *n;
  }

  Vec2 &operator*(double f) {
    Vec2 *n = new Vec2(*this);
    n->x *= f;
    n->y *= f;
    return *n;
  }
  Vec2 &operator=(Vec2 &other) {
    x = other.x;
    y = other.y;
    return *this;
  }
  Vec2 &operator-(Vec2 &other) { return this + (-1.0 * other); }
};

typedef Vec2<int> IVec2;
typedef Vec2<double> DVec2;

extern double lerp(double t, DVec2 a, DVec2 b);

#endif // COMMON_H
