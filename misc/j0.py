#!/usr/bin/env python
import sys
import ftplib
import os.path

file_list = []
out_file = ''

def WriteFile(buf):
  out_file.write(buf)

def AddDir(l):
  file_list.append(l)

def List(args):
  del file_list[0:]
  f.retrlines('LIST', AddDir)
  if len(args) > 0 and int(args[0]):
    return 1
  for i in range(len(file_list)):
    print i, file_list[i]

def Cwd(args):
  i = args[0]
  f.cwd(file_list[int(i)][55:])

def Get(args):
  i = int(args[0])
  o = args[1]
  flag = 'wb+'
  offset = 0
  global out_file
  if os.path.exists(o):
    flag = 'rb+'
    offset = os.path.getsize(o) - 1
  if (offset < 0):
    offset = 0  
  out_file = open(o, flag)
  if len(args) > 2:
    offset = int(args[2])
  if (offset > 0):
    out_file.seek(int(offset))
  cmd = 'RETR ' + file_list[i][55:]
  f.retrbinary(cmd, WriteFile, 1048576, offset)
  out_file.close()

def Go(args):
  for i in args:
    List(['1'])
    Cwd([int(i)])

funcs = {
  'go': Go,
  'ls': List,
  'cd': Cwd,
  'get': Get,
  'q': exit
}

f = ftplib.FTP('115.57.228.2')
f.login()
while (True):
  cmd = sys.stdin.readline().strip().split()
  if cmd[0] in funcs.keys():
    funcs[cmd[0]](cmd[1:])
f.close()

# 7 2 4
