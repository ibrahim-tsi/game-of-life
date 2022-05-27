#pragma once

#include <vector>
#include <utility>
#include <unordered_map>
#include <string>
#include "tile_type.hpp"

class SFTile {
  TileType _static_tile_type;

public:
  TileType current_tile() const { return _static_tile_type; }
  
  explicit SFTile(TileType tile_type);
};