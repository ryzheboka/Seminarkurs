""" loads a model and uses it to predict the class of the image in 'temporary_images/image.jpg'
the saved model should exist in the same directory """
import subprocess
import keras.models
import h5py
import numpy as np
import os
import scipy.ndimage
import time


def standard(image):
    return (image - [0.485, 0.456, 0.406]) / [0.229, 0.224, 0.225]

if __name__ == "__main__":

    create_dir = ["mkdir", "temporary_images"]
    subprocess.run(create_dir)

    labels_dict = {0: "lila Lippenstift", 1: "rosa Lippenstift", 2: "Tierchen", 3: "Nichts", 4: "Fehler"}

    print(" Model reconstruction from JSON file")
    with open('model_architecture.json', 'r') as f:
        model = keras.models.model_from_json(f.read())

    print("Load weights into the new model")
    model.load_weights('model_weights.h5')
    print("Model is loaded")

    take_foto = ['fswebcam', '--no-banner', 'temporary_images/image.jpg']
    delete_foto = ['rm', "temporary_images/image.jpg"]

    for i in range(10):
        print("start sleeping")
        time.sleep(20)
        print("end sleeping")
        subprocess.run(take_foto)
        image = scipy.ndimage.imread("temporary_images/image.jpg")
        print("Start predicting")
        label = np.argmax(model.predict(standard(np.expand_dims(image, axis=0)), 1))
        subprocess.run(delete_foto)
        print(labels_dict[int(label)])

    subprocess.run(["rm", "-r", "temporary_images"])
