#pragma once

#include "point.h"

template <typename T, size_t N>
class Triangle {
  static_assert(N >= 2, "N must be at least 2 for Triangle");

  public:
    using vertex_type = Point<T,N>;

  private:
    const vertex_type v0_, v1_, v2_;

  public:
    constexpr explicit Triangle(const vertex_type& v0, const vertex_type& v1, const vertex_type& v2) : v0_(v0), v1_(v1), v2_(v2) {}
    constexpr explicit Triangle(vertex_type&& v0, vertex_type&& v1, vertex_type&& v2) : v0_(std::move(v0)), v1_(std::move(v1)), v2_(std::move(v2)) {}

    const vertex_type& v0() const { return v0_; }
    const vertex_type& v1() const { return v1_; }
    const vertex_type& v2() const { return v2_; }

    bool operator==(const Triangle<T,N>& rhs) const { return v0() == rhs.v0() && v1() == rhs.v1() && v2() == rhs.v2(); }
    bool operator!=(const Triangle<T,N>& rhs) const { return !(*this == rhs); }
};

