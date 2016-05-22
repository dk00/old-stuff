#!/usr/bin/env python
from sys import stdin

def main():
  l = stdin.readline().split()
  n, m = int(l[0]), int(l[1])
  adj = [[] for i in range(n)]
  for k in range(m):
    l = stdin.readline().split()
    i, j = int(l[0])-1, int(l[1])-1
    adj[i].append(j)
    adj[j].append(i)
  q = []
  count = []
  for i in range(n):
    count.append(len(adj[i]))
    if count[-1] == 1:
      q.append(i)
  m = 0
  q1 = []
  while len(q) > 0:
    i = q[0]
    count[i] = 0
    del q[0]
    for j in adj[i]:
      count[j] -= 1

    if len(q) < 1:
      m += 1
      for i in range(n):
        if count[i] == 1:
          q.append(i)
  print m

if __name__ == '__main__':
  main()
