#!/usr/bin/env python
import re
import sys
import posixpath
from SocketServer import ThreadingMixIn
from BaseHTTPServer import HTTPServer, BaseHTTPRequestHandler
from urlparse import parse_qs
import dl
import ui
import mylib
class MyServer(ThreadingMixIn, HTTPServer):
  def init(self):
    self.UIs = {'default': ui.HTML(self), 'java': ui.Java(self)}
    self.tasks = {}
  def getUI(self,t = 'default'):
    if t not in self.UIs:
      t = 'default'
    return self.UIs[t]
  def newTask(self, opts):
    t = dl.task()
    r = t.init(opts)
    if r == None or r == False:
      return None
    self.tasks[t.opts['url']] = t
    t.start()
    return t
  def restartTask(self, name):
    if name not in self.tasks:
      return False
    t = task()
    t.load(self.tasks[name])
    self.tasks[name] = t
    t.start()
  def rmTask(self, name): 
    self.tasks.discard(name)

class MyHTTPHandler(BaseHTTPRequestHandler):
  def auth(self):
#    if self.serv.auth(self.headers['authorization']):
    if 'ui' in self.headers:
      self.UI = self.server.getUI(self.headers['ui'])
    else:
      self.UI = self.server.getUI()
    self.UI.setup(self)
    auth = {
      'download':   True,
      'info':       True
    }
    return auth
  def unauth(self):
    self.send_response(403, 'Unauthorized')
    self.send_header('WWW-Authenticate', 'basic');
    self.UI.show('auth')
  def wait_confirm(self):
    self.send_response(200, 'OK')
    self.UI.show('wait_confirm')
  def do_GET(self):
    auth = self.auth()
    if 'info' not in auth:
      self.unauth()
      return True
    self.send_response(200, 'OK')
    self.UI.show('wait_confirm')
  def do_POST(self):
    auth = self.auth()
    length = int(self.headers['Content-Length'])
    data = parse_qs(self.rfile.read(length), True)
    if 'cmd' not in data:
      self.send_response(400, 'Bad Request')
      self.UI.show('info')
      return True
    cmd = data['cmd'][0]
    error = None
    if cmd == 'download':
      copy = {
        'url':    'url',
        'coop':   'coop',
        'req':    'req',
        'path':   'local_path',
        'start':  'start',
        'end':    'end'
      }
      opts = {}
      for i in copy.keys():
        if i in data:
          opts[copy[i]] = data[i][0]
      if 'coop' in data:
        opts['coop'] = []
        for coop in data['coop']:
            if 'host' in coop:
                opts['coop'].append(coop)
      if 'req' in data:
        opts['req'] = data['req']
      print cmd, opts['url']
      if 'start' in opts and 'end' in opts:
        print opts['start'], opts['end']
      if 'local_path' in opts:
        print opts['local_path']
      t = self.server.newTask(opts)
      if t == None or t == False:
        error = "Can't download file"
    #if data['command'] == 'start':
    #if data['command'] == 'stop':
    #if data['command'] == 'remove':
    #if data['command'] == 'set':
    #if data['command'] == 'request':
    #if data['command'] == 'accept':
    #if data['command'] == 'deny':
    self.send_response(200, 'OK')
    if error != None:
      self.end_headers()
      self.wfile.write(error + '\n')
      return False

    if 'hdi_ag' not in data and t != None:
      self.end_headers()
      self.wfile.write('file size: ')
      print 'file size: '
      if 'size' in t.opts:
        print str(t.opts['size'])
        self.wfile.write(str(t.opts['size'])+'\n')
      else:
        self.wfile.write('0'+'\n')
      self.wfile.flush()
      t.mes = mylib.Trigger()
      while True:
        t.mes.wait()
        if t.mes.mes != None:
          self.wfile.write(t.mes.mes+'\n')
          self.wfile.flush()
          if t.mes.mes == 'complete':
            break
    else:
      self.UI.show('info')
  def do_PUT(self):
    if not self.auth():
      return False
    name = str(self.path[1:])
    if 'Range' not in self.headers or name not in self.server.tasks:
      self.send_response(416, 'Requested Range Not Satisfiable')
      return False
    r = re.search('\d+', self.headers['Range'])
    if r == None:
      self.send_response(416, 'Requested Range Not Satisfiable')
      return False
    self.send_response(200, 'OK')
    block_num = int(r.group(0))    
    length = int(self.headers['Content-Length'])
    todo = self.server.tasks[name].done(block_num, self.rfile.read(length))
    
if __name__ == "__main__":
  if len(sys.argv) < 2:
    exit(0)
  port = int(sys.argv[1])
  print 'start server'
  s = MyServer(('0.0.0.0', port), MyHTTPHandler)
  s.init()
  s.serve_forever()
