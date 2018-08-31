#include "marching_cubes.h"

constexpr std::array<MarchingCubes::index_type,8>    MarchingCubes::CUBE_INDEX_SHIFTS;
constexpr std::array<MarchingCubes::vertex_type, 12> MarchingCubes::CUBE_EDGE_SHIFTS;
constexpr std::array<std::pair<size_t,size_t>, 12>   MarchingCubes::EDGE_VERTEXES;
constexpr std::array<int,256>                        MarchingCubes::EDGE_TABLE;
constexpr std::array<std::array<int, 16>, 256>       MarchingCubes::TRIANGLE_TABLE;
