#!/usr/bin/env python
import scipy.io as sio
from scipy.optimize import fmin_cg, fmin_bfgs, minimize

#from cgFunc import cost_func, grad_func
from costFunc import cost_func
from randomWeight import random_init_weight
from utils import *
from predict import predict
from datetime import datetime
from checkGradient import check_grad


HIDDEN_LAYER_SIZE = 25
#HIDDEN_LAYER_SIZE = 25
NUM_LABELS = 10
MAX_ITER = 10


def start_train(X, y):
  input_layer_size = X.shape[1]
  hidden_layer_size = HIDDEN_LAYER_SIZE
  num_labels = NUM_LABELS
  _lambda = 1

  ############## check cost function
  jdata = sio.loadmat('ex4weights.mat')

  theta_1 = jdata['Theta1']
  theta_2 = jdata['Theta2']

  nn_param = merge_matrix_to_1d_array(theta_1, theta_2)

  J, grad = cost_func(nn_param,
  #J = cost_func(nn_param,
            input_layer_size,
            hidden_layer_size,
            NUM_LABELS,
            X,
            y,
            0)

  print 'Cost at parameters (loaded from ex4weights):', J,\
           '\n(this value should be about 0.287629)'

  #return
  ############## check cost function end

  ############## check grad
  check_grad(0)

  return
  ############## check grad end

  start_time = datetime.now()
  print 'Start training Neural Network', start_time


  init_theta_1 = random_init_weight(input_layer_size,
                                    hidden_layer_size)

  init_theta_2 = random_init_weight(hidden_layer_size,
                                    num_labels)

  nn_param = merge_matrix_to_1d_array(init_theta_1, init_theta_2)


  def cb(xk):
    print 'an iter over', datetime.now(), xk

  for idx, data in enumerate(y):
    if data == 0:
      y[idx] = 10


  opt_res = minimize(fun=cost_func,
           x0=nn_param,
           method='Newton-CG',
           #method='CG',
           options = {'maxiter': MAX_ITER, 'disp': True},
           jac =True,
           args=(input_layer_size,
                 hidden_layer_size,
                 num_labels,
                 X,
                 y,
                 _lambda),
           callback=cb)

  nn_param = opt_res.x


  '''
  nn_param = fmin_cg(cost_func,
                     fprime=grad_func,
                     x0=nn_param,
                     args=(
                           input_layer_size,
                           hidden_layer_size,
                           num_labels,
                           X,
                           y,
                           _lambda),
                     gtol=1e-12,
                     maxiter=50,
                     disp=True,
                     callback=cb)
  '''


  end_time = datetime.now()
  print 'Training overedi at', end_time
  print 'It takes %s to train the model' %(str( end_time - start_time))

  theta_1_end = hidden_layer_size * (input_layer_size + 1)
  theta_1 = nn_param[0: theta_1_end].reshape(hidden_layer_size, input_layer_size + 1)
  theta_2 = nn_param[theta_1_end:].reshape(num_labels, hidden_layer_size + 1)

  res = predict(theta_1, theta_2, X)

  '''
  res_theta = {'Theta1': theta_1, 'Theta2': theta_2}
  sio.savemat('train_res.mat', res_theta)
  '''

  n_samples = len(y)
  correct = 0
  for i in xrange(n_samples):
    if res[i] == y[i]:
      correct += 1

  print 'Training set accuracy:', float(correct) / n_samples * 100


if __name__ == '__main__':
  print 'Load data'
  #data = sio.loadmat('train.mat')
  data = sio.loadmat('ex4data1.mat')
  X = data['X']
  y = data['y']
  start_train(X, y)
