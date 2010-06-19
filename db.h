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
  void operator+=(int id);
  PlayList(string);

  void show(); //for debug
private:
  string name;
  vector<int> list;
};

class DB {
public:
  DB();
  int operator+=(Item& t);
  vector<int>& getTagId(string tag);
  int getId(string filename);
  void setTag(Item&, string);
  void addPlayList(PlayList&);
  void write(FILE *fp);
  const vector<int>& getMaster();
  const vector<PlayList>& getPlayList();

  void showAll(); //for debug
private:
  vector<Item> master;
  map<string, int> file_name_map;
  map<string, vector<int> > tag_map;
  vector<PlayList> p;
};

