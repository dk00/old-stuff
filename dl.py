#!/usr/bin/env python
import re
import sys
import select
import struct
from httplib import *
from threading import Thread, Lock
class dl(Thread):
  def __init__(self):
    Thread.__init__(self)
  def init(self, D, host, path, name):
    self.D = D;
    self.host = host
    self.path = path
    self.name = name
  def run(self):
    while True:
      r = self.D.get()
      if r == None:
        break
      (start, end) = r
      c = HTTPConnection(self.host)
      r = 'bytes=%d-%d' % (start, end)
      c.request("GET", self.path, '', {'Range': r})
      r = c.getresponse()
      #TODO: error handling
      if self.name != None:
        xwrite(self.name, start, r.read())
  def getsize(self):
    c = HTTPConnection(self.host)
    c.request("HEAD", self.path, '')
    r = c.getresponse()
    return int(r.getheader('Content-Length'))      

class task(Thread):
  def init(self, url, num_thread):
    self.num_thread = num_thread
    o = re.search('([^/]+)(/.*)?',sys.argv[1])
    if o == None:
      return 'invalid URL'
    self.host, self.path = o.groups()
    print self.host, self.path
    o = re.search('.*/([^/]*)', self.path)
    self.name = o.group(1)
    j = dl()
    j.init(None, self.host, self.path, None)
    self.length = j.getsize()
    self.block_len = 256*1024
    self.block = 0
    self.todo = set(range(0, (self.length + self.block_len - 1)/self.block_len))
    self.done = set()
  def get(self):
    try:
      todo = self.todo.pop()
    except KeyError:
      return None
    return (todo * self.block_len, (todo + 1)* self.block_len - 1)
  def put(self, block):
    ++self.num_block
    self.todo.add(block)
  def progress(self):
    return (self.num_block * self.blocklen, self.length)
  def run(self):
    self.jobs = []
    for i in range(1, self.num_thread):
      j = dl()
      j.init(self, self.host, self.path, self.name)
      self.jobs.append(j)
      j.start()
    for j in self.jobs:
      j.join()

def xwrite(name, start, buf):
  try:
    f = open(name, 'rb+')
  except IOError:
    f = open(name, 'wb+')
  f.seek(start)
  f.write(buf)
  f.close()

if __name__ == "__main__":
  t = task()
  t.init(sys.argv[1], 16)
  t.run()
