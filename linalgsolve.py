import numpy as np

a = np.array([[-3, -1, 0], [9, 2, -3], [-6, -2, 0]])
b = np.array([-91, 203, -182])

x = np.linalg.solve(a, b)

print(x)
