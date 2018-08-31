#pragma once

#include <tuple>
#include <ostream>

template <typename T, size_t N>
class Point {
  public:
    using value_type = T;

  private:
    std::array<T,N> elements_;

  public:

    constexpr Point() : elements_() {}

    template <typename ... Args>
    constexpr Point(const Args& ... args) : elements_{args...} {}

    const T& operator()(size_t i) const { return elements_[i]; }
    T&       operator()(size_t i)       { return elements_[i]; }

    const T& operator[](size_t i) const { return elements_[i]; }
    T&       operator[](size_t i)       { return elements_[i]; }

    auto begin()       { return elements_.begin(); }
    auto end()         { return elements_.end();   }
    auto begin() const { return elements_.begin(); }
    auto end()   const { return elements_.end();   }

    T x() const {
      static_assert(N >= 1, "N must be greater than 1 to call x()");
      return (*this)(0);
    }

    T y() const {
      static_assert(N >= 2, "N must be greater than 2 to call y()");
      return (*this)(1);
    }

    T z() const {
      static_assert(N >= 3, "N must be greater than 3 to call z()");
      return (*this)(2);
    }

    T w() const {
      static_assert(N >= 4, "N must be greater than 4 to call w()");
      return (*this)(3);
    }

    template <typename U>
    auto operator+=(const Point<U,N>& rhs) {
      for (size_t i = 0; i < N; ++i) {
        (*this)(i) += rhs(i);
      }
      return *this;
    }

    template <typename U>
    auto operator-=(const Point<U,N>& rhs) {
      for (size_t i = 0; i < N; ++i) {
        (*this)(i) -= rhs(i);
      }
      return *this;
    }

    template <typename U>
    auto operator*=(const U& rhs) {
      for (size_t i = 0; i < N; ++i) {
        (*this)(i) *= rhs;
      }
      return *this;
    }

    template <typename U>
    auto operator/=(const U& rhs) {
      for (size_t i = 0; i < N; ++i) {
        (*this)(i) /= rhs;
      }
      return *this;
    }

    T sum() const {
      T total(0);
      for (const auto& f : elements_) total += f;
      return total;
    }

    T prod() const {
      T factor(1);
      for (const auto& f : elements_) factor *= f;
      return factor;
    }
};

template <typename T, typename U, size_t N>
bool operator<(const Point<T,N>& lhs, const Point<U,N>& rhs) {
  for (size_t i = 0; i < N-1; ++i) {
    if (lhs(i) < rhs(i)) return true;
    if (lhs(i) > rhs(i)) return false;
  }

  return lhs(N-1) < rhs(N-1);
}

template <typename T, typename U, size_t N>
bool operator==(const Point<T,N>& lhs, const Point<U,N>& rhs) {
  for (size_t i = 0; i < N; ++i) {
    if (lhs(i) != rhs(i)) return false;
  }
  return true;
}

template <typename T, typename U, size_t N>
bool operator!=(const Point<T,N>& lhs, const Point<U,N>& rhs) {
  return !(lhs == rhs);
}

template <typename T, typename U, size_t N>
auto operator+(const Point<T,N>& lhs, const Point<U,N>& rhs) {
  Point<decltype(T(0) + U(0)),N> p;

  for (size_t i = 0; i < N; ++i) {
    p(i) = lhs(i) + rhs(i);
  }

  return p;
}

template <typename T, typename U, size_t N>
auto operator-(const Point<T,N>& lhs, const Point<U,N>& rhs) {
  Point<decltype(T(0) - U(0)),N> p;

  for (size_t i = 0; i < N; ++i) {
    p(i) = lhs(i) - rhs(i);
  }

  return p;
}

template <typename T, typename U, size_t N>
auto operator*(const Point<T,N>& lhs, const U& rhs) {
  Point<decltype(T(0) * U(0)),N> p;

  for (size_t i = 0; i < N; ++i) {
    p(i) = lhs(i) * rhs;
  }

  return p;
}

template <typename T, typename U, size_t N>
auto operator*(const T& lhs, const Point<U,N>& rhs) {
  Point<decltype(T(0) * U(0)),N> p;

  for (size_t i = 0; i < N; ++i) {
    p(i) = lhs * rhs(i);
  }

  return p;
}

template <typename T, typename U, size_t N>
auto operator/(const Point<T,N>& lhs, const U& rhs) {
  Point<decltype(T(0) / U(0)),N> p;

  for (size_t i = 0; i < N; ++i) {
    p(i) = lhs(i) / rhs;
  }

  return p;
}

template <typename T, size_t N>
std::ostream& operator<<(std::ostream& os, const Point<T,N>& p) {
  for (size_t i = 0; i < N; ++i) {
    os << p(i);
    if (i < N-1) os << ",";
  }
  return os;
}
