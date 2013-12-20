#include <stdio.h>
#include <stdlib.h>

#include <list>

#include "sim.h"
#include "ground.h"
#include "wall.h"
#include "maths.h"

#define DEG2RAD M_PI / 180.0f

using namespace std;

struct SimState {
  list<Geometry*> solids;
  float x, y, z;
  float speed;
  float yaw;
  Ground grnd;
  SimState():
    grnd(0.0f, 0.0f, 0.0f, 80000.0f, 80000.0f)
  {
    x = z = 0.0;
    y = 100.0;
    Sim::add_geometry(&grnd);
    solids.push_back(new Wall(-50.0f, 0.0f, 0.0f, 10.0f, 200.0f));
    solids.push_back(new Wall(-50.0f, 0.0f, 200.0f, 10.0f, 200.0f));
    solids.push_back(new Wall(-50.0f, 0.0f, 400.0f, 10.0f, 200.0f));
    solids.push_back(new Wall(50.0f, 0.0f, 0.0f, 10.0f, 200.0f));
    solids.push_back(new Wall(0.0f, 0.0f, -50.0f, 200.0f, 10.0f));
  }

  ~SimState() {
    for (list<Geometry*>::iterator
      solid = solids.begin();
      solid != solids.end();
      solid++)
    {
      delete *solid;
    }
  }
};

void phys_callback(float dt, SimState* ss) {
  static float walk_timer = 0.0f;
  walk_timer += dt;
  if (Sim::is_key_pressed('\e'))
    Sim::quit();

  if (Sim::is_key_pressed(Sim::KEY_LEFT))
    ss->yaw += 100.0f * dt;

  if (Sim::is_key_pressed(Sim::KEY_RIGHT))
    ss->yaw -= 100.0f * dt;

  if (Sim::is_key_pressed(Sim::KEY_UP))
    ss->speed += 20.0f * dt;

  if (Sim::is_key_pressed(Sim::KEY_DOWN))
    ss->speed -= 20.0f * dt;

  if (ss->speed > 0.0f)
    ss->speed -= 8.0f * dt;
  else if (ss->speed < 0.0f)
    ss->speed += 8.0f * dt;

  if (ss->speed < 0.1f && ss->speed > -0.1f)
    ss->speed = 0.0f;
  else
    ss->speed = clampf(ss->speed, -4.0f, 4.0f);

  float dx = sinf(DEG2RAD*ss->yaw)*ss->speed*60.0*dt;
  float dz = cosf(DEG2RAD*ss->yaw)*ss->speed*60.0*dt;

  // Smooth collisions using a 2-pass method
  for (list<Geometry*>::iterator
    solid = ss->solids.begin();
    solid != ss->solids.end();
    solid++)
  {
    if ((*solid)->collide_cicle(ss->x + dx, ss->z, 200.0f))
      goto x_collide;
  }
  ss->x += dx;

  x_collide:
  for (list<Geometry*>::iterator
    solid = ss->solids.begin();
    solid != ss->solids.end();
    solid++)
  {
    if ((*solid)->collide_cicle(ss->x, ss->z + dz, 200.0f))
      goto z_collide;
  }
  ss->z += dz;

  z_collide:
  Sim::set_cam_x(ss->x);
  // This adds a silly "walking affect"
  Sim::set_cam_y(ss->y+sinf(walk_timer*10.0f)*ss->speed);
  Sim::set_cam_z(ss->z);
  Sim::set_rot_y(ss->yaw);

  Sim::set_light1_x(ss->x);
  Sim::set_light1_y(ss->y);
  Sim::set_light1_z(ss->z);
}

int main(int argc, char* argv[]) {
  Sim::init(&argc, argv, "Maise 1.0");

  Sim::set_light1_ambient(0.5f, 0.5f, 0.5f);
  Sim::set_light1_diffuse(0.0f, 0.5f, 0.5f);
  Sim::set_light1_specular(1.0f, 1.0f, 1.0f);

  SimState ss;

  for (list<Geometry*>::iterator
    solid = ss.solids.begin();
    solid != ss.solids.end();
    solid++)
  {
    Sim::add_geometry(*solid);
  }
  
  Sim::set_phys_callback((void(*)(float, void*)) phys_callback, &ss);
  Sim::run();

  return 0;
}
