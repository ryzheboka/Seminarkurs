"""label_images.py [path to the image-directory]: Used for easy data labeling according to following rules:
    violet candle is denoted with "v" by user
    cub is denotes with "c" by user
    "l" means the object is on the left side
     "m" means the object is in the middle
     "r" means the object is on the right side
if there are two objects, only the candle is recognized

You should first note the kind of the object on the screen, and then it's place
Images are expected in specified directory

The images are labeled as following:
    vl - 0
    vm - 1
    vr - 2
    cl - 3
    cm - 4
    cr - 5
    nl - 6 (nothing)

Writes both the images and the labels in npy format into directory "data"
to run label_images.py, you need the directory "data" with the same path as the script
"""
import sys
from PIL import Image
from matplotlib import pyplot as plt
import numpy as np
import math
import os


def show_images(ims, titels):
    """partially taken from another project, needs to be commented properly

    ims: list with images in form of numpy arrays
    titels: list with names of given images

    shows ims and asks the user for their labels. Then appends the label to the global list of all labels."""
    fig = plt.figure()

    size = len(ims)
    rows = int(math.ceil(math.sqrt(size)) * 100)
    cols = math.ceil((size / (rows / 100))) * 10

    for i in range(size):
        sub = fig.add_subplot(rows + cols + i + 1)
        sub.axis("off")
        plt.title(titels[i])
        sub.imshow(ims[i] / 255)  # normalizing images

    fig.tight_layout()
    plt.subplots_adjust(wspace=0.1, hspace=0.1)
    plt.show(block=False)  # block = False means input is accepted during show
    for j in range(len(ims)):
        usr_label = input("Write the label for the picture " + str(j+1) + ": ")
        labels.append(labels_dictionary[usr_label[0]] + labels_dictionary[usr_label[1]])
    plt.close()


if __name__ == "__main__":

    directory = sys.argv[1]     # reads the path where to read the data from (first command line argument)
    labels_dictionary = {"v": 0, "c": 3, "l": 0, "m": 1, "r": 2, "n": 6}    # number equivalents for letter-labels
    my_images = list()  # initializing a list with images
    labels = list()     # initializing a list with labels

    for file in os.listdir(directory):
        #   reading all images into my_images
        if ".jpg" in file:
            my_images.append(np.asarray(Image.open(directory + "/" + file)))

    while len(my_images) > 4:
        #   labeling 4 next images
        show_images(my_images[:4], range(1, 5))
        my_images = my_images[4:]   # deleting labeled images from list

    #   labeling the rest
    show_images(my_images, range(1, len(my_images) + 1))

    #   saving
    np.save("data/labels_" + directory.split("/")[-1], np.array(labels))
    np.save("data/processed_" + directory.split("/")[-1], np.array(my_images))
    print(os.listdir(directory))
