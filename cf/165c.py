#!/usr/bin/env python
from sys import stdin

def go(s, i):
  m = 0
  while i+m < len(s) and s[i+m] == 0:
    m += 1
  return m

def main():
  k = int(stdin.readline())
  s = stdin.readline().strip()
  s = [ord(s[i])-ord('0') for i in range(len(s))]

  i = go(s, 0)
  zl = i
  j = i-1
  while j < len(s) and k > 0:
    j += 1+go(s, j+1)
    k -= 1
  zr = go(s, j+1)
  c0 = 0
  count = 0
  while j < len(s):
    if j <= i: count += zl*(zl+1)/2
    else: count += (1+zl)*(1+zr)
    zl = go(s, i+1)
    zr = go(s, j+1)
    i += 1+zl
    j += 1+zr
  print count

if __name__ == '__main__':
  main()

