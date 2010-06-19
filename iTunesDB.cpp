#include"db.h"
#include"unicode.h"
#include"iTunesDB.h"
#include"iTunesDB_default.h"
#include<cstdio>
#include<cstring>

node::node(const uint8_t def[]) {
  memcpy(data.buf, def, def[4] + def[5]*256);
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

void MakeItem(node *&r, const Item& t) {
  r = new node(def_item);
  node *c;
  c = new node(def_string);
  c->data.stringobj.type = 4;
  c->data.stringobj.strlen = 
    utf8_to_unicode(c->data.stringobj.str, t.artist);
  r->append(c);
  c = new node(def_string);
  c->data.stringobj.type = 6;
  c->data.stringobj.strlen = 4;
  strncpy(r->data.trackitem.type, GetType(t.filename), 4);
  r->append(c);
  c = new node(def_string);
  c->data.stringobj.type = 2;
  c->data.stringobj.strlen = utf8_to_unicode(c->data.stringobj.str, 
    ":iPod_Control:Music:" + t.filename);
  r->append(c);
  c = new node(def_string);
  c->data.stringobj.type = 1;
  c->data.stringobj.strlen = 
    utf8_to_unicode(c->data.stringobj.str, t.title);
  r->append(c);
}
void MakeMaster(node *&r, const vector<Item>& master) {
  r = new node(def_dataset);
  node *c;
  c = new node(def_track_list);
  c->data.list.num = 2 + master.size();
  r -> append(c);
  for (int i;i < master.size();++i) {
    MakeItem(c, master[i]);
    r -> append(c);
  }
}
void MakeListItem(node *&r, unsigned id) {
  r = new node(def_list_item);
  r->data.playlistitem.tid = id;
  node *c = new node(def_order);
  c->data.orderobj.pos = id;
  r->append(c);
}
void MakePlayList(node *&r, const PlayList& p) {
  r = new node(def_list);
  int n = p.count();
  r->data.playlist.inum = n;
  node *c;
  c = new node(def_list_dat0);
  r->append(c);
  c = new node(def_list_dat1);
  r->append(c);
  for(int i = 0;i < n;++i) {
    MakeListItem(c, p[i]);
    r->append(c);
  }
}
void MakeListSet(node *&r, const vector<PlayList>& s) {
  r = new node(def_dataset);
  node *c;
  c = new node(def_list_set);
  c->data.list.num = s.size();
  for(int i = 0;i < s.size();++i) {
    MakePlayList(c, s[i]);
    r->append(c);
  }
}
int WriteDB(node *r, FILE *fp) {
  long pos = ftell(fp);
  fseek(fp, r->data.common.len, SEEK_CUR);
  r->data.common.size = 0;
  for (int i = 0;i < r->child.size();++i) {
    WriteDB(r->child[i], fp);
    r->data.common.size += r->child[i]->data.common.size;
  }
  fseek(fp, pos, SEEK_SET);
  fwrite(r->data.buf, 1, r->data.common.len, fp);
}

void MakeDB(const DB& db, FILE *fp) {
  node *r = new node(def_db);
  node *c;
  MakeMaster(c, db.getMaster());
  r->append(c);
  MakeListSet(c, db.getPlayList());
  c->data.dataset.type = 3;
  r->append(c);
  MakeListSet(c, db.getPlayList());
  c->data.dataset.type = 2;
  r->append(c);
  WriteDB(r, fp);
}
