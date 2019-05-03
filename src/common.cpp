#include "common.hh"
#include <cassert>

double lerp(double percent, double from, double to) {
  return percent * (to - from) + from;
}

double lerp(double t, DVec2 from, DVec2 to) {
  //   assert(t >= from.x && t <= from.y);
  if (t <= from.x) {
    return to.x;
  } else if (t >= from.y) {
    return to.y;
  } else
    return lerp((t - from.x) / (from.y - from.x), to.x, to.y);
}