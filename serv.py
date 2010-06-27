#!/usr/bin/env python
import sys
import posixpath
from BaseHTTPServer import HTTPServer, BaseHTTPRequestHandler
from urlparse import parse_qs
import dl
import ui
class MyServer(HTTPServer):
  def init(self):
    self.UIs = {'default': ui.HTML(self), 'java': ui.Java(self)}
    self.tasks = {}
  def getUI(self,t = 'default'):
    if t not in self.UIs:
      t = 'default'
    return self.UIs[t]
  def newTask(self, opts):
    t = dl.task()
    t.init(opts)
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
    print 'POST'
    length = int(self.headers['Content-Length'])
    data = parse_qs(self.rfile.read(length), True)
    if 'cmd' not in data:
      self.send_response(400, 'Bad Request')
      self.UI.show('info')
      return True
    cmd = data['cmd'][0]
    if cmd == 'download':
      opts = {}
      opts['url'] = data['url'][0]
      if 'coop' in data:
        opts['coop'] = data['coop']
      if 'req' in data:
        opts['req'] = data['req']
      opts['local_path'] = ''
      if 'path' in data:
        opts['local_path'] = data['path'][0]
      print 'download', opts
      t = self.server.newTask(opts)
    #if data['command'] == 'start':
    #if data['command'] == 'stop':
    #if data['command'] == 'remove':
    #if data['command'] == 'set':
    #if data['command'] == 'request':
    #if data['command'] == 'accept':
    #if data['command'] == 'deny':
    self.send_response(200, 'OK')
    if t != None:
      t.download.wait()
    self.UI.show('info')
  def do_PUT(self):
    if not self.auth():
      return False
    r = re.search('(<=?block_num=)\d+', self.headers['range'])
    if r == None:
      self.send_response(416, 'Requested Range Not Satisfiable')
      return False
    self.send_response(200, 'OK')
    block_num = int(r.group(0))
    name = posixpath.basename(self.path)
    length = int(self.headers['Content-Length'])
    todo = t[name].done(block_num, self.rfile.read(length))
    
if __name__ == "__main__":
  if len(sys.argv) < 2:
    exit(0)
  port = int(sys.argv[1])
  print 'start server'
  s = MyServer(('localhost', port), MyHTTPHandler)
  s.init()
  s.serve_forever()
