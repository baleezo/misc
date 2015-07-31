import numpy as np

def merge_matrix_to_1d_array(*args):
  return np.append(*(np.hstack(arg) for arg in args))
