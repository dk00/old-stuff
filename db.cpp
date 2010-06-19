#include"db.h"
#include"iTunesDB.h"
#include<cstdio>
PlayList::PlayList(const string& str) : name(str) {}
PlayList& PlayList::operator+=(int id) {
  if(id >= 0)
    list.push_back(id);
  return *this;
}
unsigned PlayList::count()const {return list.size();}
int PlayList::operator[](int i)const {
  return list[i];
}

void PlayList::show(){
  printf("%s:",name.c_str());
  for(int i=0;i<list.size();++i)
    printf(" %d",list[i]);
  puts("");
}

DB::DB(){
  PlayList p0("iPod");
  p.push_back(p0);
}

DB& DB::operator+=(const Item& t){
  file_name_map[t.filename] = master.size();
  master.push_back(t);
	return *this;
}

DB& DB::operator+=(const PlayList& t){
  p.push_back(t);
	return *this;
}

void DB::setTag(const Item& item, const string& tag){
  tag_map[tag].push_back(file_name_map[item.filename]);
}
  
const vector<int>& DB::getTagId(const string& tag){
	if(tag_map.count(tag))
	  return tag_map[tag];
}

int DB::getId(const string& filename){
  if(file_name_map.count(filename) == 0)
    return -1;
  return file_name_map[filename];
}

const vector<Item>& DB::getMaster() const {
  return master;
}
const vector<PlayList>& DB::getPlayList() const {
  return p;
}

void DB::write(const string& name){
  FILE *fp = fopen(name.c_str(), "wb");
  MakeDB(*this, fp);
  fclose(fp);
}

void DB::showAll(){
  puts("item:");
  for(int i=0;i<master.size();++i)
    printf("%d: %s %s %s\n",i,master[i].title.c_str(),master[i].artist.c_str(),master[i].filename.c_str());
  puts("playList:");
  for(int i=0;i<p.size();++i){
    p[i].show();
  }	
}

