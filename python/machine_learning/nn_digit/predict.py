import numpy as np
from sigmoid import *

def predict(theta_1, theta_2, X):

  max_p = 0

  h1 = sigmoid(np.c_[np.ones((X.shape[0], 1)), X].dot(theta_1.transpose()))
  h2 = sigmoid(np.c_[np.ones((h1.shape[0], 1)), h1].dot(theta_2.transpose()))

  res = []

  for i in xrange(X.shape[0]):
    res.append(np.argmax(h2[i]) + 1)

  return res
