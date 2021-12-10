from PIL import Image
import math
from io import BytesIO
from PIL import ImageFilter
from PIL import ImageEnhance
from IPython.display import display
import numpy as np

img = Image.open("/home/cor3ntin/dev/modcpp/ms-pacman/assets/maze.png")
out = Image.new('RGB', (28, 31), color = 'white')

for x in range(0, img.size[0]):
    for y in range(0, img.size[1]):
        r, g, b, a = img.getpixel((x, y))
        if r != 0 or g != 0 or b != 0:
            out.putpixel([math.floor(x/16), math.floor(y/16)], (0, 0, 0))
display(out)

im1 = out.save("/home/cor3ntin/dev/modcpp/ms-pacman/assets/maze_data.bmp")
