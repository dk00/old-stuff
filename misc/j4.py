#!/usr/bin/env python
import time
import signal
import subprocess

while (True):
  tmp = time.time()
  ret = subprocess.call(['/home/student/96/b96120/j0x.py'])
  tmp = time.time() - tmp
  if ret == 0:
    break
  if ret == 1:
    time.sleep(30)
  elif ret == 254:
    time.sleep(2)

