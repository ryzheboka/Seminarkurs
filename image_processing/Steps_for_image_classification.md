## How to use the scripts for simply image classification with RaspberryPi and a web-camera

1. Collect the data by running "take_photo.sh" on the RaspberryPi and placing the camera properly.
2. Copy the data from RaspberryPi, then run "label_images.py" and give the relative path to folder with data as first argument. 
3. Label the images manually (label_images.py is still running and making labeling easier).
4. Run "augment_images.py" and give the relative path to folder with data as first argument. 
5. Experiment on "Train.ipynb" to train a good model.
6. Copy the model to RaspberryPi.
7. Run "load_and_use_model.py" on RaspberryPi to print predictions of the camera input.
