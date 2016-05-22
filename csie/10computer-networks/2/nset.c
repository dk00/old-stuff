#include "nset.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

int initNSet(NaiveSet *s){
	s->len = 70000;
	s->data = malloc( s->len );
	if(s->data == NULL)
		return -1;
	memset(s->data, 0, s->len);
	s->lastChunkNo = -1;
	s->numdata = 0;
	fprintf(stderr, "initNSet!\n");
	return 0;
}
int chkNSet(NaiveSet *s, int blkno){
	if(blkno >= s->len)
		return 0;
	if(s->data[blkno])
		return 1;
	return 0;
}
int chkDone(NaiveSet *s){
	return (s->lastChunkNo >= 0) && ((s->numdata) == (s->lastChunkNo)+1);
}
int setNSet(NaiveSet *s, int blkno){
	if(blkno >= s->len){
		int bsize = s->len * 2;
		if(bsize <= blkno) bsize = blkno + 1;
		char *w = malloc(bsize);
		if(w == NULL)
			return -1;
		memset(w, 0, sizeof(w));
		int i;
		for(i = 0; i < s->len; i++)
			w[i] = s->data[i];
		free(s->data);
		s->data = w;
		s->len = bsize;
	}
	if(s->data[ blkno ] == 0){
		s->data[ blkno ] = 1;
		++s->numdata;
	}
	return 0;
}
int setLastChunk(NaiveSet *s, int lastblkno){
	s->lastChunkNo = lastblkno;
	return 0;
}
