#!/usr/bin/env python
import re
import sys
import posixpath
from threading import Thread, Lock, Condition
import mylib

class RemoteFile():
  def __init__(self, url):
    self.url = url
    self.headers = {}
  def seek(pos):
    self.headers['Range'] = 'block_num=', pos
  def write(buf):
    r = urlconnect(url, self.headers, 'PUT', buf)
    return r.status == 200
  def close():
    r = None

class myWriter(Thread):
  def __init__(self):
    Thread.__init__(self)
    self.lock = Lock()
    self.sth_to_write = Lock()
    self.sth_to_write.acquire()
    self.queue = []
    self.stop = False
    self.f = []
  def load(self, req):
    for url in req:
      self.f.append(RemoteFile(url))
  def open(self, path):
    if path != '':
      try:
        f = open(path, 'r+b')
      except IOError:
        try:
          f = open(path, 'wb')
        except IOError:
          return False
      self.f.append(f)
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
      for f in self.f:
        f.seek(pos)
        f.write(buf)
    for f in self.f:
      f.close()
    return True

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
    self.r, self.opts['url'], host, path = mylib.urlconnect(self.opts['url'], headers)
    if self.r.status/100 != 2:
      return None, None
    name = self.r.getheader('Content-Disposition')
    if name != None:
      r = re.search('(?<=attachment; filename=)"?([^"]+)', name)
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
    while not self.opts['task'].Stop:
      buf = self.r.read(self.opts['block_size'])
      if len(buf) < 1:
        return True
      todo = self.opts['task'].done(self.block_num, buf)
      if todo == None:
        return True
      if todo != ++self.block_num:
        self.opts['start'] = todo
        self.init()

class task(Thread):
  def init(self, opts):
    self.Stop = False
    def_opts = {
      'url':          None,
      'refer':        '',
      'block_size':   256*1024,
      'num_threads':  8,
#    ['range':        (0,),]
#     'tags':         [],
      'coop':         [],
      'req':          []
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
    if not j.setup(dl_opts):
      return False
    opts['ori_name'], self.opts['size'] = j.init()
    if 'local_path' in opts:
      if opts['local_path'] == '':
        opts['local_path'] = opts['ori_name']
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
    if 'local_path' in opts:
      self.wr.open(opts['local_path'])
    self.wr.load(opts['req'])
    self.wr.start()
    j.start()
    if self.opts['size'] == None:
      return 0  #Size is unknown, can't download with multiple thread
    return self.opts['size']

  def dispatch(self):
    s = self.todo.keys()
    div_size = len(s)/(1 + len(self.opts['coop']))
    self.dispatch = set()
    j = 0
    for i in range(1, len(self.opts['coop']) - 1):
      k = 1
      while k < div_size and k < len(s) and s[j] == s[j+k] + 1:
        ++k      
      url = self.opts['coop'][i]
      headers = {}
      mylib.urlconnect(url, headers, 'POST','command=require ' + self.opts['url'] + ' ' + str(s[j]) + ' ' + str(s[j+k-1]))
      self.dispatch += set(range(s[j], s[j+k-1]))
    s = (self.todo - self.dispatch).keys()
    part_size = (len(s))/self.opts['num_threads']
    part_size = max(1, part_size)
    dl_opts = {
      'task':       self,
      'url':        self.opts['url'],
      'block_size': self.opts['block_size']
    }  
    for part in range(1, min(len(s), self.opts['num_threads'] - 1)):
      dl_opts['start'] = part * part_size
      j = dl()
      j.setup(dl_opts)
      self.jobs.append(j)  
    
  def run(self):
    for j in self.jobs[1:]:
      j.start()
    for j in self.jobs:
      j.join()
    self.stop()

  def load(self, t0):
#TODO: load task data
    self.opts = t.opts
    self.todo = t.todo
    self.dispatch = t.dispatch
    j = dl()
    dl_opts = {
      'task':       self,      
      'url':        self.opts['url'],
      'block_size': self.opts['block_size']
    }
    if not j.setup(dl_opts):
      return False
    j.init()
    self.jobs = []
    self.jobs.append(j)
    self.todo = None
    self.wr = myWriter()
    if 'local_path' in opts:
      self.wr.open(opts['local_path'])
    self.wr.load(opts['req'])
    self.wr.start()
    j.start()

  def stop(self):
    print 'Stop'
    self.Stop = True
    self.wr.stop = True
    self.wr.sth_to_write.acquire(False)
    self.wr.sth_to_write.release()    
    for i in range(1, len(self.opts['coop']) - 1):
      url = self.opts['coop'][i]
      headers = {}
      mylib.urlconnect(url, headers, 'POST','command=stop ' + self.opts['url'])
    for j in self.jobs:
      j.join()
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
