#include<stdio.h>
#include<math.h>
#define N 10000

struct Queue{
	int num ;
	int step ;
}queue[N+1] ;
int hash[N] ;
void initial( void )
{
	int i ;

	for( i=0 ; i<N ; i++ ) hash[i] = 0 ;
	/* 0->notused 1->used 2->target */
}
int input( void )
{
	int i , sum , tmp ;

	for( sum=i=0 ; i<4 ; i++ ){
		scanf( "%d" , &tmp ) ;
		sum += tmp * (int)pow( 10 , i ) ;
	}

	return sum ;
}
int check( int num )
{
	if( num<0 ) return 9 ;
	if( num>9 ) return 0 ;
	return num ;
}
int bfs( void )
{
	int head , tail , i , j , tmp[4] , num ;

	for( head=tail=0 ; head<=tail ; head++ ){
		if( hash[ queue[head].num ]==2 ) return queue[head].step ;

		num = queue[head].num ;
		for( i=3 ; i>=0 ; i-- ){ /* Decode */
			tmp[i] = num / (int)pow( 10 , i ) ;
			num %= (int)pow( 10 , i ) ;
		}

		for( i=0 ; i<4 ; i++ ){
			tmp[i] = check( ++tmp[i] ) ;
			for( num=j=0 ; j<4 ; j++ ) /* Encode */
				num += tmp[j] * (int)pow( 10 , j ) ;
			if( hash[num]!=1 ){
				tail++ ;
				queue[tail].num = num ;
				queue[tail].step = queue[head].step + 1 ;
			}
			if( hash[num]==2 ) return queue[tail].step ;
			hash[num] = 1 ;
			tmp[i] = check( --tmp[i] ) ;

			tmp[i] = check( --tmp[i] ) ;
			for( num=j=0 ; j<4 ; j++ ) /* Encode */
				num += tmp[j] * (int)pow( 10 , j ) ;
			if( hash[num]!=1 ){
				tail++ ;
				queue[tail].num = num ;
				queue[tail].step = queue[head].step + 1 ;
			}
			if( hash[num]==2 ) return queue[tail].step ;
			hash[num] = 1 ;
			tmp[i] = check( ++tmp[i] ) ;
		}
	}

	return -1 ;
}
int main( void )
{
	int n , num , limit ;

/*	freopen( "C:\\windows\\desktop\\10067.in" , "r" , stdin ) ;*/
	scanf( "%d" , &n ) ;
	for( ; n ; n-- ){
		initial() ;

		num = input() ; /* situation of beginning */
		queue[0].num = num ;
		queue[0].step = 0 ;
		hash[num] = 1 ;

		num = input() ; /* situation of target */
		hash[num] = 2 ;

		scanf( "%d" , &limit ) ; /* input limit */
		for( ; limit ; limit-- ) hash[input()] = 1 ;

		printf( "%d\n" , bfs() ) ;
	}

	return 0 ;
}
/* @END_OF_SOURCE_CODE */
