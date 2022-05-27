#include "win.hpp"

int main() {
  Win win("Game of Life");

  win.event_loop();
  
  return 0;
}