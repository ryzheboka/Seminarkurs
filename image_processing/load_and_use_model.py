""" loads a model and uses it to predict the class of the image in 'temporary_images/image.jpg'
the saved model should exist in the same directory """
import keras
import scipy.ndimage

if __name__ == "__main__":
    # Model reconstruction from JSON file
    with open('model_architecture.json', 'r') as f:
        model = keras.models.model_from_json(f.read())

    # Load weights into the new model
    model.load_weights('model_weights.h5')

    print(model.predict(scipy.ndimage.imread("temporary_images/image.jpg")))
