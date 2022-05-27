#include "path_finding.hpp"

namespace path_finding {
  std::pair<int, int> traverse(std::pair<int, int> start, Dir dir) {
    std::pair<int, int> end(start);

    switch (dir) {
      case Dir::left:
        end.first -= 1;

        break;

      case Dir::right:
        end.first += 1;

        break;

      case Dir::up:
        end.second -= 1;

        break;

      case Dir::down:
        end.second += 1;

        break;

      case Dir::up_left:
        end.first -= 1;
        end.second -= 1;

        break;
      
      case Dir::up_right:
        end.first += 1;
        end.second -= 1;

        break;

      case Dir::down_left:
        end.first -= 1;
        end.second += 1;

        break;

      case Dir::down_right:
        end.first += 1;
        end.second += 1;

        break;
    }

    return end;
  }
}