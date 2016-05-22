#!/usr/bin/env python
from sys import stdin

def load(l):
  p = []
  for c in l.split():
    p.append(int(c))
  while len(p) > 1 and p[0] == 0:
    del p[0]
  return p

def gcd(a, b):
  while a and b:
    if b: a %= b
    if a: b %= a
  return a+b

def main():
  stdin.readline()
  p = load(stdin.readline())
  q = load(stdin.readline())
  if q[0] < 0:
    p[0] = -p[0]
    q[0] = -q[0]
  p = [0]*(len(q)-len(p)) + p
  q = [0]*(len(p)-len(q)) + q
  p = p[0]
  q = q[0]
  if q:
    if p == 0: print '0/1'
    else:
      d = gcd(p, q)
      p /= d
      q /= d
      print '%d/%d' % (p, q)
  else:
    if p < 0: print '-Infinity'
    if p > 0: print 'Infinity'

if __name__ == '__main__':
  main()
