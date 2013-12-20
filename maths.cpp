#include "maths.h"

#define deg2rad (M_PI * 2.0f) / 360.0f

template <class T>
vec2t<T>::vec2t() {
  x = y = T();
}

template <class T>
vec2t<T>::vec2t(T x, T y) {
  this->x = x;
  this->y = y;
}

template <class T>
vec2t<T>::vec2t(const T arr[2]) {
  x = arr[0];
  y = arr[1];
}

template <class T>
const vec2t<T>& vec2t<T>::operator=(const vec2t& v) {
  x = v.x;
  y = v.y;
  return *this;
}

template <class T>
const vec2t<T>& vec2t<T>::operator=(const T arr[2]) {
  x = arr[0];
  y = arr[1];
  return *this;
}

template <class T>
const T* vec2t<T>::as_array() const {
  return vec;
}

template <class T>
vec2t<T> vec2t<T>::normal() const {
  T len = sqrt(x*x + y*y);
  return vec2t(x/len, y/len);
}

template <class T>
vec2t<T> vec2t<T>::operator+(T f) const {
  return vec2t(x+f, y+f);
}

template <class T>
vec2t<T> vec2t<T>::operator-(T f) const {
  return vec2t(x-f, y-f); 
}

template <class T>
vec2t<T> vec2t<T>::operator*(T f) const {
  return vec2t(x*f, y*f);
}

template <class T>
vec2t<T> vec2t<T>::operator/(T f) const {
  return vec2t(x/f, y/f);
}

template <class T>
vec2t<T> vec2t<T>::operator+(const vec2t& v) const {
  return vec2t(x+v.x, y+v.y);
}

template <class T>
vec2t<T> vec2t<T>::operator-(const vec2t& v) const {
  return vec2t(x-v.x, y-v.y);
}

template <class T>
vec2t<T> vec2t<T>::operator*(const vec2t& v) const {
  return vec2t(x*v.x, y*v.y);
}

template <class T>
vec2t<T> vec2t<T>::operator/(const vec2t& v) const {
  return vec2t(x/v.x, y/v.y);
}

template <class T>
T vec2t<T>::dot(const vec2t& v) const {
  return x*v.x + y*v.y;
}

template <class T>
vec2t<T> vec2t<T>::operator+(const T arr[2]) const {
  return vec2t(x+arr[0], y+arr[1]);
}

template <class T>
vec2t<T> vec2t<T>::operator-(const T arr[2]) const {
  return vec2t(x-arr[0], y-arr[1]);
}

template <class T>
vec2t<T> vec2t<T>::operator*(const T arr[2]) const {
  return vec2t(x*arr[0], y*arr[1]);
}

template <class T>
vec2t<T> vec2t<T>::operator/(const T arr[2]) const {
  return vec2t(x/arr[0], y/arr[1]);
}

template <class T>
T vec2t<T>::dot(const T arr[2]) const {
  return x*arr[0] + y*arr[1];
}

template <class T>
T& vec2t<T>::operator[](int i) {
  return vec[i];
}

template <class T>
const T& vec2t<T>::operator[](int i) const {
  return vec[i];
}

template <class T>
vec3t<T>::vec3t() {
  x = y = z = T();
}

template <class T>
vec3t<T>::vec3t(T x, T y, T z) {
  this->x = x;
  this->y = y;
  this->z = z;
}

template <class T>
vec3t<T>::vec3t(const T arr[3]) {
  x = arr[0];
  y = arr[1];
  z = arr[2];
}

template <class T>
vec3t<T>::vec3t(const T arr[2], T z) {
  x = arr[0];
  y = arr[1];
  this->z = z;
}

template <class T>
vec3t<T>::vec3t(const vec2t<T>& v, T z) {
  x = v.x;
  y = v.y;
  this->z = z;
}

template <class T>
const vec3t<T>& vec3t<T>::operator=(const vec3t& v) {
  x = v.x;
  y = v.y;
  z = v.z;
  return *this;
}

template <class T>
const vec3t<T>& vec3t<T>::operator=(const T arr[2]) {
  x = arr[0];
  y = arr[1];
  z = arr[2];
  return *this;
}

template <class T>
const T* vec3t<T>::as_array() const {
  return vec;
}

template <class T>
vec3t<T> vec3t<T>::normal() const {
  T len = sqrt(x*x + y*y + z*z);
  return vec3t(x/len, y/len, z/len);
}

template <class T>
vec3t<T> vec3t<T>::operator+(T f) const {
  return vec3t(x+f, y+f, z+f);
}

template <class T>
vec3t<T> vec3t<T>::operator-(T f) const {
  return vec3t(x-f, y-f, z-f);
}

template <class T>
vec3t<T> vec3t<T>::operator*(T f) const {
  return vec3t(x*f, y*f, z*f);
}

template <class T>
vec3t<T> vec3t<T>::operator/(T f) const {
  return vec3t(x/f, y/f, z/f);
}

template <class T>
vec3t<T> vec3t<T>::operator+(const vec3t& v) const {
  return vec3t(x+v.x, y+v.y, z+v.z);
}

template <class T>
vec3t<T> vec3t<T>::operator-(const vec3t& v) const {
  return vec3t(x-v.x, y-v.y, z-v.z);
}

template <class T>
vec3t<T> vec3t<T>::operator*(const vec3t& v) const {
  return vec3t(x*v.x, y*v.y, z*v.z);
}

template <class T>
vec3t<T> vec3t<T>::operator/(const vec3t& v) const {
  return vec3t(x/v.x, y/v.y, z/v.z);
}

template <class T>
T vec3t<T>::dot(const vec3t& v) const {
  return x*v.x + y*v.y + z*v.y;
}

template <class T>
vec3t<T> vec3t<T>::cross(const vec3t& v) const {
  return vec3t(y*v.z-z*v.y, z*v.x-x*v.z, x*v.y-y*v.x);
}

template <class T>
vec3t<T> vec3t<T>::operator+(const T arr[3]) const {
  return vec3t(x+arr[0], y+arr[1], z+arr[2]);
}

template <class T>
vec3t<T> vec3t<T>::operator-(const T arr[3]) const {
  return vec3t(x-arr[0], y-arr[1], z-arr[2]);
}

template <class T>
vec3t<T> vec3t<T>::operator*(const T arr[3]) const {
  return vec3t(x*arr[0], y*arr[1], z*arr[2]);
}

template <class T>
vec3t<T> vec3t<T>::operator/(const T arr[3]) const {
  return vec3t(x/arr[0], y/arr[1], z/arr[2]);
}

template <class T>
T vec3t<T>::dot(const T arr[3]) const {
  return x*arr[0] + y*arr[1] + z*arr[2];
}

template <class T>
vec3t<T> vec3t<T>::cross(const T arr[3]) const {
  return vec3t(y*arr[2]-z*arr[1], z*arr[0]-x*arr[2], x*arr[1]-y*arr[0]);
}

template <class T>
T& vec3t<T>::operator[](int i) {
  return vec[i];
}

template <class T>
const T& vec3t<T>::operator[](int i) const {
  return vec[i];
}

template <class T>
vec4t<T>::vec4t() {
  x = y = z = w = T();
}

template <class T>
vec4t<T>::vec4t(T x, T y, T z, T w) {
  this->x = x;
  this->y = y;
  this->z = z;
  this->w = w;
}

template <class T>
vec4t<T>::vec4t(const T arr[4]) {
  x = arr[0];
  y = arr[1];
  z = arr[2];
  w = arr[3];
}

template <class T>
vec4t<T>::vec4t(const vec3t<T>& v, T w) {
  x = v.x;
  y = v.y;
  z = v.z;
  this->w = w;
}

template <class T>
vec4t<T>::vec4t(const T arr[3], T w) {
  x = arr[0];
  y = arr[1];
  z = arr[2];
  this->w = w;
}

template <class T>
vec4t<T>::vec4t(const vec2t<T>& v, T z, T w) {
  x = v.x;
  y = v.y;
  this->z = z;
  this->w = w;
}

template <class T>
vec4t<T>::vec4t(const T arr[2], T z, T w) {
  x = arr[0];
  y = arr[1];
  this->z = z;
  this->w = w;
}

template <class T>
const vec4t<T>& vec4t<T>::operator=(const vec4t& v) {
  x = v.x;
  y = v.y;
  z = v.z;
  w = v.w;
  return *this;
}

template <class T>
const vec4t<T>& vec4t<T>::operator=(const T arr[2]) {
  x = arr[0];
  y = arr[1];
  z = arr[2];
  w = arr[3];
  return *this;
}

template <class T>
const T* vec4t<T>::as_array() const {
  return vec;
}

template <class T>
vec4t<T> vec4t<T>::normal() const {
  T len = sqrt(x*x + y*y + z*z + w*w);
  return vec4t(x/len, y/len, z/len, w/len);
}

template <class T>
vec4t<T> vec4t<T>::operator+(T f) const {
  return vec4t(x+f, y+f, z+f, w+f);
}

template <class T>
vec4t<T> vec4t<T>::operator-(T f) const {
  return vec4t(x-f, y-f, z-f, w-f);
}

template <class T>
vec4t<T> vec4t<T>::operator*(T f) const {
  return vec4t(x*f, y*f, z*f, w*f);
}

template <class T>
vec4t<T> vec4t<T>::operator/(T f) const {
  return vec4t(x/f, y/f, z/f, w/f);
}

template <class T>
vec4t<T> vec4t<T>::operator+(const vec4t& v) const {
  return vec4t(x+v.x, y+v.y, z+v.z, w+v.w);
}

template <class T>
vec4t<T> vec4t<T>::operator-(const vec4t& v) const {
  return vec4t(x-v.x, y-v.y, z-v.z, w-v.w);
}

template <class T>
vec4t<T> vec4t<T>::operator*(const vec4t& v) const {
  return vec4t(x*v.x, y*v.y, z*v.z, w*v.w);
}

template <class T>
vec4t<T> vec4t<T>::operator/(const vec4t& v) const {
  return vec4t(x/v.x, y/v.y, z/v.z, w/v.w);
}

template <class T>
T vec4t<T>::dot(const vec4t& v) const {
  return x*v.x + y*v.y + z*v.z + w*v.w;
}

template <class T>
vec4t<T> vec4t<T>::operator+(const T arr[4]) const {
  return vec4t(x+arr[0], y+arr[1], z+arr[2], w+arr[3]);
}

template <class T>
vec4t<T> vec4t<T>::operator-(const T arr[4]) const {
  return vec4t(x-arr[0], y-arr[1], z-arr[2], w-arr[3]);
}

template <class T>
vec4t<T> vec4t<T>::operator*(const T arr[4]) const {
  return vec4t(x*arr[0], y*arr[1], z*arr[2], w*arr[3]);
}

template <class T>
vec4t<T> vec4t<T>::operator/(const T arr[4]) const {
  return vec4t(x/arr[0], y/arr[1], z/arr[2], w/arr[3]);
}

template <class T>
T vec4t<T>::dot(const T arr[4]) const {
  return x*arr[0] + y*arr[1] + z*arr[2] + w*arr[3];
}

template <class T>
T& vec4t<T>::operator[](int i) {
  return vec[i];
}

template <class T>
const T& vec4t<T>::operator[](int i) const {
  return vec[i];
}

template <class T>
mat4t<T>::mat4t() {

}

template <class T>
mat4t<T>::mat4t(T e00, T e01, T e02, T e03,
      T e10, T e11, T e12, T e13,
      T e20, T e21, T e22, T e23,
      T e30, T e31, T e32, T e33)
{
  mat[0] = vec4t<T>(e00, e01, e02, e03);
  mat[1] = vec4t<T>(e10, e11, e12, e13);
  mat[2] = vec4t<T>(e20, e21, e22, e23);
  mat[3] = vec4t<T>(e30, e31, e32, e33);
}

template <class T>
mat4t<T>::mat4t(const vec4t<T>& v1, const vec4t<T>& v2,
      const vec4t<T>& v3, const vec4t<T>& v4)
{
  mat[0] = v1;
  mat[1] = v2;
  mat[2] = v3;
  mat[3] = v4;
}

template <class T>
mat4t<T>::mat4t(const T arr[4][4]) {
  int i, j;
  for (j = 0; j < 4; ++j)
    for (i = 0; i < 4; ++i)
      mat[i][j] = arr[i][j];
}

template <class T>
const mat4t<T>& mat4t<T>::operator=(const mat4t& m) {
  int i, j;
  for (j = 0; j < 4; ++j)
    for (i = 0; i < 4; ++i)
      mat[i][j] = m[i][j];
  return *this;
}

template <class T>
const mat4t<T>& mat4t<T>::operator=(const T arr[4][4]) {
  int i, j;
  for (j = 0; j < 4; ++j)
    for (i = 0; i < 4; ++i)
      mat[i][j] = arr[i][j];
  return *this;
}

template <class T>
const T* mat4t<T>::as_array() const {
  return mat[0].as_array();
}

template <class T>
mat4t<T> mat4t<T>::identity() {
  mat4t m;
  int i;
  for (i = 0; i < 4; ++i)
    m[i][i] = 1;
  return m;
}

template <class T>
mat4t<T> mat4t<T>::translate(T x, T y, T z) {
  mat4t m = identity();
  m[3][0] = x;
  m[3][1] = y;
  m[3][2] = z;
  return m;
}

template <class T>
mat4t<T> mat4t<T>::scale(T x, T y, T z) {
  mat4t m = identity();
  m[0][0] = x;
  m[1][1] = y;
  m[2][2] = z;
  return m;
}

template <class T>
mat4t<T> mat4t<T>::rotate_x(T angle) {
  mat4t m = identity();
  m[1][1] = cos(angle * deg2rad);
  m[1][2] = -sin(angle * deg2rad);
  m[2][1] = -m[1][2];
  m[2][2] = m[1][1];
  return m;
}

template <class T>
mat4t<T> mat4t<T>::rotate_y(T angle) {
  mat4t m = identity();
  m[0][0] = cos(angle * deg2rad);
  m[0][2] = sin(angle * deg2rad);
  m[2][0] = -m[0][2];
  m[2][2] = m[0][0];
  return m;
}

template <class T>
mat4t<T> mat4t<T>::rotate_z(T angle) {
  mat4t m = identity();
  m[0][0] = cos(angle * deg2rad);
  m[0][1] = -sin(angle * deg2rad);
  m[1][0] = -m[0][1];
  m[1][1] = m[0][0];
  return m;
}

template <class T>
mat4t<T> mat4t<T>::transpose() const {
  return mat4t(
    mat[0][0], mat[1][0], mat[2][0], mat[3][0],
    mat[0][1], mat[1][1], mat[2][1], mat[3][1],
    mat[0][2], mat[1][2], mat[2][2], mat[3][2],
    mat[0][3], mat[1][3], mat[2][3], mat[3][3]);
}

template <class T>
vec4t<T> mat4t<T>::operator*(const vec4t<T>& v) const {
  return vec4t<T>(
    mat[0][0]*v.x + mat[0][1]*v.y + mat[0][2]*v.z + mat[0][3]*v.w,
    mat[1][0]*v.x + mat[1][1]*v.y + mat[1][2]*v.z + mat[1][3]*v.w,
    mat[2][0]*v.x + mat[2][1]*v.y + mat[2][2]*v.z + mat[2][3]*v.w,
    mat[3][0]*v.x + mat[3][1]*v.y + mat[3][2]*v.z + mat[3][3]*v.w);
}

template <class T>
mat4t<T> mat4t<T>::operator+(T f) const {
  return mat4t(mat[0][0]+f, mat[0][1]+f, mat[0][2]+f, mat[0][3]+f,
               mat[1][0]+f, mat[1][1]+f, mat[1][2]+f, mat[1][3]+f,
               mat[2][0]+f, mat[2][1]+f, mat[2][2]+f, mat[2][3]+f,
               mat[3][0]+f, mat[3][1]+f, mat[3][2]+f, mat[3][3]+f);
}

template <class T>
mat4t<T> mat4t<T>::operator-(T f) const {
  return mat4t(mat[0][0]-f, mat[0][1]-f, mat[0][2]-f, mat[0][3]-f,
               mat[1][0]-f, mat[1][1]-f, mat[1][2]-f, mat[1][3]-f,
               mat[2][0]-f, mat[2][1]-f, mat[2][2]-f, mat[2][3]-f,
               mat[3][0]-f, mat[3][1]-f, mat[3][2]-f, mat[3][3]-f);
}

template <class T>
mat4t<T> mat4t<T>::operator*(T f) const {
  return mat4t(mat[0][0]*f, mat[0][1]*f, mat[0][2]*f, mat[0][3]*f,
               mat[1][0]*f, mat[1][1]*f, mat[1][2]*f, mat[1][3]*f,
               mat[2][0]*f, mat[2][1]*f, mat[2][2]*f, mat[2][3]*f,
               mat[3][0]*f, mat[3][1]*f, mat[3][2]*f, mat[3][3]*f);
}

template <class T>
mat4t<T> mat4t<T>::operator/(T f) const {
  return mat4t(mat[0][0]/f, mat[0][1]/f, mat[0][2]/f, mat[0][3]/f,
               mat[1][0]/f, mat[1][1]/f, mat[1][2]/f, mat[1][3]/f,
               mat[2][0]/f, mat[2][1]/f, mat[2][2]/f, mat[2][3]/f,
               mat[3][0]/f, mat[3][1]/f, mat[3][2]/f, mat[3][3]/f);
}

template <class T>
mat4t<T> mat4t<T>::operator+(const mat4t& m) const {
  return mat4t(mat[0]+m[0], mat[1]+m[1], mat[2]+m[2], mat[3]+m[3]);
}

template <class T>
mat4t<T> mat4t<T>::operator-(const mat4t& m) const {
  return mat4t(mat[0]-m[0], mat[1]-m[1], mat[2]-m[2], mat[3]-m[3]);
}

template <class T>
mat4t<T> mat4t<T>::operator*(const mat4t& m) const {
  mat4t r;
  int i, j, k;
  for (i = 0; i < 4; ++i) {
    for (j = 0; j < 4; ++j) {
      for (k = 0; k < 4; ++k) {
        r[i][j] += mat[i][k] * m[k][j];
      }
    }
  }
  return r;
}

template <class T>
mat4t<T> mat4t<T>::operator+(const T arr[4][4]) const {
  return mat4t(mat[0]+arr[0], mat[1]+arr[1], mat[2]+arr[2], mat[3]+arr[3]);
}

template <class T>
mat4t<T> mat4t<T>::operator-(const T arr[4][4]) const {
  return mat4t(mat[0]-arr[0], mat[1]-arr[1], mat[2]-arr[2], mat[3]-arr[3]);
}

template <class T>
mat4t<T> mat4t<T>::operator*(const T arr[4][4]) const {
  mat4t r;
  int i, j, k;
  for (i = 0; i < 4; ++i) {
    for (j = 0; j < 4; ++j) {
      for (k = 0; k < 4; ++k) {
        r[i][j] += mat[i][k] * arr[k][j];
      }
    }
  }
  return r;
}

template <class T>
vec4t<T>& mat4t<T>::operator[](int i) {
  return mat[i];
}

template <class T>
const vec4t<T>& mat4t<T>::operator[](int i) const {
  return mat[i];
}

// Force creation of these classes since C++
// is a terrible programming language
// and C doesn't just decide not put things
// in the compilation unit.
// 
// This also HAS to be at the end of the file
// or this program will not compile because
// C++ will decide these templates aren't being
// used, even though I explicitly am using them.

template class vec2t<float>;
template class vec3t<float>;
template class vec4t<float>;
template class mat4t<float>;

template class vec2t<int>;
template class vec3t<int>;
template class vec4t<int>;
template class mat4t<int>;