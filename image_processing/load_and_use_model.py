""" loads a model and uses it to predict the class of the image in 'temporary_images/image.jpg'
the saved model should exist in the same directory """
import subprocess
import keras.models
import h5py
import numpy as np
import os
import scipy.ndimage

if __name__ == "__main__":

    create_dir = ["mkdir", "temporary_images"]
    subprocess.run(create_dir)

    labels_dict = {0: "vl", 1: "vm", 2: "vr", 3: "cl", 4: "cm", 5: "cr", 6: "nl", 7: "nm"}

    print(" Model reconstruction from JSON file")
    with open('model_architecture.json', 'r') as f:
        model = keras.models.model_from_json(f.read())

    print("Load weights into the new model")
    model.load_weights('model_weights.h5')
    print("Model is loaded")

    take_foto = ['fswebcam', '--no-banner', 'temporary_images/image.jpg']
    delete_foto = ['rm', "temporary_images/image.jpg"]

    for i in range(10):
        subprocess.run(take_foto)
        image = scipy.ndimage.imread("temporary_images/image.jpg")
        print("Start predicting")
        label = np.argmax(model.predict(np.expand_dims(image,axis=0), 1))
        subprocess.run(delete_foto)
        print(labels_dict[int(label)])

    subprocess.run(["rm", "-r", "temporary_images"])
