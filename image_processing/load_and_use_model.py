""" loads a model and uses it to predict the class of the image in 'temporary_images/image.jpg'
the saved model should exist in the same directory """
import keras
import scipy.ndimage

if __name__ == "__main__":
    model = keras.models.load_model("model.h5")
    print(model.predict(scipy.ndimage.imread("temporary_images/image.jpg")))
