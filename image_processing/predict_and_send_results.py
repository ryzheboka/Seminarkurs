import subprocess
import keras.models
import h5py
import numpy as np
import os
import scipy.ndimage
import serial
import time

def standard(image):
    return (image - [0.485, 0.456, 0.406]) / [0.229, 0.224, 0.225]

def predict():
    subprocess.run(take_foto)
    image = scipy.ndimage.imread("temporary_images/image.jpg")
    print("Start predicting")
    label = np.argmax(model.predict(standard(np.expand_dims(image, axis=0)), 1))
    subprocess.run(delete_foto)
    print(labels_dict[int(label)])
    return(int(label))

if __name__ == "__main__":

    create_dir = ["mkdir", "temporary_images"]
    subprocess.run(create_dir)

    labels_dict = {0: "Knaeul", 1: "Kugel", 2: "Wuerfel gruen", 3: "Wuerfel blau"}

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
            ser.write(result)
        else:
            print("Message from arduino: %s",message)

    subprocess.run(["rm", "-r", "temporary_images"])
