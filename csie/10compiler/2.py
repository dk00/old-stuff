#!/usr/bin/env python
import sys
class Rule:
  def __init__(self,exp):
    self.pred = None
    self.exp = exp
    if len(self.exp) == 0:
      self.exp.append('')

class NTerm:
  def __init__(self):
    self.rules = []
    self.first = None
    self.follow = None
    
nterm = {}
nt_list = []
used = set()

def First(k):
  first = set()
  if k not in nterm:
    first.add(k)
    return first
  if nterm[k].first != None:
    return nterm[k].first
  if k in used:
    return first
  used.add(k)
  for rule in nterm[k].rules:
    f = set()
    for t in rule.exp:
      if '' in f:
        f.remove('')
      f |= First(t)      
      if '' not in f:
        break
    first |= f
  return first

def Follow(k,follow):
  if k in used:
    return
  used.add(k)
  for rule in nterm[k].rules:
    for token in reversed(rule.exp):
      if token not in nterm:
        break
      nterm[token].follow |= follow
      Follow(token,follow|nterm[k].follow)

def tcmp(a,b):
  if len(a)*len(b) > 0 and ((a[0]=='"') ^ (b[0]=='"')):
    return cmp((a[0]=='"'),(b[0]=='"'))
  return cmp(a,b)

def toStr(s,f):
  t = ''
  for item in s:
    t += ' '
    if item != '':
      t += item.strip('"')      
    else:
      if f==1:
        t += '(null)'
      else:
        t += '(eof)'
  return t

for g in sys.stdin.read().strip().split(';'):
  pr = g.split(':',2)
  if len(pr) < 2:
    continue
  k, rules = [i.strip() for i in pr]
  nt_list.append(k)
  nterm[k] = NTerm()
  nterm[k].rules = [Rule([token.strip() 
                          for token in rule.strip().split()])
                    for rule in rules.split('|')]
for k in nterm:
  used.clear()
  nterm[k].first = First(k)
  nterm[k].follow = set()
nterm[nt_list[0]].follow.add('')

for k in nterm:
  for rule in nterm[k].rules:
    follow = set([''])
    for token in reversed(rule.exp):
      if token not in nterm:
        follow = set(token)
      else:
        nterm[token].follow |= follow
        if '' in nterm[token].first:
          follow |= nterm[token].first
        else:
          follow = nterm[token].first

for k in nterm:
  used.clear()
  Follow(k,nterm[k].follow)

for k in nt_list:
  start = True
  for rule in nterm[k].rules:
    pred=set()
    for token in rule.exp:
      if '' in pred:
        pred.remove('')
      if token in nterm:
        pred |= nterm[token].first
      else:
        pred.add(token)      
      if '' not in pred:
        break
    if '' in pred:
      pred.remove('')
      pred |= nterm[k].follow
    if start:
      start = False
      print '%s\t%s\t%s\t%s\t%s' % (k,toStr(rule.exp,1),toStr(sorted(nterm[k].first,tcmp),1),toStr(sorted(nterm[k].follow,tcmp),0),toStr(sorted(pred,tcmp),0))
    else:
      print '\t%s\t\t\t%s' % (toStr(rule.exp,1),toStr(sorted(pred,tcmp),0))
