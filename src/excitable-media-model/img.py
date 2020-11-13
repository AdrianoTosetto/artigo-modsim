import numpy as np
import re
import os

from PIL import Image


def create_image(filename, width, height):
    rgbArray = np.zeros((width, height, 3), dtype=np.uint8)
    file = open(filename).readlines()
    wIndex = 0
    hIndex = 0
    print(rgbArray.ndim)
    print(rgbArray.shape)
    for line in file:
        cleanLine = line.rstrip("\n")

        for rgbValue in cleanLine.split(";"):
            [red, green, blue] = rgbValue.split(",")

            rgbArray[wIndex][hIndex][0] = red
            rgbArray[wIndex][hIndex][1] = green
            rgbArray[wIndex][hIndex][2] = blue

            hIndex = hIndex + 1
        wIndex = wIndex + 1
        hIndex = 0
    
    image = Image.fromarray(rgbArray)

    imageFilename = filename.split(".")[0] + ".png"
    image.save(imageFilename)

def fileMatches(filename):
    match = re.search(r'snapshot\d+.txt', filename, re.M | re.I)

    return match != None

def generate_images():
    for filename in os.listdir():
        if (fileMatches(filename)):
            print("creating png file for " + filename)
            create_image(filename, 100, 150)
    pass

generate_images()
# create_image("snapshot1.txt", 100, 100)
# create_image("snapshot20.txt", 100, 100)
# create_image("snapshot45.txt", 100, 100)
# create_image("snapshot49.txt", 100, 100)
