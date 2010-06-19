#ifndef _db_h
#define _db_h
#include<map>
#include<string>
#include<vector>
using namespace std;
class Item {
  public:
    string title, artist, filename;
};

class PlayList {
public:
  PlayList(const string& str);
  PlayList& operator+=(int id);
  unsigned count()const;
  int operator[](int i)const;
  void show(); //for debug
private:
  string name;
  vector<int> list;
};

class DB {
public:
  DB();
  DB& operator+=(const Item& t);
  DB& operator+=(const PlayList&);
  const vector<int>& getTagId(const string& tag);
  int getId(const string& filename);
  void setTag(const Item&, const string&);
  
  const vector<Item>& getMaster() const;
  const vector<PlayList>& getPlayList() const;
  void write(const string& name);

  void showAll(); //for debug
private:
  vector<Item> master;
  map<string, int> file_name_map;
  map<string, vector<int> > tag_map;
  vector<PlayList> p;
};
#endif
