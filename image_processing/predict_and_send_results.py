import subprocess
import keras.models
import h5py
import numpy as np
import os
import scipy.ndimage
import serial
import time



def predict():
    subprocess.run(take_foto)
    image = scipy.ndimage.imread("temporary_images/image.jpg")
    print("Start predicting")
    label = np.argmax(model.predict(np.expand_dims(image, axis=0), 1))
    subprocess.run(delete_foto)
    print(labels_dict[int(label)])
    return(int(label))

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

    print("Make contact to arduino")
    ser = serial.Serial('/dev/ttyACM0', 9600)
    time.sleep(3)
    message = ser.readline()
    if message:
        print(message)
    while message != "end":
        message = ser.readline()
        if message == "predict":
            result = predict()
            ser.write(result);

    subprocess.run(["rm", "-r", "temporary_images"])
