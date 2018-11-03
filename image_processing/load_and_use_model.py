""" loads a model and uses it to predict the class of the image in 'temporary_images/image.jpg'
the saved model should exist in the same directory """
from time import sleep
import keras.models
import scipy.ndimage
import h5py
import numpy as np

if __name__ == "__main__":
    labels_dict = {0: "vl", 1: "vm", 2: "vr", 3: "cl", 4: "cm", 5: "cr", 6: "nl", 7: "nm"}
    # Model reconstruction from JSON file
    with open('model_architecture.json', 'r') as f:
        model = keras.models.model_from_json(f.read())

    # Load weights into the new model
    model.load_weights('model_weights.h5')
    for i in range(10):     # needs a proper exit condition
        sleep(1)
        label = np.argmax(model.predict(scipy.ndimage.imread("temporary_images/image.jpg").reshape((1,288,352,3)), 1))
        print(labels_dict[int(label)])
