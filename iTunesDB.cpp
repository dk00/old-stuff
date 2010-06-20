#include"db.h"
#include"debug.h"
#include"utils.h"
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

void MakeItem(node *r, const Item& t, int id) {
  node *c = new node(def_item);
  c->data->trackitem.nstr = 2;
  c->data->trackitem.tid = id;
  c->data->trackitem.tlen = 1;
  c->data->trackitem.dbid = id;
  if (t.artist.length() > 0) {
    MakeString(c, 4, t.artist);
    c->data->trackitem.nstr++;
  }
  string tmp = GetType(t.filename);
  strncpy(c->data->trackitem.type, tmp.c_str(), 4);
  int i;
  for (i = t.filename.length() - 1;i > 0 && t.filename[i-1]!='.'; --i);
  if (i <= 0) tmp = "";
  else tmp = t.filename.c_str() + i;
  MakeString(c, 6, tmp);
  c->data->trackitem.mediatype = 1;
  if (tmp == "mp4") {
    c->data->trackitem.flag176 = 0x100;
    c->data->trackitem.mediatype = 2;
  }
  tmp = ":iPod_Control:Music:" + t.filename;
  MakeString(c, 2, tmp);
  if (t.title.length() > 0) {
    MakeString(c, 1, t.title);
    c->data->trackitem.nstr++;
  }
  r->append(c);
}
void MakeListSet(node *r, const vector<Item>& master, int type) {
  node *c = new node(def_dataset);
  c->data->dataset.type = type;
  node *p = new node(def_track_list);
  p->data->list.num = master.size();
  c->append(p);
  for (int i;i < master.size();++i)
    MakeItem(c, master[i], i + 1);
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
    MakeListItem(c, p[i] + 1);
  r->append(c);
}
void MakeListSet(node *r, const vector<PlayList>& s, int type) {
  node *c = new node(def_dataset);
  c->data->dataset.type = type;
  node *p = new node(def_list_set);
  p->data->list.num = s.size();
  if (type == 3) ++p->data->list.num;
  c->append(p);
  for (int i = 0;i < s.size();++i) {
    MakePlayList(c, s[i]);
    if(i == 0)
      c->child.back()->data->playlist.master = 1;
  }
  if (type == 3) {
    node *podcast = new node(def_podcast);
    podcast->data->playlist.dnum = 1;
    MakeString(podcast, 1, "PodCast");
    //podcast->append(new node(def_podcast_dat1));
    c->append(podcast);    
  }
  r->append(c);
}
int WriteDB(node *r, FILE *fp) {
  long pos = ftell(fp);
  fseek(fp, r->data->common.len, SEEK_CUR);
  int List = 0;
  if (!memcmp(r->data->common.id, "mhlt", 4) || 
      !memcmp(r->data->common.id, "mhlp", 4)) List = 1;
  if (!List) r->data->common.size = 0;  
  for (int i = 0;i < r->child.size();++i) {
    WriteDB(r->child[i], fp);
    r->data->common.size += r->child[i]->data->common.size;  
  }
  if (!List) r->data->common.size += r->data->common.len;
  fseek(fp, pos, SEEK_SET);
  if (!memcmp(r->data->common.id, "mhod", 4)) {
    if(r->data->dataobj.type < 15) {
      r->data->common.size += 16 + r->data->stringobj.strlen;
      fwrite(r->data->buf, 1, r->data->common.size, fp);
    }
    if(r->data->dataobj.type == 100) {
      r->data->common.size = 0x2C;
      fwrite(r->data->buf, 1, r->data->common.size, fp);
    }
  }
  else fwrite(r->data->buf, 1, r->data->common.len, fp);
  if (List) r->data->common.size = r->data->common.len;
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
