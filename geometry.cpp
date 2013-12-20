#include "maths.h"
#include "geometry.h"

Geometry::Geometry(float x, float y, float z, float w, float h) {
  this->x = x;
  this->y = y;
  this->z = z;
  this->w = w;
  this->h = h;
}

float Geometry::get_x() {
  return x;
}

float Geometry::get_y() {
  return y;
}

float Geometry::get_z() {
  return z;
}

float Geometry::get_w() {
  return w;
}

float Geometry::get_h() {
  return h;
}

bool Geometry::collide_cicle(float x, float z, float radius) {
  float cx = clampf(x, this->x - w / 2.0f, this->x + w / 2.0f);
  float cz = clampf(z, this->z - h / 2.0f, this->z + h / 2.0f);
  float dx = x - cx;
  float dz = z - cz;
  return (dx * dx + dz * dz) < radius;
}
