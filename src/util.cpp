#include <random>
#include "util.hpp"

namespace util {
  int rnd_range(int min, int max) { // both inclusive
    static std::random_device dev{};
    std::mt19937 rng{dev()};
    std::uniform_int_distribution<int> dist{min, max};

    return dist(rng);
  }
}

namespace util_sf {
  void resize_sprite(sf::Sprite& sprite, int width, int height) {
    auto size{sprite.getTexture()->getSize()};

    sprite.setScale((float)width / size.x, (float)height / size.y);
  }

  void resize_sprite(sf::Sprite& sprite, sf::Vector2u size) {
    resize_sprite(sprite, (int)size.x, (int)size.y);
  }
}