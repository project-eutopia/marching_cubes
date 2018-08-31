#pragma once

#include <vector>
#include <set>
#include <map>

#include "point.h"
#include "size.h"
#include "triangle.h"

class Mesh {
  public:
    using triangle_type = Triangle<double,3>;
    using vertex_type = triangle_type::vertex_type;
    using size_type = Size<size_t,3>;
    using index_type = Point<size_t,3>;

  private:
    std::vector<vertex_type> vertexes_;
    std::vector<std::tuple<size_t,size_t,size_t>> faces_;

  public:
    explicit Mesh(const std::vector<triangle_type>& triangles);

    size_t size() const;
    triangle_type triangle(size_t i) const;

    std::ostream& write_off_file(std::ostream& os) const;
};

