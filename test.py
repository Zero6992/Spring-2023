import numpy as np

for i in range(100):
    np.random.seed(i)
    w = 2 * np.random.random((3,1)) - 1
    print(w)

