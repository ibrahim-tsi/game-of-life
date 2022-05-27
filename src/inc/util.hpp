#pragma once

#include <SFML/Graphics.hpp>

namespace util {
  int rnd_range(int min, int max);
}

namespace util_sf {
  void resize_sprite(sf::Sprite& sprite, int width, int height);
  void resize_sprite(sf::Sprite& sprite, sf::Vector2u size);
}