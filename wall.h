#ifndef WALL_H
#define WALL_H

#include "geometry.h"
#include "shader.h"
#include "bitmap.h"
#include "maths.h"

class Wall: public Geometry {
  public:
    Wall(float x, float y, float z, float w, float h);
    virtual ~Wall();
    virtual void draw(float);
  protected:
    static Pipeline* shader;
    static Bitmap* tex;
    static unsigned shader_count;
    static unsigned vao;
    static unsigned vbo;

    static vec4 ambient;
    static vec4 diffuse;
    static vec4 specular;
    static float shininess;
};

#endif
