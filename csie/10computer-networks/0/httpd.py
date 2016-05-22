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
    halt = False
    while not halt:
      inready, outready, xready = select.select([self.Server,sys.stdin],[],[])
      for s in inready:
        if s == self.Server:        
          conn, addr = self.Server.accept()
          print "Connection from", addr
          client_thread = Client(conn)
          client_thread.start()
          self.threads.append(client_thread)
        elif s == sys.stdin:
          tmp = sys.stdin.readline()
          if tmp == "q\n":
            halt = True
            break;
    for thread in self.threads:
      thread.join()
    self.Server.close()

def parse_ver(ver_string):
  protocol, ver, junk = (ver_string + "//").split('/',2)
  main_ver, sub_ver, junk = (ver + '..').split('.',2)
  if protocol == "HTTP" and int("0" + main_ver)*10 + int("0" + sub_ver) >= 11:
    return "HTTP/1.1+"
  return "Other"

def Responce400(client):
  client.writelines("HTTP/1.1 400 Bad Request\r\n")
  client.writelines("Content-Type: text/html; charset=utf-8\r\n");
  client.writelines("\r\n")
  client.writelines("<title>400 Bad Request</title>\n")
  client.writelines("<h2>400 Bad Request</h2>\n")

def Responce501(client):
  client.writelines("HTTP/1.1 501 Not Implemented\r\n")
  client.writelines("Content-Type: text/html; charset=utf-8\r\n");
  client.writelines("\r\n")
  client.writelines("<title>501 Not Implemented</title>\n")
  client.writelines("<h2>501 Not Implemented</h2>\n")

def Responce404(client):
  client.writelines("HTTP/1.1 404 Not Found\r\n")
  client.writelines("Content-Type: text/html; charset=utf-8\r\n");
  client.writelines("\r\n")
  client.writelines("<title>404 Not Found</title>\n")
  client.writelines("<h2>404 Not Found</h2>\n")  

def Responce200(client):
  client.writelines("HTTP/1.1 200 OK\r\n")
  client.writelines("Content-Type: text/html; charset=utf-8\r\n");
  client.writelines("\r\n")
  client.writelines("<title>Simple HTTP Server</title>\n")
  client.writelines("<h2>Group 21</h2>\n")

class Client(Thread):
  def __init__(self,conn):
    Thread.__init__(self)
    self.conn = conn

  def run(self):    
    client = self.conn.makefile('r+')
    method, uri, http_ver, junk = (client.readline().strip('\r\n')+"   ").split(' ',3)
    print [method, uri, http_ver]
    if len(http_ver) > 0:
      while True:
        if client.readline() == "\r\n":
          break
    http_ver = parse_ver(http_ver)
    if len(uri)>1 and uri[0] != '/':
      Responce400(client)      
    elif method != 'GET':
      Responce501(client)
    elif len(uri) == 0  or uri == "/":
      Responce200(client)
    else:
      Responce404(client)

    self.conn.close()

s = Server()
s.Init('',8080)
s.Run()
