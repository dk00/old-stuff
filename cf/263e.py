#!/usr/bin/env python
from sys import stdin

def main():
  n, m, k = stdin.readline().split()
  n, m, k = int(n), int(m), int(k)
  a = []
  for i in range(n):
    a[i] = []
    l = stdin.readline().split()
    for j in l:
      a[i].append(int(j))
  s0 = [[0]*m]*n
  s1 = [[0]*m]*n
  s2 = [[0]*m]*n
  for i in range(1,n):

  


if __name__ == '__main__':
  main()
