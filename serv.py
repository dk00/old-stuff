#!/usr/bin/env python
import sys
import posixpath
from BaseHTTPServer import HTTPServer, BaseHTTPRequestHandler
from urlparse import parse_qs
import dl
import ui
class MyServer(HTTPServer):
  def init(self):
    self.ui = ui.UI(self)
    self.tasks = {}
  def newTask(self, opts):
    t = dl.task()
    t.init(opts)
    self.tasks[t.opts['ori_name']] = t
    t.start()
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
    return True
    self.send_response(403, 'Unauthorized')
    self.send_header('WWW-Authenticate', self.server.auth_method);
    self.server.ui.auth(self.wfile)
    return False
  def do_GET(self):
    if not self.auth():
      return False
    self.send_response(200, 'OK')
    self.server.ui.info(self.wfile)
  def do_POST(self):
    if not self.auth():
      return False    
    print 'POST'
    length = int(self.headers['Content-Length'])
    data = parse_qs(self.rfile.read(length), True)
    if 'cmd' not in data:
      self.send_response(400, 'Bad Request')
      self.server.ui.info(self.wfile)
      return True
    if data['cmd'][0] == 'download':
      opts = {}
      opts['url'] = data['url'][0]
      if 'coop' in data:
        opts['coop'] = data['coop'][0].split('/')
      opts['local_path'] = ''
      if 'path' in data:
        opts['local_path'] = data['path'][0]
      print 'download', opts
      self.server.newTask(opts)
    #if data['command'] == 'start':
    #if data['command'] == 'stop':
    #if data['command'] == 'remove':
    #if data['command'] == 'set':
    #if data['command'] == 'request':
    #if data['command'] == 'accept':
    #if data['command'] == 'deny':
    self.send_response(200, 'OK')
    self.server.ui.info(self.wfile)
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
    todo = t[name].done(block_num, self.rfile.read())
    
if __name__ == "__main__":
  if len(sys.argv) < 2:
    exit(0)
  port = int(sys.argv[1])
  print 'start server'
  s = MyServer(('localhost', port), MyHTTPHandler)
  s.init()
  s.serve_forever()
