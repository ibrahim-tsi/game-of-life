#include "tile_dirs.hpp"
#include "tile_type.hpp"

const std::unordered_map<std::size_t, std::string>& tile_dirs() {
  static const std::unordered_map<std::size_t, std::string>& _tile_dirs = {
    {std::size_t(TileType::background), R"(resources\tiles\background.png)"},
    {std::size_t(TileType::cell), R"(resources\tiles\cell.png)"}
  };

  return _tile_dirs;
}