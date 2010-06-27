#!/usr/bin/env python
from urlparse import urlsplit
from urllib import urlencode
from urlparse import parse_qs
import mylib
import sys
import re
import dl

if __name__ == "__main__":
  if len(sys.argv) < 2:
    exit(0)
  t = dl.task()
  req = [
    {'host':  'linux7.csie.ntu.edu.tw:6666'}
  ]
  for i in range(0,len(req)):
    req[i] = urlencode(req[i], True)
  coop = [
    { 'host': 'linux9.csie.ntu.edu.tw:6666',
      'cmd':  'download',
      'req':  req
    },
    { 'host': 'linux4.csie.ntu.edu.tw:6666',
      'cmd':  'download',
      'req':  req
    },
    { 'host': 'linux5.csie.ntu.edu.tw:6666',
      'cmd':  'download',
      'req':  req
    }
  ]
  for i in range(0,len(coop)):
    coop[i] = urlencode(coop[i], True)
  cmd = {
    'cmd': 'download',
    'url': sys.argv[1],
    'path': '',
    'coop': coop
  }
  data = urlencode(cmd, True)
  r, url, host, path = mylib.urlconnect('linux7.csie.ntu.edu.tw:6666',{},'POST',data)
  print r.read()

