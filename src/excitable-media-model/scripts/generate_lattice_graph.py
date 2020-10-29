from random import randrange

f = open('image_array.txt', "w")

for i in range(0, 500):
    for j in range(0, 500):
        f.write(str(randrange(0, 255)))


def create_image_from_rbg_array(file_path, width, height):
    pass