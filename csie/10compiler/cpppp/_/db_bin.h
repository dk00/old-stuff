struct node {
  char id[4];
  unsigned char *buf;
  vector<node *> child;
};
