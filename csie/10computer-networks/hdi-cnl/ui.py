class baseUI:
  def __init__(self, serv):
    self.serv = serv
  def setup(self, out):
    self.out = out
class HTML(baseUI):
  def show(self, what):
    self.out.send_header('Content-Type', 'text/plain; charset=utf-8')
    print 'test'

class Java(baseUI):
  def show(self, what):
    print 'test'
