#ifndef _itunes
#define _itunes
#include<vector>
#include<cstdint>
using namespace std;
union _node {
  uint8_t buf[1];
	struct {
		char id[4];
		uint32_t len;
		uint32_t size;
		uint8_t u1[4];
		uint8_t u2[2];
		char spc0[54];
		uint8_t hash[20];
	} database;
	struct {
		char id[4];
		uint32_t len;
		uint32_t size;
    uint32_t type;
	} dataset;
	struct {
		char id[4];
		uint32_t len;
    uint32_t num;
	} list;
	struct {
		char id[4];
		uint32_t len, size, nstr, tid, visible;
		char type[4];
		uint8_t type0, type1, cf, rating;
		uint32_t mtime;
		uint32_t tsize;
    uint32_t tlen;
		uint32_t tnum;
		uint32_t total;
		uint32_t year;
		uint32_t brate;
		uint32_t srate;
    uint32_t vol;
		uint32_t start;
		uint32_t stop;
    uint32_t scheck;
		uint32_t pcnt;
		uint32_t pcnt1;
		uint32_t lastplay;
		uint32_t dnum;
		uint32_t dtotal;
		uint32_t drmuid;
		uint32_t adddate;
		uint32_t btime;
    uint64_t dbid;
		uint8_t chcek;
		uint8_t arating;
		uint16_t bpm;
    uint16_t acnt;
		uint16_t unk9;
    uint32_t asize;
		uint32_t unk11;
		uint32_t srate1;
		uint32_t rdate;
		uint16_t unk14;
		uint16_t ef;
		uint32_t unk15;
		uint32_t unk16;
		uint32_t skipcnt;
		uint32_t lastskip;
    uint8_t hasa;
		uint8_t sskip;
		uint8_t playpos;
		uint8_t flag4;
    uint64_t dbid2;

    uint32_t flag176;
    uint32_t unk21, pregap;
    uint32_t scnt0, scnt1;
    uint32_t unk25, postgap, unk27;

    uint32_t mediatype;
		uint32_t snum,epi;
		uint32_t unk31,unk32,unk33, unk34, unk35, unk36, unk37;
		uint32_t gapless;
		uint32_t unk38;
		uint32_t tf;
		uint16_t af;
		uint8_t unk39[20];
		uint32_t unk40, unk41, unk42, unk43;
		uint16_t unk44;
	} trackitem;
	struct {
		char id[4];
		uint32_t len, size, dnum, inum;
    uint8_t master;
		uint8_t unk[3];
		uint32_t time;
    uint64_t pid;
		uint32_t unk3;
    uint16_t nstr;
		uint8_t pf, gf;
    uint32_t order;
	} playlist;
	struct {
		char id[4];
		uint32_t len, size, dnum;
		uint16_t gf;
		uint8_t unk2, unk3;
		uint32_t gid, tid, time, grpref, unk4, unk5;
		uint64_t unk6;
	} playlistitem;
	struct {
		char id[4];
		uint32_t len, size, type;
    uint8_t data[1];
  } dataobj;
	struct {
		char id[4];
		uint32_t len, size, type, unk1, unk2, pos, strlen, unk, unk4;
    uint8_t str[1];
	} stringobj;
	struct {
		char id[4];
		uint32_t len, size, type, unk1, unk2, pos;
		uint8_t pad[16];
	} orderobj;
	struct {
		char id[4];
		uint32_t len, size;
	} common;
};

class node {
public: 
  node(const uint8_t def[]);
  node(const uint8_t def[], int len);
  ~node();
  void append(node *ch);
  _node *data;
  vector<node *> child;
};

#endif
