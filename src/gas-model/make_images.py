import numpy as np
import re
import os
import sys
import shlex

from PIL import Image

BASE_FOLDER = ""

def create_image(filename):
    rgbArray = None

    with open(f'{BASE_FOLDER}/{filename}') as file:
        lines = file.readlines()

        header = lines[0]
        dim = header.split(",")

        width  = int(dim[0])
        height = int(dim[1])
        wIndex = 0
        hIndex = 0

        rgbArray = np.zeros((width, height, 3), dtype=np.uint8)

        for line in lines[1:]:

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
    filenameNoExt = filename.split(".")[0]
    imageFilename = f"{BASE_FOLDER}/{filenameNoExt}.png"

    image.save(imageFilename)

def fileMatches(filename):
    match = re.search(r'snapshot\d+.txt', filename, re.M | re.I)

    return match != None

def generate_images(targetFolder):
    print(targetFolder)
    for filename in os.listdir(targetFolder):
        if (fileMatches(filename)):
            print(f"creating png file for {targetFolder}/{filename}")
            create_image(filename)


def prompt():

    cmdline = " ".join(map(shlex.quote, sys.argv[1:]))
    global BASE_FOLDER
    BASE_FOLDER = cmdline
    generate_images(cmdline)

prompt()

# create_image("snapshot1.txt", 100, 100)
# create_image("snapshot20.txt", 100, 100)
# create_image("snapshot45.txt", 100, 100)
# create_image("snapshot49.txt", 100, 100)
