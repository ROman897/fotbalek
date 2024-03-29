//
// Created by roman on 4.4.2017.
//

#ifndef PV264_PROJECT_VECTOR2_H
#define PV264_PROJECT_VECTOR2_H
#include <cmath>

template <typename T> struct Vector2 {
  T m_x, m_y;

public:
  Vector2(T x, T y) : m_x(x), m_y(y) {}
  Vector2() : m_x(0), m_y(0) {}

  friend Vector2 operator+(Vector2 lhs, const Vector2 &rhs) {
    return lhs.add(rhs);
  }

  friend Vector2 &operator+=(Vector2 &lhs, const Vector2 &rhs) {
    return lhs.add(rhs);
  }

  friend Vector2 operator-(Vector2 lhs, const Vector2 &rhs) {
    return lhs.subtract(rhs);
  }

  friend Vector2 &operator-=(Vector2 &lhs, const Vector2 &rhs) {
    return lhs.subtract(rhs);
  }

  friend Vector2 operator/(Vector2 lhs, float rhs) { return lhs.divide(rhs); }

  friend Vector2 operator/=(Vector2 &lhs, float rhs) { return lhs.divide(rhs); }

  friend Vector2 operator*(Vector2 lhs, float rhs) { return lhs.multiply(rhs); }

  friend Vector2 operator*=(Vector2 &lhs, float rhs) {
    return lhs.multiply(rhs);
  }

  friend T DotProduct(Vector2 lhs, Vector2 rhs) {
    return lhs.m_x * rhs.m_x + lhs.m_y * rhs.m_y;
  }

  T lengthSquared() { return m_x * m_x + m_y * m_y; }

  T length() { return std::sqrt(m_x * m_x + m_y * m_y); }

  Vector2 getNormal() { return Vector2(-m_y, m_x); }

  void normalize() {
    auto len = length();
    if (len == 0)
      return;
    m_x /= len;
    m_y /= len;
  }

  void setLength(T len) {
    auto _len = length();
    if (_len == 0)
      return;
    m_x *= len / _len;
    m_y *= len / _len;
  }

  void limitLength(T len) {
    if (length() > len)
      setLength(len);
  }

  bool operator==(const Vector2 &rhs) const {
    return m_x == rhs.m_x && m_y == rhs.m_y;
  }

  bool operator!=(const Vector2 &rhs) const { return !(rhs == *this); }

private:
  Vector2 &add(const Vector2 &vec) {
    m_x += vec.m_x;
    m_y += vec.m_y;
    return *this;
  }
  Vector2 &subtract(const Vector2 &vec) {
    m_x -= vec.m_x;
    m_y -= vec.m_y;
    return *this;
  }
  Vector2 &divide(T divider) {
    m_x /= divider;
    m_y /= divider;
    return *this;
  }
  Vector2 &multiply(T multiplier) {
    m_x *= multiplier;
    m_y *= multiplier;
    return *this;
  }
};

#endif // PV264_PROJECT_VECTOR2_H
