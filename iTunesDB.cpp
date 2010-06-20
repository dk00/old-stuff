#include"db.h"
#include"debug.h"
#include"unicode.h"
#include"iTunesDB.h"
#include"iTunesDB_default.h"
#include<cstdio>
#include<cstdlib>
#include<cstring>

node::node(const uint8_t def[]) {
  int len = ((_node *)def)->common.len;
  data = (_node *)new char[len];
  memcpy(data->buf, def, len);
}

node::node(const uint8_t def[], int add) {
  int len = ((_node *)def)->common.len + add;
  data = (_node *)new char[len];
  memcpy(data->buf, def, len);
}

node::~node() {
  delete data;
}
void node::append(node *ch) {
  child.push_back(ch);
}

const char* GetType(const string& name) {
  int i,j;
  static char type[4] = {' ', ' ', ' ', ' '};
  i = name.length();
  for(j = 1;j < 4;j++)
    type[j] = name[i-j];
  return type;
}

void MakeString(node *r,int type, const string& s) {
  node *c = new node(def_string, s.length()*2 + 16);
  c->data->stringobj.type = type;
  c->data->stringobj.strlen = utf8_to_utf16(c->data->stringobj.str, s);
  r->append(c);
}

void MakeItem(node *r, const Item& t) {
  node *c = new node(def_item);
  MakeString(c, 4, t.artist);
  string tmp = GetType(t.filename);
  strncpy(c->data->trackitem.type, tmp.c_str(), 4);
  int i;
  for (i = t.filename.length() - 1;i > 0 && t.filename[i-1]!='.'; --i);
  if (i <= 0) tmp = "";
  else tmp = t.filename.c_str() + i;
  MakeString(c, 6, tmp);
  tmp = ":iPod_Control:Music:" + t.filename;
  MakeString(c, 2, tmp);
  MakeString(c, 1, t.title);
  r->append(c);
}
void MakeListSet(node *r, const vector<Item>& master, int type) {
  node *c = new node(def_dataset);
  c->data->dataset.type = type;
  node *p = new node(def_track_list);
  p->data->list.num = 2 + master.size();
  c->append(p);
  for (int i;i < master.size();++i)
    MakeItem(c, master[i]);
  r -> append(c);
}
void MakeListItem(node *r, unsigned id) {
  node *c = new node(def_list_item);
  c->data->playlistitem.tid = id;
  node *p = new node(def_order, 20);
  p->data->orderobj.pos = id;
  c->append(p);
  r->append(c);
}
void MakePlayList(node *r, const PlayList& p) {
  node *c = new node(def_list);
  int n = p.count();
  c->data->playlist.inum = n;
  MakeString(c, 1, p.name);
  for(int i = 0;i < n;++i)
    MakeListItem(c, p[i]);
  r->append(c);
}
void MakeListSet(node *r, const vector<PlayList>& s, int type) {
  node *c = new node(def_dataset);
  c->data->dataset.type = type;
  node *p = new node(def_list_set);
  p->data->list.num = s.size();
  c->append(p);
  for(int i = 0;i < s.size();++i)
    MakePlayList(c, s[i]);
  r->append(c);
}
int WriteDB(node *r, FILE *fp) {
  long pos = ftell(fp);
  fseek(fp, r->data->common.len, SEEK_CUR);
  r->data->common.size = 0;  
  for (int i = 0;i < r->child.size();++i) {
    WriteDB(r->child[i], fp);
    r->data->common.size += r->child[i]->data->common.size;  
  }
  r->data->common.size += r->data->common.len;
  fseek(fp, pos, SEEK_SET);
  if (!memcmp(r->data->common.id, "mhod", 4) && r->data->stringobj.type < 15) {
    r->data->common.size += 16 + r->data->stringobj.strlen;
    fwrite(r->data->buf, 1, r->data->common.size, fp);
  }
  else fwrite(r->data->buf, 1, r->data->common.len, fp);
  fseek(fp, pos + r->data->common.size, SEEK_SET);
  return 0;
}

void MakeDB(const DB& db, FILE *fp) {
  node *r = new node(def_db);
  MakeListSet(r, db.getMaster(), 1); 
  MakeListSet(r, db.getPlayList(), 3);
  MakeListSet(r, db.getPlayList(), 2);
  WriteDB(r, fp);
}
