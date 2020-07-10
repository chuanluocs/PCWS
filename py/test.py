import numpy as np
from pcws import pcws

k, p, e = pcws(10, 1, [[100, 200, 0], [0, 0, 300], [100, 0, 400], [200, 0, 0]])
print(k, p, e)

k, p, e = pcws(10, 1, np.random.rand(1000, 10000))
print(k, p, e)

