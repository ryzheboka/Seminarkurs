"""
augment_images.py [path to the image-directory] [count_position]:
augments images by flipping them. Then saves both, the original and the augmented images+labels in the npy format."""

import numpy as np
import sys

def augment(augment_function,augment_dict):
    """ returns a tuple with an array with flipped version of each image from my_images and an array of labels"""
    #   initializing arrays with augmented data
    augmented_images = np.zeros_like(my_images)
    augmented_labels = np.zeros_like(labels)

    for i, image in enumerate(my_images):   # iterate over each image and corresponding index
        augmented_images[i] = (augment_function(image))  # augment image and insert it
        augmented_labels[i] = (augment_dict[labels[i]])   # read the corresponding label and insert it

    return augmented_images, augmented_labels

def noise(image):
    noise = 1.-(np.random.random(my_images[0].shape)*0.2)
    return image*noise

if __name__ == "__main__":

    directory = sys.argv[1]  # reads the path where to read the data from (first command line argument)
    if sys.argv[2]:
        reflection_dict = {0: 2, 1: 1, 2: 0, 3: 5, 4: 4, 5: 3, 6: 6, 7: 7}  # number equivalents for flipped images
    else:
        reflection_dict = {i:i for i in range(8)}
    my_images = np.load("data/x_no_augmentation_" + directory.split("/")[-1]+".npy")   # used globally
    print(my_images.shape)
    labels = np.load("data/y_no_augmentation_" + directory.split("/")[-1]+".npy")   # used globally

    flipped_images, flipped_labels = augment(np.fliplr,reflection_dict)
    labels = np.concatenate((labels, flipped_labels))
    my_images = np.concatenate((my_images, flipped_images))
    noisy_images, noisy_labels = augment(noise,{i:i for i in range(8)})
    #   save labels (y) and images (x)
    np.save("data/y_" + directory.split("/")[-1], np.concatenate((labels, noisy_labels),0))
    np.save("data/x_" + directory.split("/")[-1], np.concatenate((my_images, noisy_images),0))
