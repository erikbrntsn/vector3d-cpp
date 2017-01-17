#pragma once
#include <array>
#include <cmath>
#include <ostream>

template<typename T>
class Vector {
private:
  std::array<T, 3> values_;

public:
  Vector() : values_{{0, 0, 0}} {}
  Vector(const T &a, const T &b, const T &c) : values_{{a, b, c}} {}
  Vector(const Vector<T> &rhs) : values_(rhs.values_) {}
  Vector(const std::array<T, 3> &rhs) : values_(rhs) {}
  template<typename TRhs>
  Vector(const Vector<TRhs> &rhs) : values_{{static_cast<T>(rhs[0]), static_cast<T>(rhs[1]), static_cast<T>(rhs[2])}} {};

  Vector& operator=(const Vector &vec) = default;

  T& operator[](unsigned i){
    return values_[i];
  }

  T operator[](unsigned i) const {
    return values_[i];
  }

  #define VECTOR_INPLACE_ARITHMETIC_OP(OPERATOR) \
  Vector<T>& operator OPERATOR (const Vector<T> &rhs){ \
    values_[0] OPERATOR rhs.values_[0]; \
    values_[1] OPERATOR rhs.values_[1]; \
    values_[2] OPERATOR rhs.values_[2]; \
    return *this; \
  }

  VECTOR_INPLACE_ARITHMETIC_OP(+=);
  VECTOR_INPLACE_ARITHMETIC_OP(-=);
  VECTOR_INPLACE_ARITHMETIC_OP(*=);
  VECTOR_INPLACE_ARITHMETIC_OP(/=);
  #undef VECTOR_INPLACE_ARITHMETIC_OP

  #define VECTOR_INPLACE_ARITHMETIC_OP(OPERATOR) \
  template<typename TRhs> \
  Vector<T>& operator OPERATOR (const TRhs &rhs){ \
    values_[0] OPERATOR rhs; \
    values_[1] OPERATOR rhs; \
    values_[2] OPERATOR rhs; \
    return *this; \
  }

  VECTOR_INPLACE_ARITHMETIC_OP(+=);
  VECTOR_INPLACE_ARITHMETIC_OP(-=);
  VECTOR_INPLACE_ARITHMETIC_OP(*=);
  VECTOR_INPLACE_ARITHMETIC_OP(/=);
  #undef VECTOR_INPLACE_ARITHMETIC_OP

  T norm() const {
    return std::sqrt(values_[0] * values_[0] +
                     values_[1] * values_[1] +
                     values_[2] * values_[2]);
  }

  Vector<T> operator-() const {
    return {-values_[0], -values_[1], -values_[2]};
  }

  void normalize(){
    *this /= norm();
  }

  void normalizeSafely(){
    T norm_ = norm();
    if (norm_ != 0.0) {
      *this /= norm_;
    }
  }

  Vector<T> cross(const Vector<T> &rhs) const {
    return {values_[1]*rhs.values_[2] - values_[2]*rhs.values_[1],
            values_[2]*rhs.values_[0] - values_[0]*rhs.values_[2],
            values_[0]*rhs.values_[1] - values_[1]*rhs.values_[0]};
  }

  T dot(const Vector<T> &rhs) const {
    return values_[0]*rhs.values_[0] + values_[1]*rhs.values_[1] + values_[2]*rhs.values_[2];
  }

  typename decltype(values_)::iterator begin(){
    return values_.begin();
  }

  typename decltype(values_)::iterator end(){
    return values_.end();
  }

  typename decltype(values_)::const_iterator cbegin() const {
    return values_.cbegin();
  }

  typename decltype(values_)::const_iterator cend() const {
    return values_.cend();
  }
};

template<typename T>
Vector<T> operator*(Vector<T> lhs, const Vector<T> &rhs) {
  lhs *= rhs;
  return lhs;
}

template<typename T>
Vector<T> operator/(Vector<T> lhs, const Vector<T> &rhs) {
  lhs *= 1/rhs;
  return lhs;
}

template<typename T>
Vector<T> operator+(Vector<T> lhs, const Vector<T> &rhs) {
  lhs += rhs;
  return lhs;
}

template<typename T>
Vector<T> operator-(Vector<T> lhs, const Vector<T> &rhs) {
  lhs -= rhs;
  return lhs;
}

template<typename T, typename TRhs>
Vector<T> operator*(Vector<T> lhs, const TRhs &rhs) {
  lhs *= rhs;
  return lhs;
}

template<typename T, typename TRhs>
Vector<T> operator/(Vector<T> lhs, const TRhs &rhs) {
  lhs *= 1/rhs;
  return lhs;
}

template<typename T, typename TRhs>
Vector<T> operator+(Vector<T> lhs, const TRhs &rhs) {
  lhs += rhs;
  return lhs;
}

template<typename T, typename TRhs>
Vector<T> operator-(Vector<T> lhs, const TRhs &rhs) {
  lhs -= rhs;
  return lhs;
}

template<typename T, typename TRhs>
Vector<T> operator*(const TRhs &lhs, Vector<T> rhs) {
  rhs *= lhs;
  return rhs;
}

template<typename T, typename TRhs>
Vector<T> operator/(const TRhs &lhs, Vector<T> rhs) {
  rhs *= 1/lhs;
  return rhs;
}

template<typename T, typename TRhs>
Vector<T> operator+(const TRhs &lhs, Vector<T> rhs) {
  rhs += lhs;
  return rhs;
}

template<typename T, typename TRhs>
Vector<T> operator-(const TRhs &lhs, Vector<T> rhs) {
  rhs -= lhs;
  return rhs;
}

template <typename T>
std::ostream &operator<<(std::ostream &os, const Vector<T> &rhs) {
  os << rhs[0] << "," << rhs[1] << "," << rhs[2];
  return os;
}
