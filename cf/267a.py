#!/usr/bin/env python
from sys import stdin

def main():
  n = int(stdin.readline())
  for i in range(n):
    a, b = stdin.readline().split()
    a, b = int(a), int(b)
    m = 0
    while a and b:
      m += a/b
      a %= b
      if a:
        m += b/a
        b %= a
    print m

if __name__ == '__main__':
  main()
