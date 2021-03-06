#!/usr/bin/env python
from sys import stdin

def main():
  count = [0]*256
  for c in stdin.readline():
    count[ord(c)] += 1
  res = 'YES'
  for c in stdin.readline():
    count[ord(c)] -= 1
    if c.strip() and count[ord(c)] < 0:
      res = 'NO'
  print res

if __name__ == '__main__':
  main()

