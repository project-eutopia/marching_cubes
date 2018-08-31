#include "point.h"
#include "size.h"
#include "tensor.h"
#include "marching_cubes.h"

#include <cstdint>
#include <iostream>
#include <fstream>

// g++ -Wall --std=c++14 -g *.cpp -o main && ./main
int main() {
  Tensor<uint8_t,3> tensor({5u, 5u, 5u}, 0);

  tensor(1u, 1u, 1u) = 255u;
  tensor(2u, 1u, 1u) = 255u;
  tensor(3u, 1u, 1u) = 255u;
  tensor(1u, 2u, 1u) = 255u;
  tensor(1u, 3u, 1u) = 255u;
  tensor(1u, 1u, 2u) = 255u;
  tensor(1u, 1u, 3u) = 255u;

  /* Mesh mesh = MarchingCubes::polygonize_tensor<uint8_t>(tensor, [](uint8_t v) -> bool { return v > 127u; }); */
  Mesh mesh = MarchingCubes::polygonize_isosurface<uint8_t>(tensor, 127u);

  {
    std::ofstream ofs;
    ofs.open("test.off");
    mesh.write_off_file(ofs);
  }

  return 0;
}
