import numpy as np
from utils import *
import math

np.seterr(over='ignore')

def sigmoid(z):
  #return math.tanh(z)
  return 1.0 / (1.0 + np.exp(-z))


def sigmoid_gradient(z):
  g_z = sigmoid(z)
  return g_z * (1 - g_z)


def get_col(matrix, col):
  return matrix[:, col : col + 1]

b_y = None

def cost_func(nn_param,
              input_layer_size,
              hidden_layer_size,
              num_labels,
              X,
              y,
              _lambda):

  global b_y

  theta_1_end = hidden_layer_size * (input_layer_size + 1)

  seg_1 = nn_param[0: theta_1_end]
  theta_1 = seg_1.reshape(hidden_layer_size, input_layer_size + 1)

  seg_2 = nn_param[theta_1_end:]
  theta_2 = seg_2.reshape(num_labels, hidden_layer_size + 1)

  num_samples = X.shape[0]

  a1 = np.c_[np.ones(num_samples), X]

  z2 = np.dot(theta_1, a1.transpose())

  a2 = sigmoid(z2)

  a2 = np.r_[np.ones((1, a2.shape[1])), a2]

  z3 = np.dot(theta_2, a2)

  a3 = sigmoid(z3)

  hx = np.log(a3)

  minus_hx = np.log(1 - a3)

  labels = np.array([i for i in xrange(1, num_labels + 1)])

  if b_y is None:
    b_y = np.array([y[i] == labels for i in xrange(len(y))]).astype(int)

  v_b_y = np.hstack(b_y.transpose())
  v_hx = np.hstack(hx)
  v_minus_hx = np.hstack(minus_hx)

  J = -(np.dot(v_b_y, v_hx) + np.dot((1 - v_b_y), v_minus_hx))/ num_samples
  r1 = np.square(theta_1)
  r2 = np.square(theta_2)

  #r1[:, 0] = np.zeros(r1.shape[0])
  r1[:, 0] = 0
  #r2[:, 0] = np.zeros(r2.shape[0])
  r2[:, 0] = 0

  J += _lambda * (np.sum(r1) + np.sum(r2)) / num_samples / 2; 

  return J


def grad_func(nn_param,
              input_layer_size,
              hidden_layer_size,
              num_labels,
              X,
              y,
              _lambda):

  global b_y

  theta_1_end = hidden_layer_size * (input_layer_size + 1)

  seg_1 = nn_param[0: theta_1_end]
  theta_1 = seg_1.reshape(hidden_layer_size, input_layer_size + 1)

  seg_2 = nn_param[theta_1_end:]
  theta_2 = seg_2.reshape(num_labels, hidden_layer_size + 1)

  num_samples = X.shape[0]

  a1 = np.c_[np.ones(num_samples), X]

  z2 = np.dot(theta_1, a1.transpose())

  a2 = sigmoid(z2)

  a2 = np.r_[np.ones((1, a2.shape[1])), a2]

  z3 = np.dot(theta_2, a2)

  a3 = sigmoid(z3)

  hx = np.log(a3)

  minus_hx = np.log(1 - a3)

  labels = np.array([i for i in xrange(num_labels)])

  #if b_y is None:
  b_y = np.array([y[i] == labels for i in xrange(len(y))])

  D3 = a3 - b_y.transpose()
  D2 = np.dot(theta_2.transpose(), D3) * np.r_[np.zeros((1, z2.shape[1])), sigmoid_gradient(z2)]
  D2 = D2[1:,:]

  theta_1_grad = np.dot(D2, a1)
  theta_2_grad = np.dot(D3, a2.transpose())

  reg_1 = _lambda * theta_1
  reg_2 = _lambda * theta_2

  reg_1[:, 0] = 0
  reg_2[:, 0] = 0

  theta_1_grad += reg_1
  theta_2_grad += reg_2

  grad = merge_matrix_to_1d_array(theta_1_grad, theta_2_grad) / num_samples

  return grad
