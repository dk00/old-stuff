#!/usr/bin/env python

def f1():
  print 111

def f2():
  print 222

funcs = {
  'abc': f1,
  'def': f2
}

t = '0123456789'
print t[5:]

if 'abc' in funcs.keys():
  funcs['abc']()
funcs['def']()
