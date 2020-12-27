import os
import requests
import urllib.parse

from flask import redirect, render_template, request, session
from functools import wraps
from PIL import Image, ImageFilter

# Define a function for checksum
def checksum(number):
    """ Return true if checksum is valid """

    # Declare the variables
    result = 0
    count = 0
    tmp = number
    length = len(str(number))

    print("type(number) *helpers = " + str(type(number)))
    print("type(tmp) = " + str(type(tmp)))

    # Loop through the number to calculate checksum
    while count < length:
        digit = int(tmp % 10)

        tmp = int(tmp / 10)

        # If number is in the second-to-last group
        if count % 2 == 0:
            result += digit

        else:
            # If product is less than 10 (1 digit)
            if digit < 5:
                result += 2 * digit

            # If product is higher than 9 (2 digits)
            else:
                result += ((2 * digit) % 10) + 1

        count += 1

    return result % 10 == 0

### Filters functions
def grayscale(image_path:str)->Image:
    img = Image.open(image_path)
    width, height = img.size

    pixels = img.load() # create the pixel map

    for py in range(height):
        for px in range(width):
            r, g, b = img.getpixel((px, py))

            if r == g == b:
                continue

            else:
                average = (float)(r + g + b)/ 3

                tr = tg = tb = round(average)

            pixels[px, py] = (tr,tg,tb)

    return img

def reflect(image_path:str)->Image:
    img = Image.open(image_path)
    temp_img = Image.open(image_path)
    width, height = img.size

    pixels = img.load() # create the pixel map
    temp = temp_img.load() # create the pixel map

    for py in range(height):
        for px in range(width):
            r, g, b = temp_img.getpixel((px, py))

            temp[px, py] = (r,g,b)

        for px in range(width):
            pixels[px, py] = temp[width - px - 1, py]

    return img

def sepia(image_path:str)->Image:
    img = Image.open(image_path)
    width, height = img.size

    pixels = img.load() # create the pixel map

    for py in range(height):
        for px in range(width):
            r, g, b = img.getpixel((px, py))

            tr = int(0.393 * r + 0.769 * g + 0.189 * b)
            tg = int(0.349 * r + 0.686 * g + 0.168 * b)
            tb = int(0.272 * r + 0.534 * g + 0.131 * b)

            if tr > 255:
                tr = 255

            if tg > 255:
                tg = 255

            if tb > 255:
                tb = 255

            pixels[px, py] = (tr,tg,tb)

    return img
