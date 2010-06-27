import re
from threading import Lock
from httplib import HTTPConnection
class Trigger():
  def __init__(self):
    self.lock = Lock()
    self.lock.acquire()
  def wait(self):
    self.lock.acquire()
  def trigger(self):
    self.lock.acquire(False)
    self.lock.release()

def CheckOpts(opts, def_opts):
  for att in def_opts.keys():
    opts.setdefault(att, def_opts[att])
    if opts[att] == None:
      return None
  return opts
#def LoadOpts():

#def SaveOpts(opts):

def urlconnect(url, headers, method = 'GET', content = '', redirect = 8):
  while redirect>0:
    --redirect
    s = re.search('([^:]://)?(?P<host>[^/:]+(:\d+)?)(?P<path>/.*)',url)
    host, path = s.group('host'), s.group('path')
    if host == None or path == None:
      return False
    c = HTTPConnection(host)
    c.request(method, path, content, headers)
    r = c.getresponse()
#TODO: retry
    new_url = r.getheader('Location')
    if r.status/100 != 3 or new_url == None:
      break
    url = new_url
  return r, url, host, path
