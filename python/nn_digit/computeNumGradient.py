import numpy as np

def compute_num_gradent(J, theta):

  numgrad = np.zeros(len(theta))
  perturb = np.zeros(len(theta))
  e = 1e-4
  for p in xrange(len(theta)):
    perturb[p] = e
    loss1, d = J(theta - perturb)
    loss2, d = J(theta + perturb)

    #loss1 = J(theta - perturb)
    #loss2 = J(theta + perturb)

    numgrad[p] = (loss2 - loss1) / (2 * e)
    perturb[p] = 0

  return numgrad
