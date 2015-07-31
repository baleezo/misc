import numpy as np
import scipy.io as sio
from scipy.optimize import fmin_cg, fmin_bfgs, minimize

#from cgFunc import cost_func, grad_func
from costFunc import cost_func
from randomWeight import random_init_weight
from utils import *
from predict import predict
from datetime import datetime
from computeNumGradient import *

def debug_init_weight(fan_out, fan_in):

  return np.array([np.sin(i) for i in xrange(fan_out * (1 + fan_in))]) / 10

def check_grad(_lambda):

  input_layer_size = 3
  hidden_layer_size = 5
  num_labels = 3
  num_samples = 5

  import scipy.io as sio

  cdata = sio.loadmat('check.mat')

  init_theta_1 = cdata['Theta1']
  #init_theta_1 = debug_init_weight(hidden_layer_size,
  #                                 input_layer_size)

  init_theta_2 = cdata['Theta2']
  #init_theta_2 = debug_init_weight(num_labels,
  #                                 hidden_layer_size)


  nn_param = merge_matrix_to_1d_array(init_theta_1, init_theta_2)

  X = cdata['X']
  #X = debug_init_weight(num_samples, input_layer_size - 1).reshape(num_samples, input_layer_size)


  y = cdata['y']
  #y = 1 + np.array([np.mod(i, num_labels) for i in xrange(num_samples)])

  def costF(nn_param):
    return cost_func(nn_param,
            input_layer_size,
            hidden_layer_size,
            num_labels,
            X,
            y,
            _lambda)

  #def gradF(nn_param):
  #  return grad_func(nn_param,
  #          input_layer_size,
  #          hidden_layer_size,
  #          num_labels,
  #          X,
  #          y,
  #          _lambda)
 
  cost, grad = costF(nn_param)
  #grad = gradF(nn_param)

  num_grad = compute_num_gradent(costF, nn_param)

  r = np.hstack([np.vstack(grad), np.vstack(num_grad)])

  print r
