#include "mesh.h"

#include <iostream>

Mesh::Mesh(const std::vector<Mesh::triangle_type>& triangles) {
  // Get unique vertexes
  std::set<Mesh::vertex_type> vertex_set;
  for (const auto& triangle : triangles) {
    vertex_set.insert(triangle.v0());
    vertex_set.insert(triangle.v1());
    vertex_set.insert(triangle.v2());
  }

  vertexes_.reserve(vertex_set.size());
  vertexes_.insert(vertexes_.end(), vertex_set.begin(), vertex_set.end());
  vertex_set.clear();

  std::map<Mesh::vertex_type,size_t> vertex_to_index;
  for (size_t i = 0; i < vertexes_.size(); ++i) {
    vertex_to_index[vertexes_[i]] = i;
  }

  for (const auto& triangle : triangles) {
    faces_.emplace_back(
      vertex_to_index[triangle.v0()],
      vertex_to_index[triangle.v1()],
      vertex_to_index[triangle.v2()]
    );
  }
}

size_t Mesh::size() const { return faces_.size(); }

Mesh::triangle_type Mesh::triangle(size_t i) const {
  return Mesh::triangle_type(
    vertexes_[std::get<0>(faces_[i])],
    vertexes_[std::get<1>(faces_[i])],
    vertexes_[std::get<2>(faces_[i])]
  );
}

std::ostream& Mesh::write_off_file(std::ostream& os) const {
  os << "OFF " << vertexes_.size() << " " << faces_.size() << " 0" << std::endl;

  for (const auto& vertex : vertexes_) {
    os << vertex.x() << " " << vertex.y() << " " << vertex.z() << std::endl;
  }

  for (const auto& face : faces_) {
    os << "3 " << std::get<0>(face) << " " << std::get<1>(face) << " " << std::get<2>(face) << std::endl;
  }

  return os;
}
