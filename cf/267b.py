#!/usr/bin/env python
from sys import stdin

def main():
  m = int(stdin.readline())
  dom = {}
  count = [0]*7
  for i in range(7):
    for j in range(7):
      if i != j: dom[i, j] = []

  for i in range(m):
    j, k = stdin.readline().split()
    j, k = int(j), int(k)
    count[j] += 1
    count[k] += 1
    dom[j, k].append(i+1)
  odd = 0
  n = 0
  for i in range(7):
    if count[i]%2:
      start = i
      odd += 1
  
  if odd != 0 and odd != 2:
    print 'No'
    return
  stack = [(start,)]
  while stack:
    sign = ''
    for i in range(7):
      if (stack[-1][0], i) in dom and dom[stack[-1][0], i]:
        d = dom[stack[-1][0], i]
        sign = '+'
        break
      if (i, stack[-1][0]) in dom and dom[i, stack[-1][0]]:
        d = dom[i, stack[-1][0]]
        sign = '-'
        break
    print sign, stack
    if sign:
      stack.append((i, '%d %s' % (d.pop(), sign)))
    else:
      d = stack.pop()
      if (len(d) > 1): print d[1]

if __name__ == '__main__':
  main()



