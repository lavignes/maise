/**
 * maths.h: A cleaner and typesafe implementation of provided maths functions.
 * @author Scott LaVigne
 */
#ifndef MATHS_H
#define MATHS_H

#include <cmath>

#define clampf(v, min, max) (v < min)? min : (v > max)? max : v;

/**
 * A template class representing a 2D vector.
 */
template <class T>
struct vec2t {
  union {
    struct { T x, y; };
    struct { T s, t; };
    T vec[2];
  };

  /**
   * Constructors
   */
  explicit vec2t();
  explicit vec2t(T x, T y);
  explicit vec2t(const T arr[2]);

  /**
   * Assignment operators
   */
  const vec2t& operator=(const vec2t& v);
  const vec2t& operator=(const T arr[2]);

  /**
   * Return the same vector casted as an array.
   * @return pointer to first element in array
   */
  const T* as_array() const;

  /**
   * Calculate vector normal.
   * @return the normal
   */
  vec2t normal() const;

  /**
   * Add scalar.
   * @param f a scalar
   * @return a new vector of the result
   */
  vec2t operator+(T f) const;

  /**
   * Subtract scalar.
   * @param f a scalar
   * @return a new vector of the result
   */
  vec2t operator-(T f) const;

  /**
   * Multiply scalar.
   * @param f a scalar
   * @return a new vector of the result
   */
  vec2t operator*(T f) const;

  /**
   * Divide scalar.
   * @param f a scalar
   * @return a new vector of the result
   */
  vec2t operator/(T f) const;

  /**
   * Add vector.
   * @param f a vector
   * @return a new vector of the result
   */
  vec2t operator+(const vec2t& v) const;

  /**
   * Subtract vector.
   * @param f a vector
   * @return a new vector of the result
   */
  vec2t operator-(const vec2t& v) const;

  /**
   * Multiply vector.
   * @param f a vector
   * @return a new vector of the result
   */
  vec2t operator*(const vec2t& v) const;

  /**
   * Divide vector.
   * @param f a vector
   * @return a new vector of the result
   */
  vec2t operator/(const vec2t& v) const;

  /**
   * Vector dot product.
   * @param f a vector
   * @return a scalar result.
   */
  T dot(const vec2t& v) const;

  /**
   * Add array.
   * @param arr an array
   * @return a new vector of the result
   */
  vec2t operator+(const T arr[2]) const;

  /**
   * Subtract array.
   * @param arr an array
   * @return a new vector of the result
   */
  vec2t operator-(const T arr[2]) const;

  /**
   * Multiply array.
   * @param arr an array
   * @return a new vector of the result
   */
  vec2t operator*(const T arr[2]) const;

  /**
   * Divide array.
   * @param arr an array
   * @return a new vector of the result
   */
  vec2t operator/(const T arr[2]) const;

  /**
   * Array dot product.
   * @param arr an array
   * @return a new vector of the result
   */
  T dot(const T arr[2]) const;

  /**
   * Access element.
   * @param i element index
   * @return a reference to a scalar element
   */
  T& operator[](int i);

  /**
   * Access immutable element.
   * @param i element index
   * @return a reference to an immutable scalar element
   */
  const T& operator[](int i) const;
};

/**
 * A template class representing a 3D vector.
 */
template <class T>
struct vec3t {
  union {
    struct { T x, y, z; };
    struct { T r, g, b; };
    struct { T s, t, u; };
    T vec[3];
  };

  /**
   * Constructors
   */
  explicit vec3t();
  explicit vec3t(T x, T y, T z);
  explicit vec3t(const T arr[3]);
  explicit vec3t(const T arr[2], T z);
  explicit vec3t(const vec2t<T>& v, T z);

  /**
   * Assignment operators
   */
  const vec3t& operator=(const vec3t& v);
  const vec3t& operator=(const T arr[2]);

  /**
   * Return the same vector casted as an array.
   * @return pointer to first element in array
   */
  const T* as_array() const;

  /**
   * Calculate vector normal.
   * @return the normal
   */
  vec3t normal() const;

  /**
   * Add scalar.
   * @param f a vector
   * @return a new vector of the result
   */
  vec3t operator+(T f) const;

  /**
   * Subtract scalar.
   * @param f a vector
   * @return a new vector of the result
   */
  vec3t operator-(T f) const;

  /**
   * Multiply scalar.
   * @param f a vector
   * @return a new vector of the result
   */
  vec3t operator*(T f) const;

  /**
   * Divide scalar.
   * @param f a vector
   * @return a new vector of the result
   */
  vec3t operator/(T f) const;

  /**
   * Add vector.
   * @param f a vector
   * @return a new vector of the result
   */
  vec3t operator+(const vec3t& v) const;

  /**
   * Subtract vector.
   * @param f a vector
   * @return a new vector of the result
   */
  vec3t operator-(const vec3t& v) const;

  /**
   * Multiply vector.
   * @param f a vector
   * @return a new vector of the result
   */
  vec3t operator*(const vec3t& v) const;

  /**
   * Divide vector.
   * @param f a vector
   * @return a new vector of the result
   */
  vec3t operator/(const vec3t& v) const;

  /**
   * Vector dot product.
   * @param f a vector
   * @return a scalar result.
   */
  T dot(const vec3t& v) const;

  /**
   * Vector cross product.
   * @param f a vector
   * @return a new vector of the result
   */
  vec3t cross(const vec3t& v) const;

  /**
   * Add array.
   * @param arr an array
   * @return a new vector of the result
   */
  vec3t operator+(const T arr[3]) const;

  /**
   * Subtract array.
   * @param arr an array
   * @return a new vector of the result
   */
  vec3t operator-(const T arr[3]) const;

  /**
   * Multiply array.
   * @param arr an array
   * @return a new vector of the result
   */
  vec3t operator*(const T arr[3]) const;

  /**
   * Divide array.
   * @param arr an array
   * @return a new vector of the result
   */
  vec3t operator/(const T arr[3]) const;

  /**
   * Array dot product.
   * @param arr an array
   * @return a new vector of the result
   */
  T dot(const T arr[3]) const;

  /**
   * Array cross product.
   * @param arr an array
   * @return a new vector of the result
   */
  vec3t cross(const T arr[3]) const;
  
  /**
   * Access element.
   * @param i element index
   * @return a reference to a scalar element
   */
  T& operator[](int i);

  /**
   * Access immutable element.
   * @param i element index
   * @return a reference to an immutable scalar element
   */
  const T& operator[](int i) const;
};

/**
 * A template class representing a 4D vector.
 */
template <class T>
struct vec4t {
  union {
    struct { T x, y, z, w; };
    struct { T r, g, b, a; };
    struct { T s, t, u, v; };
    T vec[4];
  };

  /**
   * Constructors
   */
  explicit vec4t();
  explicit vec4t(T x, T y, T z, T w);
  explicit vec4t(const T arr[4]);
  explicit vec4t(const vec3t<T>& v, T w);
  explicit vec4t(const T arr[3], T w);
  explicit vec4t(const vec2t<T>& v, T z, T w);
  explicit vec4t(const T arr[2], T z, T w);

  /**
   * Assignment operators
   */
  const vec4t& operator=(const vec4t& v);
  const vec4t& operator=(const T arr[2]);

  /**
   * Return the same vector casted as an array.
   * @return pointer to first element in array
   */
  const T* as_array() const;

  /**
   * Calculate vector normal.
   * @return the normal
   */
  vec4t normal() const;

  /**
   * Add scalar.
   * @param f a vector
   * @return a new vector of the result
   */
  vec4t operator+(T f) const;

  /**
   * Subtract scalar.
   * @param f a vector
   * @return a new vector of the result
   */
  vec4t operator-(T f) const;

  /**
   * Multiply scalar.
   * @param f a vector
   * @return a new vector of the result
   */
  vec4t operator*(T f) const;

  /**
   * Divide scalar.
   * @param f a vector
   * @return a new vector of the result
   */
  vec4t operator/(T f) const;

  /**
   * Add vector.
   * @param f a vector
   * @return a new vector of the result
   */
  vec4t operator+(const vec4t& v) const;

  /**
   * Subtract vector.
   * @param f a vector
   * @return a new vector of the result
   */
  vec4t operator-(const vec4t& v) const;

  /**
   * Multiply vector.
   * @param f a vector
   * @return a new vector of the result
   */
  vec4t operator*(const vec4t& v) const;

  /**
   * Divide vector.
   * @param f a vector
   * @return a new vector of the result
   */
  vec4t operator/(const vec4t& v) const;

  /**
   * Vector dot product.
   * @param f a vector
   * @return a scalar result.
   */
  T dot(const vec4t& v) const;

  /**
   * Add array.
   * @param arr an array
   * @return a new vector of the result
   */
  vec4t operator+(const T arr[4]) const;

  /**
   * Subtract array.
   * @param arr an array
   * @return a new vector of the result
   */
  vec4t operator-(const T arr[4]) const;

  /**
   * Multiply array.
   * @param arr an array
   * @return a new vector of the result
   */
  vec4t operator*(const T arr[4]) const;

  /**
   * Divide array.
   * @param arr an array
   * @return a new vector of the result
   */
  vec4t operator/(const T arr[4]) const;

  /**
   * Array dot product.
   * @param arr an array
   * @return a new vector of the result
   */
  T dot(const T arr[4]) const;

  /**
   * Access element.
   * @param i element index
   * @return a reference to a scalar element
   */
  T& operator[](int i);

  /**
   * Access immutable element.
   * @param i element index
   * @return a reference to an immutable scalar element
   */
  const T& operator[](int i) const;
};

/**
 * A template class representing a 4x4 matrix.
 */
template <class T>
struct mat4t {
  vec4t<T> mat[4];

  /**
   * Constructors
   */
  explicit mat4t();
  explicit mat4t(T e00, T e01, T e02, T e03,
        T e10, T e11, T e12, T e13,
        T e20, T e21, T e22, T e23,
        T e30, T e31, T e32, T e33);
  explicit mat4t(const vec4t<T>& v1, const vec4t<T>& v2,
        const vec4t<T>& v3, const vec4t<T>& v4);
  explicit mat4t(const T arr[4][4]);

  /**
   * Assignment operators
   */
  const mat4t& operator=(const mat4t& m);
  const mat4t& operator=(const T arr[4][4]);

  /**
   * Return the same matrix casted as an array.
   * @return pointer to first element in array
   */
  const T* as_array() const;

  /**
   * Return identity matrix.
   * @return an identity matrix
   */
  static mat4t identity();

  /**
   * Generate translation matrix
   * @param  x x-axis translation
   * @param  y y-axis translation
   * @param  z z-axis translation
   * @return   a translation matrix
   */
  static mat4t translate(T x, T y, T z);

  /**
   * Generate scale matrix
   * @param  x x-axis scale
   * @param  y y-axis scale
   * @param  z z-axis scale
   * @return   a scale matrix
   */
  static mat4t scale(T x, T y, T z);

  /**
   * Generate x-axis rotation matrix
   * @param  angle an angle in degrees
   * @return       a rotation matrix
   */
  static mat4t rotate_x(T angle);

  /**
   * Generate y-axis rotation matrix
   * @param  angle an angle in degrees
   * @return       a rotation matrix
   */
  static mat4t rotate_y(T angle);

  /**
   * Generate z-axis rotation matrix
   * @param  angle an angle in degrees
   * @return       a rotation matrix
   */
  static mat4t rotate_z(T angle);

  /**
   * Transpose a matrix.
   * @return the transposed form of the matrix
   */
  mat4t transpose() const;

  /**
   * Vector multiply.
   * @param v a 4D vector
   * @return  a 4D result vector
   */
  vec4t<T> operator*(const vec4t<T>& v) const;

  /**
   * Add scalar.
   * @param f a scalar
   * @return  the result matrix
   */
  mat4t operator+(T f) const;

  /**
   * Subtract scalar.
   * @param f a scalar
   * @return  the result matrix
   */
  mat4t operator-(T f) const;

  /**
   * Multiply scalar.
   * @param f a scalar
   * @return  the result matrix
   */
  mat4t operator*(T f) const;

  /**
   * Divide scalar.
   * @param f a scalar
   * @return  the result matrix
   */
  mat4t operator/(T f) const;

  /**
   * Add matrix.
   * @param m a matrix
   * @return  the result matrix
   */
  mat4t operator+(const mat4t& m) const;

  /**
   * Subtract matrix.
   * @param m a matrix
   * @return  the result matrix
   */
  mat4t operator-(const mat4t& m) const;

  /**
   * Multiply matrix.
   * @param m a matrix
   * @return  the result matrix
   */
  mat4t operator*(const mat4t& m) const;

  /**
   * Add array.
   * @param arr an array
   * @return    the result matrix
   */
  mat4t operator+(const T arr[4][4]) const;

  /**
   * Subtract array.
   * @param arr an array
   * @return    the result matrix
   */
  mat4t operator-(const T arr[4][4]) const;

  /**
   * Multiply array.
   * @param arr an array
   * @return    the result matrix
   */
  mat4t operator*(const T arr[4][4]) const;

  /**
   * Access element.
   * @param i element index
   * @return a reference to a vector row element
   */
  vec4t<T>& operator[](int i);

  /**
   * Access immutable element.
   * @param i element index
   * @return a reference to an immutable vector row element
   */
  const vec4t<T>& operator[](int i) const;
};

typedef vec2t<float> vec2;
typedef vec3t<float> vec3;
typedef vec4t<float> vec4;
typedef mat4t<float> mat4;

typedef vec2t<int> vec2i;
typedef vec3t<int> vec3i;
typedef vec4t<int> vec4i;
typedef mat4t<int> mat4i;

#endif // MATHS_H
