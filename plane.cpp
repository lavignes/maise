#include <math.h>

#include "plane.h"

#define DEG2RAD (M_PI * 2.0f) / 360.0f

Plane::Plane(float x, float y, float z, float yaw) {
  this->x = x;
  this->y = y;
  this->z = z;
  pitch = roll = 0.0;
  this->yaw = yaw;
  v = 0.0;
}

float Plane::get_x() {
  return x;
}

float Plane::get_y() {
  return y;
}

float Plane::get_z() {
  return z;
}

void Plane::set_x(float x){
  this->x = x;
}

void Plane::set_y(float y){
  this->y = y;
}

void Plane::set_z(float z){
  this->z = z;
}

float Plane::get_roll() {
  return roll;
}

void Plane::set_roll(float roll) {
  this->roll = roll;
}

float Plane::get_pitch() {
  return pitch;
}

void Plane::set_pitch(float pitch) {
  this->pitch = pitch;
}

float Plane::get_yaw() {
  return yaw;
}

void Plane::set_yaw(float yaw) {
  this->yaw = yaw;
}

float Plane::get_speed() {
  return v;
}

void Plane::set_speed(float speed) {
  v = speed;
}

void Plane::phys(float dt) {
  float p = sinf(pitch * DEG2RAD); // Basically get if we are looking up or down
  int up = (p > 0) - (p < 0);
  float yaw_d = up * asinf(sinf(DEG2RAD * roll) * p) * v;
  if (yaw_d > 32.0)
    yaw_d = 32.0;
  else if (yaw_d < -32.0)
    yaw_d = -32.0;
  yaw += yaw_d*dt;

  if (v < 0.0)
    v = 0.0;

  x += v*cosf(DEG2RAD * yaw) * dt;
  z -= v*sinf(DEG2RAD * yaw) * dt;
  y += (v * sinf(DEG2RAD * pitch) - v * fabs(sinf(DEG2RAD * roll))) * dt;
}
