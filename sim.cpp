#include <stdio.h>

#include "sim.h"

#define DEG2RAD (M_PI * 2.0f) / 360.0f

Sim* Sim::self = NULL;
list<Geometry*> Sim::geoms;

vec3 Sim::cam_pos;
vec3 Sim::cam_angles;
mat4 Sim::view_matrix;
mat4 Sim::proj_matrix;
mat4 Sim::ortho_matrix;
mat4 Sim::vp;

vec3 Sim::light1_pos;
vec4 Sim::ambient1;
vec4 Sim::diffuse1;
vec4 Sim::specular1;

void (*Sim::callback)(float,void*)  = NULL;
void* Sim::cb_data = NULL;

bool Sim::running = false;

bool Sim::key_presses[512];
bool Sim::key_releases[512];
bool Sim::key_holds[512];

void Sim::keyboard_clear() {
  for (int i = 0; i < 256; i++) {
    key_presses[i] = false;
    key_releases[i] = false;
  }
}

void Sim::keyboard_down(unsigned char key, int x, int y) {
  key_presses[key] = true;
  key_holds[key] = true;
  key_releases[key] = false;
}

void Sim::keyboard_up(unsigned char key, int x, int y) {
  key_presses[key] = false;
  key_holds[key] = false;
  key_releases[key] = true;
}

void Sim::keyboard_special_down(int key, int x, int y) {
  key_presses[key+256] = true;
  key_holds[key+256] = true;
  key_releases[key+256] = false;
}

void Sim::keyboard_special_up(int key, int x, int y) {
  key_presses[key+256] = false;
  key_holds[key+256] = false;
  key_releases[key+256] = true;
}

Sim* Sim::instance() {
  return (self)? self : self = new Sim();
}

Sim::Sim() {

}

Sim::~Sim() {

}

void Sim::init(int* argc, char* argv[], const string& title) {
  glutInit(argc, argv);
  glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
  glutInitWindowSize(800, 800);
  glutInitContextVersion(3, 1);
  glutInitContextProfile(GLUT_FORWARD_COMPATIBLE);
  glutInitContextProfile(GLUT_CORE_PROFILE);
  glutCreateWindow(title.c_str());
  glewExperimental = true;
  glewInit();

  glutKeyboardFunc(keyboard_down);
  glutKeyboardUpFunc(keyboard_up);
  glutSpecialFunc(keyboard_special_down);
  glutSpecialUpFunc(keyboard_special_up);
  glutReshapeFunc(reshape);
  
  glutSetKeyRepeat(GLUT_KEY_REPEAT_OFF);
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_TEXTURE_2D);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glClearColor(0.0, 0.0, 0.0, 1.0);
  glShadeModel(GL_SMOOTH);
}

void Sim::add_geometry(Geometry* geom) {
  geoms.push_back(geom);
}

static uint64_t raw_time() {
  struct timespec ts;
  clock_gettime(CLOCK_MONOTONIC, &ts);
  return (uint64_t) ts.tv_sec * (uint64_t) 1000000000 + (uint64_t) ts.tv_nsec;
}

void Sim::run() {
  running = true;
  float t0 = 0, t1 = 0, dt = 0;
  float ft = 0, f = 0, fps = 0;
  clock_t start_time = raw_time();
  while (running) {
    t1 = (float) (raw_time() - start_time) * 1e-9;
    dt = t1 - t0;
    t0 = t1;

    if (f > 60) {
      fps = f / (t1 - ft);
      printf("%.1lf fps\n", fps);
      ft = t0;
      f = 0;
    }
    f++;

    keyboard_clear();
    glutMainLoopEvent();
    look();
    if (callback)
      callback(dt, cb_data);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    list<Geometry*>::iterator g, end = geoms.end();
    for(g = geoms.begin(); g != end; g++) {
      (*g)->draw(dt);
    }

    glutSwapBuffers();
  }
}

void Sim::quit() {
  running = false;
}

void Sim::look() {

  view_matrix =
    mat4::rotate_y(cam_angles.y-180.0f) *
    mat4::rotate_x(cam_angles.x) * 
    mat4::rotate_z(cam_angles.z);

  view_matrix =
    mat4::translate(-cam_pos.x, -cam_pos.y, -cam_pos.z) * view_matrix;

}

void Sim::reshape(int width, int height) {
  const static float near = 0.1;
  const static float far = 8000.0;
  float aspect = float(width) / height;
  float th = tanf(60.0*DEG2RAD / 2.0);
  proj_matrix[0][0] = 1.0 / (aspect * th);
  proj_matrix[1][1] = 1.0 / th;
  proj_matrix[2][2] = (far+near)/(near-far);
  proj_matrix[3][2] = (2*far*near)/(near-far);
  proj_matrix[2][3] = -1.0;

  float w = width / 2.0;
  float h = height / 2.0;
  ortho_matrix[0][0] = 2.0/(w - (-w));
  ortho_matrix[1][1] = 2.0/(h - (-h));
  ortho_matrix[2][2] = 2.0/(near - far);
  ortho_matrix[3][3] = 1.0;
  ortho_matrix[3][0] = 0.0;
  ortho_matrix[3][1] = -1.0;
  ortho_matrix[3][2] = -(far + near)/(far - near);

  glViewport(0, 0, width, height);
}

bool Sim::is_key_pressed(int key) {
  return key_presses[key];
}

bool Sim::is_key_released(int key) {
  return key_releases[key];
}

bool Sim::is_key_held(int key) {
  return key_holds[key];
}

void Sim::set_cam_x(float x) {
  cam_pos.x = x;
}

void Sim::set_cam_y(float y) {
  cam_pos.y = y;
}

void Sim::set_cam_z(float z) {
  cam_pos.z = z;
}

float Sim::get_cam_x() {
  return cam_pos.x;
}

float Sim::get_cam_y() {
  return cam_pos.y;
}

float Sim::get_cam_z() {
  return cam_pos.z;
}

void Sim::set_rot_x(float x) {
  cam_angles.x = x;
}

void Sim::set_rot_y(float y) {
  cam_angles.y = y;
}

void Sim::set_rot_z(float z) {
  cam_angles.z = z;
}

float Sim::get_rot_x() {
  return cam_angles.x;
}

float Sim::get_rot_y() {
  return cam_angles.y;
}

float Sim::get_rot_z() {
  return cam_angles.z;
}

void Sim::set_light1_x(float x) {
  light1_pos.x = x;
}

void Sim::set_light1_y(float y) {
  light1_pos.y = y;
}

void Sim::set_light1_z(float z) {
  light1_pos.z = z;
}

float Sim::get_light1_x() {
  return light1_pos.x;
}

float Sim::get_light1_y() {
  return light1_pos.y;
}

float Sim::get_light1_z() {
  return light1_pos.z;
}

void Sim::set_light1_ambient(float r, float g, float b) {
  ambient1.r = r;
  ambient1.g = g;
  ambient1.b = b;
  ambient1.a = 1.0f;
}

void Sim::set_light1_diffuse(float r, float g, float b) {
  diffuse1.r = r;
  diffuse1.g = g;
  diffuse1.b = b;
  diffuse1.a = 1.0f;
}

void Sim::set_light1_specular(float r, float g, float b) {
  specular1.r = r;
  specular1.g = g;
  specular1.b = b;
  specular1.a = 1.0f;
}

vec4& Sim::get_light1_ambient() {
  return ambient1;
}

vec4& Sim::get_light1_diffuse() {
  return diffuse1;
}

vec4& Sim::get_light1_specular() {
  return specular1;
}

mat4& Sim::get_view_matrix() {
  return view_matrix;
}

mat4& Sim::get_projection_matrix() {
  return proj_matrix;
}

mat4& Sim::get_ortho_matrix() {
  return ortho_matrix;
}

void Sim::set_phys_callback(void (*cb)(float,void*), void* data) {
  callback = cb;
  cb_data = data;
}
