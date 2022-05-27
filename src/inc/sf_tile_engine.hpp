#pragma once

#include <cassert>
#include <cstddef>
#include <functional>
#include <unordered_set>
#include <string>
#include <utility>
#include <SFML/Graphics.hpp>
#include "tile_map.hpp"
#include "util.hpp"

template <typename T>
class SFTileEngine {
  int _tile_size;
  std::function<std::size_t(T const& tile)> _get_tile_id;

  std::unordered_map<
    std::size_t, std::pair<sf::Texture, sf::Sprite>
  > _sprites{};

  void add_sprite(const std::pair<std::size_t, std::string>& id_path) {
    if (_sprites.contains(id_path.first))
      return;
    
    auto ret{_sprites.insert(
      {id_path.first, {sf::Texture(), sf::Sprite()}})
    };

    sf::Texture& tex{ret.first->second.first};

    assert(tex.loadFromFile(id_path.second));
    
    sf::Sprite& tile_sprite{ret.first->second.second};

    tile_sprite.setTexture(tex);
    util_sf::resize_sprite(tile_sprite, _tile_size, _tile_size);
  }

public:
  SFTileEngine(
    int tile_size,
    std::function<std::size_t(T const& tile)> get_tile_id,
    const std::unordered_map<std::size_t, std::string>& tile_dirs
  ) :
    _tile_size(tile_size),
    _get_tile_id(get_tile_id)
  {
    for (const auto& id_path : tile_dirs)
      add_sprite(id_path); 
  }

  void render(sf::RenderWindow& ren, const TileMap<T>& tile_map) {
    const sf::View& view = ren.getView();
    
    int start_x = (
      (int(view.getCenter().x) - (int(view.getSize().x) / 2)) / _tile_size
    );
    
    int start_y = (
      (int(view.getCenter().y) - (int(view.getSize().y) / 2)) / _tile_size
    );

    int width = int(view.getSize().x) / _tile_size;
    int height = int(view.getSize().y) / _tile_size;

    for (int c = start_x < 0 ? 0 : start_x;
      c < start_x + width + 1 && c < tile_map.width();
      c++)
    {
      for (int r = start_y < 0 ? 0 : start_y;
        r < start_y + height + 1 && r < tile_map.height();
        r++)
      {
        std::size_t id = _get_tile_id(tile_map.get_tile(c, r));
        sf::Sprite& tile_sprite = _sprites.at(id).second;

        tile_sprite.setPosition(c * _tile_size, r * _tile_size);
        ren.draw(tile_sprite);
      }
    }
  }
};