#!/usr/bin/env python
from sys import stdin
N = 42
C = [[1, 1]]
def init():
  for i in range(N):
    C.append([1])
    for j in range(i+1):
      C[-1].append(C[-2][j] + C[-2][j+1])
    C[-1].append(1)

def go(n):
  count = [0]*(N+2)
  i = 0
  j = 2
  while n >= j:
    n -= j
    for k in range(len(C[i])):
      count[k] += C[i][k]
    j *= 2
    i += 1
  l = 0
  while i >= 0 and n > 1:
    if n >= j:
      n -= j
      for k in range(len(C[i])):
        count[k+l] += C[i][k]
      l += 1
    j /= 2
    i -= 1
  count[l] += n
  return count

def lg(n):
  k = 0
  while n%2 == 0:
    k += 1
    n /= 2
  if n > 1: return -1
  return k

def main():
  init()
  while True:
    l = stdin.readline().split()
    if len(l) < 2: break
    n, k = int(l[0]), int(l[1])
    k = lg(k)
    if k < 0:
      print 0
      continue
    count = go(n)
    print count[k]

if __name__ == '__main__':
  main()

