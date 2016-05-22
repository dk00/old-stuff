#ifndef _NSET_H
#define _NSET_H

typedef struct{
	char *data;
	int len, numdata;
	int lastChunkNo;
} NaiveSet;

int initNSet(NaiveSet *s);
int chkNSet(NaiveSet *s, int blk_no);
int chkDone(NaiveSet *s);
int setNSet(NaiveSet *s, int blk_no);
int setLastChunk(NaiveSet *s, int lastblkno);
#endif
