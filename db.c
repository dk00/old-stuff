#include "db.h"
void PlayList::operator+=(int id){
  if(id<0)
    fputs("file not found!\n", stderr);
  else
    list.push_back(id);
}

PlayList::PlayList(string str){
  name.assign(str);
}

void PlayList::show(){
  printf("%s:",name.c_str());
  for(int i=0;i<list.size();++i)
    printf(" %d",list[i]);
  puts("");
}

DB::DB(){
}

int DB::operator+=(Item& t){
  file_name_map[t.filename] = master.size();
  master.push_back(t);
}

void DB::addPlayList(PlayList& t){
  p.push_back(t);
}

void DB::setTag(Item& item, string tag){
  tag_map[tag].push_back( file_name_map[item.filename] );
}
  
vector<int>& DB::getTagId(string tag){
  return tag_map[tag];
}

int DB::getId(string filename){
  if(file_name_map.find(filename) == file_name_map.end())
    return -1;
  return file_name_map[filename];
}

void DB::write(FILE *fp){
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

