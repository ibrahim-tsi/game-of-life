#include <string>
#include <cstddef>
#include <string>
#include <memory>
#include <vector>
#include "sf_tile.hpp"
#include "sf_tile_engine.hpp"
#include "tile_map.hpp"
#include "tile_type.hpp"
#include <SFML/Graphics.hpp>

class Win {
  std::string _title;
  int _fps;
  sf::RenderWindow _ren;
  std::vector<std::unique_ptr<TileMap<SFTile>>> _tile_map_layers;
  std::unique_ptr<SFTileEngine<SFTile>> _sf_tile_engine;

  void generate_state(TileMap<SFTile>& tile_map);
  void create_window(int width, int height);
  void init();
  void plot(int x, int y);
  void next_turn();

public:
  explicit Win(const std::string& title, int fps = 24);

  void event_loop();
};