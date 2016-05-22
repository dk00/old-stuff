#include<cstdio>
int main(int argc, char **argv) {
  unsigned int port = 65637, id = 257;
  bool topo = false;
  for (i = 1; i + 1 < argc; ++i) {
    if (!strcmp(argv[i], "-p"))
      sscanf(argv[++i], &port);
    else if (!strcmp(argv[i], "-t"))
      topo |= serv.Load(argv[++i]);
    else if (!strcmp(argv[i], "-d"))
      sscanf(argv[++i], "%d", &id);
  }
  if (!serv.SetPort(port))
    return 0;
  while (1) {
    serv.Wait();
    if (!strcmp(cmd, "send"))
      serv.Send();
    else if (!strcmp(cmd, "update")) {
      scanf("%d %d", &id, &cost);
      serv.Update(id, cost);
    }
    else if (!strcmp(cmd, "display"))
      serv.Display()
  }
}
