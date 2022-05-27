#include <algorithm>
#include <random>
#include "win.hpp"
#include "util.hpp"
#include "tile_dirs.hpp"
#include "path_finding.hpp"
#include <iostream>

const int tile_size = 16;

void Win::generate_state(TileMap<SFTile>& tile_map) {
  int x = util::rnd_range(0, tile_map.width() - 1);
  int y = util::rnd_range(0, tile_map.height() - 1);

  tile_map.set_tile(x, y, SFTile(TileType::cell));

  std::vector<path_finding::Dir> dirs = {
    path_finding::Dir::left,
    path_finding::Dir::right,
    path_finding::Dir::up,
    path_finding::Dir::down,
    path_finding::Dir::up_left,
    path_finding::Dir::up_right,
    path_finding::Dir::down_left,
    path_finding::Dir::down_right
  };

  auto rd = std::random_device{}; 
  auto rng = std::default_random_engine{rd()};
  std::shuffle(std::begin(dirs), std::end(dirs), rng);

  int neighbour_count = 0;

  for (const auto& dir : dirs) {
    auto xy = path_finding::traverse({x, y}, dir);

    if (tile_map.in_bounds(xy.first,  xy.second)) {
      tile_map.set_tile(xy.first, xy.second, SFTile(TileType::cell));

      neighbour_count += 1;
    }

    if (neighbour_count == 3)
      break;
  }
}

void Win::create_window(int width, int height) {
  _ren.create(
    sf::VideoMode(width, height),
    _title.c_str()
  );
}

void Win::init() {
  const int tile_map_width = 50;
  const int tile_map_height = 50;

  _tile_map_layers.push_back(
    std::make_unique<TileMap<SFTile>>(
      tile_map_width,
      tile_map_height,
      SFTile(TileType::background)
    )
  );

  generate_state(*_tile_map_layers.back());
  
  auto get_tile_id = [](SFTile const& tile) {
    return std::size_t(tile.current_tile());
  };
  
  _sf_tile_engine = std::make_unique<SFTileEngine<SFTile>>(
    tile_size,
    get_tile_id,
    tile_dirs()
  );

  create_window(tile_map_width * tile_size, tile_map_height * tile_size);
}

void Win::plot(int x, int y) {
  TileMap<SFTile>& tile_map = *_tile_map_layers.at(0);

  if (tile_map.in_bounds(x, y)) {
    TileType tile_type = (
      tile_map.get_tile(x, y).current_tile() ==
        TileType::background ? TileType::cell : TileType::background
    );

    tile_map.set_tile(x, y, SFTile(tile_type));
  }
}

void Win::next_turn() {
  TileMap<SFTile>& tile_map = *_tile_map_layers.at(0);
  std::vector<std::pair<int, int>> to_die;
  std::vector<std::pair<int, int>> to_live;

  for (int r = 0; r < tile_map.height(); r++) {
    for (int c = 0; c < tile_map.width(); c++) {
      int neighbour_count = 0;

      for (int nr = r - 1; nr <= r + 1; nr++)
        for (int nc = c - 1; nc <= c + 1; nc++)
          if (!(nr == r && nc == c))
            if (tile_map.in_bounds(nc, nr))
                if (tile_map.get_tile(nc, nr).current_tile() == TileType::cell)
                  neighbour_count += 1;

      if (neighbour_count < 2) {
        if (tile_map.get_tile(c, r).current_tile() == TileType::cell)
          to_die.push_back({c, r});
      }

      else if (neighbour_count == 3) {
        if (tile_map.get_tile(c, r).current_tile() == TileType::background)
          to_live.push_back({c, r});
      }

      else if (neighbour_count > 3) {
        if (tile_map.get_tile(c, r).current_tile() == TileType::cell)
          to_die.push_back({c, r});
      }
    }
  }

  for (const auto& pos : to_die)
    tile_map.set_tile(pos.first, pos.second, SFTile(TileType::background));

  for (const auto& pos : to_live)
    tile_map.set_tile(pos.first, pos.second, SFTile(TileType::cell));
}

Win::Win(const std::string& title, int fps) :
  _fps(fps), _title(title)
{
  _ren.setVerticalSyncEnabled(true);
  _ren.setFramerateLimit(_fps);
  init();
}

void Win::event_loop() {
  TileMap<SFTile>& tile_map = *_tile_map_layers.at(0);
  sf::Clock clock;
  bool pause = true;

  while (_ren.isOpen()) {
    sf::Event event{};

    while (_ren.pollEvent(event)) {
      if (event.type == sf::Event::Closed)
        _ren.close();

      else if (event.type == sf::Event::MouseButtonPressed) {
        if (event.mouseButton.button == sf::Mouse::Left)
          plot(
            event.mouseButton.x / tile_size,
            event.mouseButton.y / tile_size
          );
      }

      else if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::T)
          next_turn();

        else if (event.key.code == sf::Keyboard::R) {
          tile_map.clear(SFTile(TileType::background));
          generate_state(tile_map);
        }

        else if (event.key.code == sf::Keyboard::P)
          pause = !pause;
      }

    }

    if (!pause)
      if (clock.getElapsedTime().asMilliseconds() >= 500) {
        clock.restart();
        next_turn();
      }

    _ren.clear(sf::Color::Black);
    _sf_tile_engine->render(_ren, tile_map);
    _ren.display();
  }
}