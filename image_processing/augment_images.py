"""augments images by flipping them. Then saves both, the original and the augmented images+labels in the npy format."""

import numpy as np
import sys


def augmentation():
    #   initializing arrays with augmented data
    augmented_images = np.zeros_like(my_images)
    augmented_labels = np.zeros_like(labels)

    for i, image in enumerate(my_images):   # iterate over each image and corresponding index
        augmented_images[i] = (np.fliplr(image))  # augment image and insert it
        augmented_labels[i] = (reflection_dict[labels[i]])   # read the corresponding label and insert it

    return augmented_images, augmented_labels

if __name__ == "__main__":

    directory = sys.argv[1]  # reads the path where to read the data from (first command line argument)
    reflection_dict = {0: 2, 1: 1, 2: 0, 3: 5, 4: 4, 5: 3, 6: 6, 7: 7}  # number equivalents for flipped images
    my_images = np.load("data/x_no_augmentation_" + directory.split("/")[-1]+".npy")   # used globally
    labels = np.load("data/y_no_augmentation" + directory.split("/")[-1]+".npy")   # used globally

    a_images, a_labels = augmentation()

    #   save labels (y) and images (x)
    np.save("data/y_" + directory.split("/")[-1], np.stack((labels, a_labels)))
    np.save("data/x_" + directory.split("/")[-1], np.stack((my_images, a_images)))
