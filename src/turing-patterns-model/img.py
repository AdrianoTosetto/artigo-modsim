import numpy as np
import re
import os
import sys
import shlex

from PIL import Image

BASE_FOLDER = ""

def create_image(filename, width, height):
    rgbArray = np.zeros((width, height, 3), dtype=np.uint8)
    file = open(BASE_FOLDER + "/" + filename).readlines()
    wIndex = 0
    hIndex = 0

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

    imageFilename = BASE_FOLDER + "/" + filename.split(".")[0] + ".png"

    image.save(imageFilename)

def fileMatches(filename):
    match = re.search(r'snapshot\d+.txt', filename, re.M | re.I)

    return match != None

def generate_images(targetFolder):
    print(targetFolder)
    for filename in os.listdir(targetFolder):
        if (fileMatches(filename)):
            print("creating png file for " + targetFolder + "/" + filename)
            create_image(filename, 400, 400)


def prompt():
    print("Type the folder target without the slash. This folder is where the ")
    print("snapshotsXX.txt are located")
    cmdline = " ".join(map(shlex.quote, sys.argv[1:]))
    global BASE_FOLDER
    BASE_FOLDER = cmdline
    generate_images(cmdline)

prompt()

# create_image("snapshot1.txt", 100, 100)
# create_image("snapshot20.txt", 100, 100)
# create_image("snapshot45.txt", 100, 100)
# create_image("snapshot49.txt", 100, 100)
