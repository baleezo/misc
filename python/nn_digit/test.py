#!/usr/bin/env python
import scipy.io as sio 
from predict import *
import numpy as np


def test():

  data = sio.loadmat('pro_train.mat')
  X = data['X']
  y = data['y']

  for idx, data in enumerate(y):
    if data == 0:
      y[idx] = 10

  #theta = sio.loadmat('train_res.mat')
  theta = sio.loadmat('train_res2.mat')

  theta_1 = theta['Theta1']
  theta_2 = theta['Theta2']

  print 'start to calc'

  res = predict(theta_1, theta_2, X)

  print 'calc overed'

  print 'start to check'

  n_samples = len(y)
  corr = 0
  for i , data in enumerate(y):
    if res[i] == data:
      corr += 1


  #for idx, data in enumerate(res):
  #  if data == 10:
  #    res[idx] = 0

  #img_id = [i for i in xrange(1, len(res) + 1)]

  #data = np.column_stack((np.array(img_id), np.array(res)))

  #import time

  #with open('res%d.csv' %(int(time.clock() * 10000)), 'w') as f:
  #  f.write('ImageId,Label\n')
  #  np.savetxt(f, data, fmt='%i', delimiter=',')

  print 'Training set accuracy:', float(corr) / n_samples * 100

if __name__ == '__main__':
  test()
