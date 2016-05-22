#!/usr/bin/env python
import sys
import socket
import select
import struct
from threading import Thread

class Server:
  def __init__(self):
    self.Server = None;
    self.threads = [];
    
  def Init(self,host,port):
    self.Server = socket.socket(socket.AF_INET,socket.SOCK_STREAM)
    self.Server.bind((host,port))
    self.Server.listen(8)

  def Run(self):
    Halt = False
    while not Halt:
      inready, outready, xready = select.select([self.Server,sys.stdin],[],[])
      for s in inready:
        if s == self.Server:        
          conn, addr = self.Server.accept()
          print "Connection from", addr
          client_thread = Client(conn)
          client_thread.start()
          self.threads.append(client_thread)
        elif s == sys.stdin:
          if sys.stdin.readline() == "q":
            halt = True
            break;
    for thread in self.threads:
      thread.join()
    self.Server.close()

class Client(Thread):
  def __init__(self,conn):
    Thread.__init__(self)
    self.conn = conn

  def run(self):    
    while True:
      data = self.conn.recv(1)
      if data:
        num = struct.unpack('b',data);
        print num[0],
        self.conn.send(data)
      else:
        break
    self.conn.close()

s = Server()
s.Init('',12222)
s.Run()
