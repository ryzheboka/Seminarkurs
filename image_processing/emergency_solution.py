import numpy as np
from PIL import Image
import os

my_file = open("second_labels","r")
labels = my_file.read()
print(np.array([int(el) for el in list(labels)]))
my_images = list()
for file in sorted(os.listdir("all_data_wensday")):
    if ".jpg" in file:
        image_array = np.asarray(Image.open("all_data_wensday/" + file))
        print(file)
        my_images.append(image_array)
np.save("data/y_no_augmentation_2", np.array(list(labels)))
np.save("data/x_no_augmentation_2", np.array(my_images))
#np.save("data/file_names", np.array(labeled_names))