#pragma once

#include <utility>
#include <string_view>
#include <string>
#include <functional>

namespace path_finding {
  enum class Dir {
    left,
    right,
    up,
    down,
    up_left,
    up_right,
    down_left,
    down_right
  };

  std::pair<int, int> traverse(std::pair<int, int> start, Dir dir);
}