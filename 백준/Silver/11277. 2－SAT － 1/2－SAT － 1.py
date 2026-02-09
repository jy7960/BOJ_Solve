from itertools import product
n, m = map(int, input().split())
x = [list(map(int, input().split())) for _ in range(m)]
for p in product([0,1], repeat=n):
    p = [0] + list(p)
    is_ok = True
    for i, j in x:
        xi, xj = p[abs(i)], p[abs(j)]
        if i < 0:
            xi = not xi
        if j < 0:
            xj = not xj
        if not (xi or xj):
            is_ok = False
            break
    if is_ok:
        print(1)
        break
else:
    print(0)