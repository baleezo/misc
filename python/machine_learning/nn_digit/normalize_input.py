#!/usr/bin/env python
import scipy.io as sio
import numpy as np

def process_file(fname):
  print 'Load data from %s' % fname
  data = sio.loadmat(fname)
  X = data['X']
  y = data.get('y')

  #std = np.std(X, 0)
  #std[std == 0] = 1
  #X = (X - np.mean(X, 0)) / std
  for i in xrange(X.shape[0]):
    mean = np.mean(X[i])
    std = np.std(X[i])
    X[i] -= mean
    X[i] /= std

    #X[i] = (X[i] - np.mean(X[i])) / np.std(X[i])

  data = {'X': X}
  if y is not None:
    data['y'] = y

  sio.savemat('normalized_%s' % fname, data)

if __name__ == '__main__':
  process_file('train.mat')
  process_file('testdata.mat')
