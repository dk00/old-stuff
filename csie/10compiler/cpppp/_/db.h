#include<map>
#include<string>
#include<vector>
using namespace std;
struct Item {
  string title, artist, filename;
};

class PlayList {
public:
  void operator+=(int id);
  PlayList();
private:
  string name;
  vector<string> list;
};

class DB {
public:
  DB();
  int operator+=(Item& t);
  vactor<int>& getId(string& tag);
  int getId(string& filename);
  void write(FILE *fp);
private:
  vector<Item> master;
  map<string, int> file_name_map;
  map<string, vector<int> > tag_map;
  vector<PlayList> p;
};

