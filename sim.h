#ifndef SIM_H
#define SIM_H

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <GL/freeglut_ext.h>

#include <string>
#include <list>
using namespace std;

#include "geometry.h"
#include "maths.h"

class Sim {

  public:
    enum KEYS {
      KEY_F1 = GLUT_KEY_F1 + 256,
      KEY_F2 = GLUT_KEY_F2 + 256,
      KEY_F3 = GLUT_KEY_F3 + 256,
      KEY_F4 = GLUT_KEY_F4 + 256,
      KEY_F5 = GLUT_KEY_F5 + 256,
      KEY_F6 = GLUT_KEY_F6 + 256,
      KEY_F7 = GLUT_KEY_F7 + 256,
      KEY_F8 = GLUT_KEY_F8 + 256,
      KEY_F9 = GLUT_KEY_F9 + 256,
      KEY_F10 = GLUT_KEY_F10 + 256,
      KEY_F11 = GLUT_KEY_F11 + 256,
      KEY_F12 = GLUT_KEY_F12 + 256,
      KEY_LEFT = GLUT_KEY_LEFT + 256,
      KEY_UP = GLUT_KEY_UP + 256,
      KEY_RIGHT = GLUT_KEY_RIGHT + 256,
      KEY_DOWN = GLUT_KEY_DOWN + 256,
      KEY_PAGE_UP = GLUT_KEY_PAGE_UP + 256,
      KEY_PAGE_DOWN = GLUT_KEY_PAGE_DOWN + 256,
      KEY_HOME = GLUT_KEY_HOME + 256,
      KEY_END = GLUT_KEY_END + 256,
      KEY_INSERT = GLUT_KEY_INSERT + 256,
    };

    static Sim* instance();
    ~Sim();

    static void init(int* argc, char* argv[], const string& title);

    static void add_geometry(Geometry* geom);

    static void run();
    static void quit();

    static bool is_key_pressed(int key);
    static bool is_key_released(int key);
    static bool is_key_held(int key);

    static void set_cam_x(float x);
    static void set_cam_y(float y);
    static void set_cam_z(float z);

    static float get_cam_x();
    static float get_cam_y();
    static float get_cam_z();

    static void set_rot_x(float x);
    static void set_rot_y(float y);
    static void set_rot_z(float z);

    static float get_rot_x();
    static float get_rot_y();
    static float get_rot_z();

    static void set_light1_x(float x);
    static void set_light1_y(float y);
    static void set_light1_z(float z);

    static float get_light1_x();
    static float get_light1_y();
    static float get_light1_z();

    static void set_light1_ambient(float r, float g, float b);
    static void set_light1_diffuse(float r, float g, float b);
    static void set_light1_specular(float r, float g, float b);

    static vec4& get_light1_ambient();
    static vec4& get_light1_diffuse();
    static vec4& get_light1_specular();

    static mat4& get_view_matrix();
    static mat4& get_projection_matrix();
    static mat4& get_ortho_matrix();

    static void set_phys_callback(void (*cb)(float,void*), void* data);

  protected:

    static vec3 cam_pos;
    static vec3 cam_angles;

    static mat4 view_matrix;
    static mat4 proj_matrix;
    static mat4 ortho_matrix;
    static mat4 vp;

    static vec3 light1_pos;
    static vec4 ambient1;
    static vec4 diffuse1;
    static vec4 specular1;

    Sim();
    static void look();
    static void reshape(int,int);
    static list<Geometry*> geoms;
    static Sim* self;
    static void (*callback)(float,void*);
    static void* cb_data;
    static bool running;

    static void keyboard_clear();
    static void keyboard_down(unsigned char, int, int);
    static void keyboard_up(unsigned char, int, int);
    static void keyboard_special_down(int, int, int);
    static void keyboard_special_up(int, int, int);
    static bool key_presses[];
    static bool key_releases[];
    static bool key_holds[];

};

#endif /* SIM_H */
