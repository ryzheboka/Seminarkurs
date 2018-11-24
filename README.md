# Seminarkurs
 
The goal of the the project is to build a robot that can sort and transport objects. The robot is build from Fishertechnik and connected to an Arduino and RaspberryPi.

## Prerequisites

RaspberryPi 3+:
- Python 3
- libhdf5 (needed to install h5py on Raspbian)
- h5py
- Tensorflow 1.10
- Keras 2.2.4
- fswebcam


Computer used for data processing:
- Python 3
- PIL
- h5py
- Tensorflow 1.10
- Keras 2.2.4

## Sorting objects
Sorting objects is done using image classification. The code for image classification is in image_processing.

### Running image classification on RaspberryPi

1. Collect the data by running "take_photo.sh" on the RaspberryPi and placing the camera properly.
2. Copy the data from RaspberryPi, then run "label_images.py" and give the relative path to folder with data as first argument. 
3. Label the images manually (label_images.py is still running and making labeling easier).
4. Run "augment_images.py" and give the relative path to folder with data as first argument. 
5. Experiment on "Train.ipynb" to train a good model.
6. Copy the model to RaspberryPi. Name it properly (see "load_and_use_model.py").
7. Run "load_and_use_model.py" on RaspberryPi to print predictions of the camera input.


 


