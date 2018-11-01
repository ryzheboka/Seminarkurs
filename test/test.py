"""The tests are specific to the data that isn't in the repository. Modify values for use with other data """

import unittest
import numpy as np


class TestImageProcessing(unittest.TestCase):

    def test_label_images(self):
        labels = np.load("../image_processing/data/labels_training_images.npy")
        self.assertEqual(labels[0], 2)
        self.assertEqual(labels[1], 0)


if __name__ == '__main__':
    unittest.main()
