"""
augment_images.py [path to the image-directory] [count_position]:
augments images by flipping them. Then saves both, the original and the augmented images+labels in the npy format."""

import numpy as np
import sys

def augment(augment_function):
    """ returns a tuple with an array with flipped version of each image from my_images and an array of labels"""
    #   initializing arrays with augmented data
    augmented_images = np.zeros_like(my_images)

    for i, image in enumerate(my_images):   # iterate over each image and corresponding index
        augmented_images[i] = (augment_function(image))  # augment image and insert it

    return augmented_images

def noise(image):
    noise = 1.-(np.random.random(my_images[0].shape)*0.2)
    return image*noise

if __name__ == "__main__":

    my_images = np.load("data/x_no_augmentation_2.npy")   # used globally
    print(my_images.shape)
    labels = np.load("data/y_no_augmentation_2.npy")   # used globally

    flipped_images = augment(np.fliplr)
    my_images = np.concatenate((my_images, flipped_images))
    labels = np.concatenate((labels, labels))

    np.save("data/x_2", my_images)
    np.save("data/y_2", labels)

