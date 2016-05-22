#!/usr/bin/env python
from sys import stdin

def arg(n, cap):
  d = [n]*n
  d[0] = 0
  p = [i for i in range(n)]
  q = [0]
  while len(q) > 0:
    i = q[0]
    del q[0]
    for j in range(n):
      if cap[i][j] > 0 and d[i] + 1 < d[j]:
        d[j] = d[i] + 1
        p[j] = i
        q.append(j)
  if d[n-1] >= n: return 0
  i = n-1
  lim = cap[p[i]][i]
  while i != 0:
    lim = min(lim, cap[p[i]][i])
    i = p[i]
  i = n-1
  while i != 0:
    cap[p[i]][i] -= lim
    i = p[i]
  return lim

def traffic(n, cap):
  total = 0
  while True:
    tmp = arg(n, cap)
    if tmp < 1: break
    total += tmp
  return total

def main():
  n = int(stdin.readline().strip())
  m = int(stdin.readline().strip())
  cap = [[0]*n]*n
  road = []
  for i in range(m):
    x, y, c = stdin.readline().strip().split()
    x, y, c = int(x)-1, int(y)-1, int(c)
    road.append((x, y, c))
    cap[x][y] = c
    cap[y][x] = c
  print '%.5f' % traffic(n, cap)
  for x, y, c in road:
    print '%.5f' % (c - cap[x][y])

if __name__ == '__main__':
  main()
