#!/usr/bin/env python
from sys import stdin

def main():
  l = stdin.readline().split()
  r, g, b = int(l[0]), int(l[1]), int(l[2])
  if r > 0: r = 27 + (r+1)/2*3
  if g > 0: g = 28 + (g+1)/2*3
  if b > 0: b = 29 + (b+1)/2*3
  print max(r, max(g, b))

if __name__ == '__main__':
  main()

