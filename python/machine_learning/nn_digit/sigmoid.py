import numpy as np

def sigmoid(z):
  return 1.0 / (1.0 + np.exp(-z))


def sigmoid_gradient(z):
  g_z = sigmoid(z)
  return g_z * (1 - g_z)

