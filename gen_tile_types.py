import os

def get_tile_dirs():
  tiles_dir = "resources{0}tiles".format(os.sep)
  tile_dirs = {}
  
  for subdir, dirs, files in os.walk(tiles_dir):
    for file in files:
      tile_dir = subdir + os.sep + file
      tile_name = ""

      try:
        tile_name = tile_dir[len(tiles_dir) + 1:].replace(os.sep, "_")
      except IndexError:
        continue

      ext_pos = tile_name.find(".")

      if (ext_pos != -1):
        tile_name = tile_name[:ext_pos]
      
      tile_dirs[tile_name] = tile_dir

  return tile_dirs

def gen_tile_types(tile_types):
  tile_type_dir = "src{0}inc{0}tile_type.hpp".format(os.sep)
  
  if os.path.exists(tile_type_dir):
    os.remove(tile_type_dir)

  with open(tile_type_dir, "a") as tile_types_file:
    tile_types_file.write("#pragma once\n\n")
    tile_types_file.write("enum class TileType {\n")

    for i, tile_type in enumerate(tile_types):
      tile_types_file.write("  " + tile_type)

      if i != len(tile_types) - 1:
        tile_types_file.write(",\n")

    tile_types_file.write("\n};")

def gen_tile_dirs_hpp(tile_types, map_type):
  tile_dirs_hpp_dir = "src{0}inc{0}tile_dirs.hpp".format(os.sep)

  if os.path.exists(tile_dirs_hpp_dir):
    os.remove(tile_dirs_hpp_dir)

  with open(tile_dirs_hpp_dir, "a") as tile_dirs_hpp_file:
    tile_dirs_hpp_file.write("#pragma once\n\n")
    tile_dirs_hpp_file.write("#include <unordered_map>\n")
    tile_dirs_hpp_file.write("#include <cstddef>\n")
    tile_dirs_hpp_file.write("#include <string>\n")
    tile_dirs_hpp_file.write("#include \"tile_type.hpp\"\n\n")
    tile_dirs_hpp_file.write(map_type + " tile_dirs();")

def gen_tile_dirs_cpp(tile_dirs, map_type):
  tile_dirs_cpp_dir = "src{0}tile_dirs.cpp".format(os.sep)

  if os.path.exists(tile_dirs_cpp_dir):
    os.remove(tile_dirs_cpp_dir)
    
  with open(tile_dirs_cpp_dir, "a") as tile_dirs_cpp_file:
    tile_dirs_cpp_file.write("#include \"tile_dirs.hpp\"\n")
    tile_dirs_cpp_file.write("#include \"tile_type.hpp\"\n\n")
    tile_dirs_cpp_file.write(map_type + " tile_dirs() {\n")
    tile_dirs_cpp_file.write("  static {} _tile_dirs = {{\n".format(map_type))

    i = 0
    
    for name, path in tile_dirs.items():
      tile_dirs_cpp_file.write("    {{std::size_t(TileType::{}), R\"({})\"}}".format(name, path))

      if (i != len(tile_dirs) - 1):
        tile_dirs_cpp_file.write(",\n")

      i += 1
      
    tile_dirs_cpp_file.write("\n  };\n\n")
    tile_dirs_cpp_file.write("  return _tile_dirs;\n")
    tile_dirs_cpp_file.write("}")
    

def main():
  tile_dirs = get_tile_dirs()
  tile_types = tile_dirs.keys()

  gen_tile_types(tile_types)

  map_type = "const std::unordered_map<std::size_t, std::string>&"
  
  gen_tile_dirs_hpp(tile_types, map_type)
  gen_tile_dirs_cpp(tile_dirs, map_type)
  
if __name__ == "__main__":
  main()
