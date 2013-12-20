#include <stdlib.h>
#include <stdio.h>

#include <GL/glew.h>

#include "shader.h"

using namespace std;

Pipeline::Shader::Shader(Type type, const string& path) {
  FILE* file = fopen(path.c_str(), "rb");
  fseek(file, 0, SEEK_END);
  int size = ftell(file);
  rewind(file);
  char* buffer = new char[size];
  fread(buffer, size, 1, file);

  id = glCreateShader(type);
  this->type = type;
  glShaderSource(id, 1, (const char**) &buffer, &size);

  delete[] buffer;
  fclose(file);

  // Compile shader
  printf("Compiling %s...", path.c_str());
  int compile_ok;
  glCompileShader(id);
  glGetShaderiv(id, GL_COMPILE_STATUS, &compile_ok);

  if (compile_ok == false) {

    printf("error!\n");
    printf("Error in compilation of %s\n", path.c_str());

    int info_size;
    glGetShaderiv(id, GL_INFO_LOG_LENGTH, &info_size);

    char* info = new char[info_size];
    glGetShaderInfoLog(id, info_size, NULL, info);

    printf("%s\n", info);
    delete[] info;

    exit(compile_ok);
  }

  printf("ok!\n");
}

Pipeline::Shader::~Shader() {
  glDeleteShader(id);
}

unsigned Pipeline::Shader::get_id() const {
  return id;
}

Pipeline::Shader::Type Pipeline::Shader::get_type() const {
  return type;
}

void Pipeline::link(unsigned slots) {
  id = glCreateProgram();

  // Attach the shaders
  glAttachShader(id, vert_shader->get_id());
  glAttachShader(id, frag_shader->get_id());
  
  printf("Linking program...");
  int link_ok;
  glLinkProgram(id);

  glGetProgramiv(id, GL_LINK_STATUS, &link_ok);

  if (link_ok == false) {
    printf("error!\n");

    printf("Error in linking\n");

    int info_size;
    glGetProgramiv(id, GL_INFO_LOG_LENGTH, &info_size);

    char* info = new char[info_size];
    glGetProgramInfoLog(id, info_size, NULL, info);

    printf("%s\n", info);
    delete[] info;

    exit(link_ok);
  }
  attributes = new unsigned[slots];
  uniforms = new unsigned[slots];
  printf("ok!\n");
}

Pipeline::Pipeline(
  const Shader* vertex,
  const Shader* fragment,
  unsigned slots): vert_shader(vertex), frag_shader(fragment)
{
  link(slots);
}

Pipeline::Pipeline(const std::string& vert_path, const std::string& frag_path,
    unsigned slots)
{
  vert_shader = new Shader(Shader::VERTEX, vert_path);
  frag_shader = new Shader(Shader::FRAGMENT, frag_path);
  link(slots);
}

Pipeline::~Pipeline() {
  delete[] attributes;
  delete[] uniforms;
  delete vert_shader;
  delete frag_shader;
  glDeleteProgram(id);
}

void Pipeline::bind_attribute(const string& attr_name, unsigned slot) {
  attributes[slot] = glGetAttribLocation(id, attr_name.c_str());
}

void Pipeline::bind_uniform(const string& unif_name, unsigned slot) {
  uniforms[slot] = glGetUniformLocation(id, unif_name.c_str());
}

unsigned Pipeline::get_id() const {
  return id;
}

unsigned Pipeline::get_attribute(unsigned slot) const {
  return attributes[slot];
}

unsigned Pipeline::get_uniform(unsigned slot) const {
  return uniforms[slot];
}