#!/usr/bin/env python
from sys import stdin

def main():
  s = stdin.readline().strip()
  t = stdin.readline().strip()
  j = 0
  k = 0
  a = 0
  for i in range(len(s)):
    while k + 1 < len(t) and s[i] != t[k]:
      k += 1
    a += k - j + 1
    if s[i] == t[j]:
      j += 1
      if j >= len(t): break
      if j > k: k = j
  print a

if __name__ == '__main__':
  main()

