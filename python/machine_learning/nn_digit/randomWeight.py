import numpy as np

def random_init_weight(l_in, l_out):
  epsilon_init = 0.12
  return np.random.rand(l_out, l_in + 1) * 2 * epsilon_init - epsilon_init
