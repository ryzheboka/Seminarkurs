"""label_images.py [path to the image-directory] [count_position]: Used for easy data labeling according to following rules:
    violet candle is denoted with "v" by user
    cub is denotes with "c" by user
    "l" means the object is on the left side
     "m" means the object is in the middle
     "r" means the object is on the right side
if there are two objects, only the candle is recognized

You should first note the kind of the object on the screen, and then it's place
Images are expected in specified directory

if count_position is '1', the images are labeled as following:
    vl - 0
    vm - 1
    vr - 2
    cl - 3
    cm - 4
    cr - 5
    nl - 6 (nothing)
    nm - 7 (black screen -> a camera error, take one more photo)

else, the images are labeled in the following way:
    l - 0
    r - 1
    o - 2
    n - 4 (nothing)
    e - 3 (camera error)

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
    """
    ims: list with images in form of numpy arrays
    titels: list with names of given images

    shows ims and asks the user for their labels. Then appends the label to the global list of all labels."""
    fig = plt.figure()
    size = len(ims)

    """
    Pyplot has two versions for notating the parameters of Subplot:
    The first notation: subplot(num_rows, num_cols, plot_number)
    The second notation: subplot(num_rows*100+num_cols*10+plot_number)
    The second notation is more convenient for smaller numbers, and is used in the snippet below

    See documentation of Pyplot for details.
    """
    rows = int(math.ceil(math.sqrt(size)) * 100)  # number of rows in the plot is rounded square root
    cols = math.ceil((size / (rows / 100))) * 10  # number of columns equals number of plots/number of rows (rounded up)

    for i in range(size):
        sub = fig.add_subplot(rows + cols + i + 1)      # creating a subplot
        sub.axis("off")     # remove Axis
        plt.title(titels[i])    # append the title
        sub.imshow(ims[i] / 255)  # normalizing images

    # put subplots together, less free space in between
    fig.tight_layout()
    plt.subplots_adjust(wspace=0.1, hspace=0.1)

    # show the figure without blocking input
    plt.show(block=False)

    # read user input for each image, translate it into label, then append the label
    for j in range(len(ims)):
        usr_label = input("Write the label for the picture " + str(j + 1) + ": ")
        label = labels_dictionary[usr_label]
        labels.append(label)

    # close the plot
    plt.close()


if __name__ == "__main__":

    directory = sys.argv[1]  # reads the path where to read the data from (first command line argument)
    classify_place = sys.argv[2]    # if true, define the position in label, else define only the class without position
    print(classify_place)

    if os.path.isfile("data/x_no_augmentation_" + directory.split("/")[-1]+".npy"):
        #   read labeled images
        my_images = np.load("data/x_no_augmentation_" + directory.split("/")[-1]+".npy").tolist()
        labels = np.load("data/y_no_augmentation_" + directory.split("/")[-1]+".npy").tolist()
        labeled_names = np.load("data/file_names_" + directory.split("/")[-1]+".npy").tolist()
    else:
        my_images = list()  # initializing a list with images
        labels = list()  # initializing a list with labels
        labeled_names = list()

    if classify_place=="1":
        labels_dictionary = {"vl": 0,"vm": 1,"vr": 2, "cl": 3, "cm": 4, "cr": 5, "nl": 6, "nm": 7}  # number equivalents for letter-labels
    else:
        labels_dictionary = {"l": 0, "r": 1, "o": 2, "e": 3, "n": 4}
    current_images = list()

    for file in os.listdir(directory):
        #   reading all images into my_images
        if ".jpg" in file and file not in labeled_names:
            image_array = np.asarray(Image.open(directory + "/" + file))
            current_images.append(image_array)
            my_images.append(image_array)
            labeled_names.append(file)

    while len(current_images) > 4:
        #   labeling 4 next images
        show_images(current_images[:4], range(1, 5))
        current_images = current_images[4:]  # deleting labeled images from list

    # labeling the rest
    if len(current_images):
        show_images(current_images, range(1, len(current_images) + 1))

    #   saving labels, images and corresponding file names
    np.save("data/y_no_augmentation_" + directory.split("/")[-1], np.array(labels))
    np.save("data/x_no_augmentation_" + directory.split("/")[-1], np.array(my_images))
    np.save("data/file_names_" + directory.split("/")[-1], np.array(labeled_names))
