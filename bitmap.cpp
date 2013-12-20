#include <stdlib.h>
#include <stdio.h>

#include <GL/glew.h>

#include "bitmap.h"

using namespace std;

Bitmap::Bitmap(const std::string& path) {

  FILE* file = fopen(path.c_str(), "rb");
  int offset;
  int width;
  int height;
  int size;

  fseek(file, 0xa, SEEK_SET);
  fread(&offset, 4, 1, file);

  fseek(file, 0x12, SEEK_SET);
  fread(&width, 4, 1, file);
  fread(&height, 4, 1, file);

  fseek(file, 0x22, SEEK_SET);
  fread(&size, 4, 1, file);

  pixels = (unsigned short*) malloc(size);
  fseek(file, offset, SEEK_SET);
  fread(pixels, 2, size/2, file);

  fclose(file);

  unsigned short* pixel;

  // twiddle red and blue channels A1B5G5R5 -> A1R5G5B5
  for (int i = 0; i < size/2; ++i) {
    pixel = pixels + i;
    *pixel = (((*pixel & 0x7c00) >> 10) | (*pixel & 0x83e0) | ((*pixel & 0x1f) << 10));
  }

  #ifndef GL_UNSIGNED_SHORT_1_5_5_5_REV
  #define GL_UNSIGNED_SHORT_1_5_5_5_REV 0x8366
  #endif

  glGenTextures(1, &id);
  glBindTexture(GL_TEXTURE_2D, id);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0,
       GL_RGBA, GL_UNSIGNED_SHORT_1_5_5_5_REV, pixels);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

  this->width = width;
  this->height = height;
}

Bitmap::~Bitmap() {
  glDeleteTextures(1, &id);
  free(pixels);
}

unsigned Bitmap::get_id() {
  return id;
}

unsigned Bitmap::get_width() {
  return width;
}

unsigned Bitmap::get_height() {
  return height;
}

float Bitmap::intensity_at(int i) {
  float t =
    ((pixels[i] & 0x7c00) >> 10) +
    ((pixels[i] & 0x3e0) >> 5) + 
    (pixels[i] & 0x1f);
  return (t / 3.0) / 32.0;
}

unsigned short Bitmap::operator[](int i) {
  return pixels[i];
}

