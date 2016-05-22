/* @JUDGE_ID:4461XX 144 C */
/* A */
#include<stdio.h>
int stu[30] , n , k ;
void swap( int *i , int *j )
{
	int tmp ;
	tmp = *i ;
	*i = *j ;
	*j = tmp ;
}
int gcd( int m , int n )
{
	if( m<n ) swap( &m , &n ) ;
	while( n ){
		m %= n ;
		swap( &m , &n ) ;
	}
	return m ;
}
void count( void )
{
	int i , j=1 , store=0 , hash[30] , people=0 ;
	for( i=0 ; i<n ; i++ ) hash[i] = 0 ;
	for( i=0 ; ; i=(++i)%n ){
		if( hash[i] ) continue ;
		if( !store ){
			store = j ;
			j = (++j) % k ;
			if( !j ) j = k ;
		}
		if( store+stu[i]>=40 ){
			store -= 40-stu[i] ;
			printf( "%3d" , i+1 ) ;
			hash[i] = 1 ;
			people++ ;
		}
		else{
			stu[i] += store ;
			store = 0 ;
		}
		if( people==n ) break ;
	}
}
void main( void )
{
	int lcm , num , i , j ;
	while( scanf( "%d %d" , &n , &k ) == 2 ){
		if( !n && !k ) break ;
		lcm = n * k / gcd( n , k ) ;
		num = ( ( 1 + k ) * lcm / 2 ) / n ;
	/* ( ( (1+k)*k/2 )*( lcm/k ) ) / n */
		for( i=1 ; ; i++ )
			if( num*i>=40 ){
				for( j=0 ; j<n ; j++ ) stu[j] = num * ( i - 1 ) ;
				count() ;
				break ;
			}
		putchar( '\n' ) ;
	}
}
/* @end_of_source_code */
