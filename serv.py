#!/usr/bin/env python
import sys
import dl
import ui
from BaseHTTPServer import HTTPServer, BaseHTTPRequestHandler
from urlparse import parse_qs
class MyServer(HTTPServer):
  def init(self, ui):
    self.tasks = []
  def newTask(self, url):
    t = task(url)
    self.tasks.append(t)

class MyHTTPHandler(BaseHTTPRequestHandler):
  def auth(self):
    if self.serv.auth(self.headers['authorization']):
      return True
    self.responce(403, 'Unauthorized')
    self.send_header('WWW-Authenticate', serv.auth_method);
    self.serv.ui.auth(self.wfile)
    return False
  def do_GET(self):
    if not self.auth():
      return False
    self.responce(200, 'OK')
    self.serv.ui.info(self.wfile)
  def do_POST(self):
    if not self.auth():
      return False    
    data = parse_qs(self.rfile.read(), True)
    if 'command' in data and data['command'] == 'new':
      #TODO: self.serv.newTask(data['name'], opt, other)
      self.serv.newTask(data['name'])
    self.responce(200, 'OK')
    self.serv.ui.info(self.wfile)
    
if __name__ == "__main__":
  if len(sys.argv) < 2:
    exit(0)
  port = int(sys.argv[1])
  print 'start server'
  s = MyServer(('localhost', port), MyHTTPhandler)
  s.serve_forever()

