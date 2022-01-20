from PIL import Image
from pathlib import Path
import sys

color_mapping = {
    0x000000: 0, # wall
    0x0000FF: 1, # pellet
    0xFFFFFF: 2, # path
    0xFFFF00: 3, # pen door
    0x00FF00: 4, # super pellet
    0xFF0000: 5, # pen
    0x00FFFF: 6, # portal 1
    0xFF00FF: 7  # portal 2
}

def fromRGB(c):
    return (c[0]<<16) + (c[1]<<8) + c[2]

def dump_as_array(path):
    img  = Image.open(path)
    w = img.size[0]
    h = img.size[1]
    name = Path(path).stem
    print("constexpr std::array<std::array<int, {}>, {}> {} = {{ {{".format(w, h, name))
    for y in range(0, h):
        print("{{{}{}{}".format(", ".join([str(color_mapping[fromRGB(img.getpixel((x, y)))]) for x in range(0, w)]), "}", "," if y < h-1 else "", "\n"))
    print("} };\n")

print("{}\n".format("#pragma once"))
print("{}\n".format("#include <array>"))
for n in range(1, len(sys.argv)):
    dump_as_array(sys.argv[n])
