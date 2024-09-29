from PIL import Image
import sys
name=sys.argv[1]
x=sys.argv[2]
y=sys.argv[3]
xsize=sys.argv[4]
ysize=sys.argv[5]
x=int(x)
y=int(y)
xsize=int(xsize)
ysize=int(ysize)
day  =  Image.open("assets/graphics/terrain/day.png")
morning=Image.open("assets/graphics/terrain/morning.png")
night = Image.open("assets/graphics/terrain/night.png")
tday=day.crop((x,y,x+xsize,y+ysize))
print("day saved!")
tmorning=morning.crop((x,y,x+xsize,y+ysize))
print("morning saved!")
tnight=night.crop((x,y,x+xsize,y+ysize))
print("night saved!")
tday.save(f"assets/graphics/terrain/d{name}.png")
tnight.save(f"assets/graphics/terrain/n{name}.png")
tmorning.save(f"assets/graphics/terrain/m{name}.png")
