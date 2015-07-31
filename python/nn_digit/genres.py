#!/usr/bin/env python
import scipy.io as sio 
from predict import *
import numpy as np


def genres():

  data = sio.loadmat('normalized_testdata.mat')
  X = data['X']

  theta = sio.loadmat('train_res_normal_2000.mat')

  theta_1 = theta['Theta1']
  theta_2 = theta['Theta2']

  print 'start to predict'

  res = predict(theta_1, theta_2, X)

  print 'predict overed'

  for idx, data in enumerate(res):
    if data == 10:
      res[idx] = 0

  img_id = [i for i in xrange(1, len(res) + 1)]

  data = np.column_stack((np.array(img_id), np.array(res)))

  import time

  res_file = 'res%d.csv' %(int(time.clock() * 1000))

  with open(res_file, 'w') as f:
    f.write('ImageId,Label\n')
    np.savetxt(f, data, fmt='%i', delimiter=',')

  print 'generate res file[%s]' % res_file

if __name__ == '__main__':
  genres()
