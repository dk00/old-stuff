#!/usr/bin/env python
import re
import sys
import posixpath
from httplib import HTTPConnection
from threading import Thread, Lock, Condition
from urlparse import urlsplit
import mylib

class myWriter(Thread):
  def __init__(self):
    Thread.__init__(self)
    self.lock = Lock()
    self.sth_to_write = Lock()
    self.sth_to_write.acquire()
    self.queue = []
    self.stop = False
  def open(self, path):
    try:
      self.f = open(path, 'r+b')
    except IOError:
      try:
        self.f = open(path, 'wb')
      except IOError:
        return False
    return True
  def append(self, pos, buf):
    with self.lock:
      self.queue.append((pos, buf))
    self.sth_to_write.acquire(False)
    self.sth_to_write.release()
  def run(self):
    while len(self.queue) > 0 or not self.stop:
      if len(self.queue) == 0:
        self.sth_to_write.acquire()
        continue
      with self.lock:
        pos, buf = self.queue.pop()
      print 'write data', pos
      self.f.seek(pos)
      self.f.write(buf)   
    return self.f.close()

def urlget(url, headers, redirect = 8):
  while redirect>0:
    --redirect
    s = urlsplit(url)
    host, path = s.netloc, s.path
    if host == '':
      host, path = path.split('/', 1)
      path = '/' + path
    c = HTTPConnection(host)
    c.request("GET", path, '', headers)
    r = c.getresponse()      
    new_url = r.getheader('Location')
    if r.status/100 != 3 or new_url == None:
      break
    url = new_url
  return r, url, host, path

class dl(Thread):
  def setup(self, opts):
    def_opts = {
      'task':       None,
      'url':        None,
      'block_size': None
#     ['start':  0,]
    }
    self.r = None
    opts = mylib.CheckOpts(opts, def_opts)
    self.opts = opts
    if opts == None:
      return False
    return True

  def init(self):
    headers = {}
    self.block_num = 0
    if 'start' in self.opts:
      self.block_num = self.opts['start']
      headers['Range'] = 'bytes=%d-' % (self.opts['start'] * self.opts['block_size'])
    self.r, self.opts['url'], host, path = urlget(self.opts['url'], headers)
    if self.r.status/100 != 2:
      return None
    name = self.r.getheader('Content-Disposition')
    if name != None:
      r = re.search('(?<=attachment; filename=)"?([^"]+)')
      if r != None:
        name = r.group(1)
      else:
        name = None
    if name == None:
      name = posixpath.basename(path)
    return name, int(self.r.getheader('Content-Length'))
    
  def run(self):
    if self.r == None:
      self.init()
    while True:
      buf = self.r.read(self.opts['block_size'])
      if len(buf) < 1:
        return True
      todo = self.opts['task'].done(self.block_num, buf)
      if todo == None:
        return True
      if todo != ++self.block_num:
        print todo, self.block_num
        self.opts['start'] = todo
        self.init()

class task(Thread):
  def init(self, opts):
    def_opts = {
      'url':          None,
      'local_path':   '',
      'refer':        '',
      'block_size':   256*1024,
      'num_threads':  3,
#     ['range':        (0,),]
      'tags':         []
    }
    opts = mylib.CheckOpts(opts, def_opts)
    if opts == None:
      return False
    self.opts = opts    
    j = dl()
    dl_opts = {
      'task':       self,      
      'url':        self.opts['url'],
      'block_size': self.opts['block_size']
    }
    j.setup(dl_opts)
    def_name, self.opts['size'] = j.init()
    if opts['local_path'] == '':
      opts['local_path'] = def_name
    self.jobs = []
    self.jobs.append(j)
    self.todo = None
    self.opts['start'] = 0
    self.opts['end'] = (self.opts['size'] + self.opts['block_size'] - 1)/self.opts['block_size']
    if 'range' in self.opts:
      self.opt['start'], self.opt['end'] = self.opts['range']
    num_blocks = self.opts['end'] - self.opts['start'] + 1
    if  num_blocks > 1:
      self.todo = set([i for i in range(self.opts['start'] + 1, self.opts['end'])])
    self.wr = myWriter()
    self.wr.open(opts['local_path'])
    self.wr.start()
    j.start()
    if self.opts['size'] == None:
      return 0  #Size is unknown, can't download with multiple thread
    return self.opts['size']
    
  def run(self):
    dl_opts = {
      'task':       self,
      'url':        self.opts['url'],
      'block_size': self.opts['block_size']
    }
    num_blocks = self.opts['end'] - self.opts['start']
    part_size = (num_blocks)/self.opts['num_threads']
    part_size = max(1, part_size)
    for part in range(1, min(num_blocks, self.opts['num_threads'] - 1)):
      dl_opts['start'] = part * part_size
      j = dl()
      j.setup(dl_opts)
      self.jobs.append(j)
      j.start()
    for j in self.jobs:
      j.join()
    self.wr.stop = True
    self.wr.sth_to_write.acquire(False)
    self.wr.sth_to_write.release()
    self.wr.join()

  def done(self, block_num, buf):
    self.wr.append(block_num * self.opts['block_size'], buf)
    if self.todo == None:
      return block_num + 1
    self.todo.discard(block_num)
    if block_num + 1 in self.todo:
      self.todo.discard(block_num + 1)
      return block_num + 1
    if len(self.todo) < 1:
      return None
    return self.todo.pop()

if __name__ == "__main__":
  if len(sys.argv) < 2:
    exit(0)
  t = task()
  if t.init({'url': sys.argv[1]}):
    t.run()
