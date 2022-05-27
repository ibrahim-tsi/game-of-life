#pragma once

#include <vector>

template <typename T>
class TileMap {
  int _width{};
  int _height{};
  std::vector<std::vector<T>> _data{};

public:
  int width() const { return _width; }
  int height() const { return _height; }
  const std::vector<std::vector<T>>& data() const { return _data; }

  TileMap(int width, int height, const T& tile) : _width(width), _height(height) {
    std::vector<T> cols(width, tile);
    
    for (int r{0}; r < _height; r++)
      _data.push_back(cols);
  }

  void clear(T tile) {
    for (int r{0}; r < _height; r++)
      std::fill(_data.at(r).begin(), _data.at(r).end(), tile);
  }

  bool in_bounds(int c, int r) const {
    return c >= 0 && c < _width && r >= 0 && r < _height;
  }

  const T& get_tile(int c, int r) const {
    return _data.at(r).at(c);
  }
  
  void set_tile(int c, int r, T tile) {
    _data.at(r).at(c) = tile;
  }
};