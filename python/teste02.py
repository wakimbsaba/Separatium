import Sep

# Test 002

p = [[0.70, 0.80, 0.10, 0.30],[0.30, 0.20, 0.90, 0.70]]
D = p.copy()
H = p.copy()
Ce = p.copy()
X = [[1.0, 3.0, 6.0, 8.0],[2.0, 4.0, 7.0, 9.0]]

Sep.separatium(p, H, Ce, D, X, 2)
