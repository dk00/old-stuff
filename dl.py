#!/usr/bin/env python
import re
import sys
import posixpath
from threading import Thread, Lock, Condition
from urllib import urlencode
from urlparse import parse_qs
import mylib

class RemoteFile():
  def __init__(self, req, url):
    self.headers = parse_qs(req)    
    for i in self.headers.keys():
      self.headers[i] = self.headers[i][0]
    self.host = self.headers['host'].strip('/') + '/' + url
    del self.headers['host']
  def seek(self, pos):
    self.headers['Range'] = 'block_num=' + str(pos)
  def write(self, buf):
    self.headers['Content-Length'] = str(len(buf))
    r, url, host, path = mylib.urlconnect(self.host, self.headers, 'PUT', buf)
    return r.status == 200
  def close():
    r = None

class myWriter(Thread):
  def __init__(self, task):
    Thread.__init__(self)
    self.t = task
    self.lock = Lock()
    self.sth_to_write = mylib.Trigger()
    self.queue = []
    self.stop = False
    self.remote = []
    self.f = None
  def load(self, req):
    for url in req:
      self.remote.append(RemoteFile(url, self.t.opts['url']))
  def open(self, path):
    if path != '':
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
    self.sth_to_write.trigger()
  def run(self):
    while len(self.queue) > 0 or not self.stop:
      if len(self.queue) == 0:
        self.sth_to_write.wait()
        continue
      with self.lock:
        pos, buf = self.queue.pop()
      if self.f != None:
        self.f.seek(pos * self.t.opts['block_size'])
        self.f.write(buf)
      if pos in self.t.remote:
        continue
      for f in self.remote:
        f.seek(pos)
        f.write(buf)
    if self.f != None:
      self.f.close()
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
    if 'start' in self.opts:
      self.block_num = self.opts['start']
      headers['Range'] = 'bytes=%d-' % (self.opts['start'] * self.opts['block_size'])
    else:
      self.block_num = 0
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
      self.block_num += 1
      if todo != self.block_num:
        self.opts['start'] = todo
        self.init()
    print this.name, 'end'

class task(Thread):
  def init(self, opts):
    self.mes = None
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
    if opts['ori_name'] == None:
      return False
    self.setRange()
    if 'local_path' in opts:
      if opts['local_path'] == '':
        opts['local_path'] = opts['ori_name']
    self.jobs = []
    self.jobs.append(j)
    self.wr = myWriter(self)
    if 'local_path' in opts:      
      self.wr.open(opts['local_path']) 
    self.wr.load(opts['req'])
    if self.opts['size'] == None:
      return 0  #Size is unknown, can't download with multiple thread
    return self.opts['size']

  def setRange(self):
    self.todo = None
    self.remote = set()
    if 'start' not in self.opts:
      self.opts['start'] = 0
    self.opts['start'] = int(self.opts['start'])
    if 'size' not in self.opts:
      return
    if 'end' not in self.opts:
      self.opts['end'] = (self.opts['size'] + self.opts['block_size'] - 1)/self.opts['block_size']
    self.opts['end'] = int(self.opts['end'])
    self.todo = [i for i in range(self.opts['start'], self.opts['end'])]
    num_blocks = len(self.todo)

  def dispatch(self):
    if 'size' not in self.opts or self.todo == None:
      return
    s = self.todo
    self.todo = set(self.todo)
    div_size = len(s)/(1 + len(self.opts['coop']))
    self.remote = set()
    j = 0
    self.todo1 = self.todo
    self.todo1.discard(0)
    for i in range(0, len(self.opts['coop'])):
      k = 0
      while k < div_size and k < len(s) and s[j+k] + 1 == s[j+k+1]:
        k += 1
      cmd = parse_qs(self.opts['coop'][i])
      for i in cmd.keys():
        cmd[i] = cmd[i][0]
      headers = {}
      cmd['url'] = self.opts['url']
      cmd['start'] = str(s[j])
      cmd['end'] = str(s[j]+k)
      j += k
      cmd['hdi_ag'] = '1'
      url = cmd['host']
      del cmd['host']
      if mylib.urlconnect(url, headers, 'POST', urlencode(cmd)):
        self.remote |= set(range(int(cmd['start']), int(cmd['end'])))
        self.todo1 -= set(range(int(cmd['start']), int(cmd['end'])))
#      self.opts['coop'][i] = parse_qs(self.opts['coop'][i])
    s = [b for b in (self.todo - self.remote)]
    part_size = (len(s))/self.opts['num_threads']
    part_size = max(1, part_size) 
    for part in range(1, min(len(s), self.opts['num_threads'])):
      dl_opts = {
        'task':       self,
        'url':        self.opts['url'],
        'block_size': self.opts['block_size']
      } 
      dl_opts['start'] = part * part_size
      if part <= len(s) % part_size:
        dl_opts['start'] += 1
      dl_opts['start'] = s[dl_opts['start']]
      self.todo1.discard(dl_opts['start'])
      j = dl()
      j.setup(dl_opts)
      self.jobs.append(j)
    self.todo = set(s)
    
  def run(self):
    self.dispatch()
    self.wr.start()
    self.jobs[0].start()
    for j in self.jobs[1:]:
      j.init()
      j.start()
    for j in self.jobs:
      j.join()
    self.stop()

  def load(self, t0):
#TODO: load task data
    self.Stop = False
    self.opts = t.opts
    self.todo = t.todo
    self.todo1 = t.todo1
    self.remote = t.remote
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

  def stop(self):
    self.Stop = True        
#    for i in range(1, len(self.opts['coop']) - 1):
#     cmd = parse_qs(self.opts['coop'][i])
#     headers = {}
#     cmd['cmd'] = 'stop'
#     url = cmd['host']
#     del cmd['host']
#     mylib.urlconnect(url, headers, 'POST', urlencode(cmd))
    for j in self.jobs:
      j.join()
    self.wr.sth_to_write.trigger()
    self.wr.join()
    if self.mes != None:
      self.mes.trigger('complete')
  def done(self, block_num, buf):
    self.wr.append(block_num, buf)
    if self.mes != None:
      self.mes.trigger('got' + str(len(buf)))
    if block_num in self.remote and block_num not in self.todo:
      self.remote.discard(block_num)
      if len(self.remote) + len(self.todo) == 0:
        self.wr.stop = True
      return None
    if len(self.todo) == 0 and len(self.remote) > 0:
      self.todo |= self.remote
    if self.todo == None:
      if self.wr.stop == True or len(buf) < self.opts['block_size']:
        self.wr.stop = True
        return None
      return block_num + 1
    self.todo.discard(block_num)
    if len(self.remote) + len(self.todo) == 0:
      self.wr.stop = True
      return None
    if len(self.todo) == 0:
      return None
    if len(self.todo) > 0 and len(self.todo1) == 0:
      self.todo1 = self.todo
    if block_num + 1 in self.todo1:
      self.todo1.discard(block_num + 1)
      return block_num + 1
    return self.todo1.pop()

if __name__ == "__main__":
  if len(sys.argv) < 2:
    exit(0)
  t = task()
  req = {
    'url':  'linux4.csie.ntu.edu.tw:6666'
  }
  req = urlencode(req)
  coop = {
    'host': 'linux7.csie.ntu.edu.tw:6666',
    'cmd':  'download',
    'req':  req
  }
  opts = {
    'url': sys.argv[1], 
    'local_path': ''
  }
  if t.init(opts):
    t.run()

