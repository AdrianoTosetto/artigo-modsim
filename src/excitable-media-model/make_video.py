import os
import sys
import re
import glob

import numpy as np
import shlex
import cv2

def create_video(basefolder, videoFilename):
    img_array = []
    size = 0
    filesPattern = f"{basefolder}/*.png"

    for filename in sorted(glob.glob(filesPattern)):
        img = cv2.imread(filename)
        height, width, layers = img.shape
        size = (width,height)
        img_array.append(img)
    
    
    out = cv2.VideoWriter(f'{videoFilename}.avi',cv2.VideoWriter_fourcc(*'DIVX'), 15, size)
    
    for i in range(len(img_array)):
        out.write(img_array[i])
    out.release()

def prompt():

    baseFolder = " ".join(map(shlex.quote, sys.argv[1:2]))
    filename = " ".join(map(shlex.quote, sys.argv[2:3]))
    print(baseFolder)
    print(filename)
    create_video(baseFolder, filename)

prompt()