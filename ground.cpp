#include <GL/glew.h>

#include "ground.h"
#include "sim.h"

Pipeline* Ground::shader = NULL;
Bitmap* Ground::tex = NULL;
unsigned Ground::shader_count = 0;
unsigned Ground::vao = 0;
unsigned Ground::vbo = 0;

vec4 Ground::ambient(1.0f, 1.0f, 1.0f, 1.0f);
vec4 Ground::diffuse(1.0f, 1.0f, 1.0f, 1.0f);
vec4 Ground::specular(1.0f, 1.0f, 1.0f, 1.0f);
float Ground::shininess = 1.0f;

const static vec3 sprite[6] = {
  vec3(-1.0f, 0.0f, 1.0f),
  vec3(-1.0f, 0.0f, -1.0f),
  vec3(1.0f, 0.0f, 1.0f),
  vec3(1.0f, 0.0f, 1.0f),
  vec3(-1.0f, 0.0f, -1.0f),
  vec3(1.0f, 0.0f, -1.0f),
};

const static vec2 tex_st[6] = {
  vec2(512.0f, 512.0f),
  vec2(512.0f, 0.0f),
  vec2(0.0f, 512.0f),
  vec2(0.0f, 512.0f),
  vec2(512.0f, 0.0f),
  vec2(0.0f, 0.0f),
};

static vec3 norms[6];

Ground::Ground(float x, float y, float z, float w, float h):
  Geometry(x, y, z, w, h)
{
  shader = (shader)? shader : new Pipeline("geom.vert", "geom.frag");
  tex = (tex)? tex : new Bitmap("ground.bmp");
  shader_count++;

  if (vao == 0 && vbo == 0) {
    glUseProgram(shader->get_id());
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    // compute normals
    for (int i = 0; i < 6; i += 3) {
      vec3 u = sprite[i+2] - sprite[i];
      vec3 v = sprite[i+1] - sprite[i];
      vec3 n = u.cross(v).normal();

      norms[i] = n;
      norms[i+1] = n;
      norms[i+2] = n;
    }

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData( GL_ARRAY_BUFFER, sizeof(sprite) + sizeof(tex_st) + sizeof(norms), NULL, GL_STATIC_DRAW);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(sprite), sprite);
    glBufferSubData(GL_ARRAY_BUFFER, sizeof(sprite), sizeof(tex_st), tex_st);
    glBufferSubData(GL_ARRAY_BUFFER, sizeof(sprite) + sizeof(tex_st), sizeof(norms), norms);

    shader->bind_attribute("coord", 0);
    glEnableVertexAttribArray(shader->get_attribute(0));
    glVertexAttribPointer(
      shader->get_attribute(0), 3, GL_FLOAT, false, 0, (void*)(0));
    
    shader->bind_attribute("st", 1);
    glEnableVertexAttribArray(shader->get_attribute(1));
    glVertexAttribPointer(
      shader->get_attribute(1), 2, GL_FLOAT, false, 0, (void*)(sizeof(sprite)));

    shader->bind_attribute("norm", 2);
    glEnableVertexAttribArray(shader->get_attribute(1));
    glVertexAttribPointer(
      shader->get_attribute(2), 3, GL_FLOAT, false, 0, (void*)(sizeof(sprite) + sizeof(tex_st)));

    shader->bind_uniform("m", 0);
    shader->bind_uniform("v", 1);
    shader->bind_uniform("proj", 2);
    shader->bind_uniform("tex", 3);

    shader->bind_uniform("ambient_mat", 4);
    shader->bind_uniform("diffuse_mat", 5);
    shader->bind_uniform("specular_mat", 6);
    shader->bind_uniform("shine", 7);

    shader->bind_uniform("light1", 8);
    shader->bind_uniform("light1_ambient", 9);
    shader->bind_uniform("light1_diffuse", 10);
    shader->bind_uniform("light1_specular", 11);

    glUniform4fv(shader->get_uniform(4), 1, ambient.as_array());
    glUniform4fv(shader->get_uniform(5), 1, diffuse.as_array());
    glUniform4fv(shader->get_uniform(6), 1, specular.as_array());
    glUniform1f(shader->get_uniform(7), shininess);
  }
}

Ground::~Ground() {
  shader_count--;
  if (shader_count == 0) {
    glDeleteBuffers(1, &vbo);
    glDeleteVertexArrays(1, &vao);
    delete shader;
    delete tex;
  }
}

void Ground::draw(float dt) {
  glUseProgram(shader->get_id());
  glBindVertexArray(vao);

  glUniformMatrix4fv(shader->get_uniform(0), 1, false, 
    (mat4::scale(w, 1.0f, h) * mat4::translate(x, y, z)).as_array());
  glUniformMatrix4fv(shader->get_uniform(1), 1, false, 
    Sim::get_view_matrix().as_array());
  glUniformMatrix4fv(shader->get_uniform(2), 1, false, 
    Sim::get_projection_matrix().as_array());

  glUniform4f(shader->get_uniform(8),
    Sim::get_light1_x(),
    Sim::get_light1_y(),
    Sim::get_light1_z(), 1.0f);

  glUniform4fv(shader->get_uniform(9), 1, Sim::get_light1_ambient().as_array());
  glUniform4fv(shader->get_uniform(10), 1, Sim::get_light1_diffuse().as_array());
  glUniform4fv(shader->get_uniform(11), 1, Sim::get_light1_specular().as_array());

  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, tex->get_id());
  glUniform1i(shader->get_uniform(2), 0);
  
  glBindBuffer(GL_ARRAY_BUFFER, vbo);

  glDrawArrays(GL_TRIANGLES, 0, 6);
}
