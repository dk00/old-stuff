/* title
  ¼Æ¿W (Sudoku) ¨D¸Ñ
*/

/* comment ************************************************************
   Åª¤J¼Æ¿W (sudoku) ¸ê®ÆÀÉ, ­pºâ¨Ã¦L¥X¼Æ¿W¸Ñ. 

   ¼Æ¿W¸ê®ÆÀÉ®æ¦¡¬°­Y¤zÂI©Òºc¦¨ªº¾ã¼Æ²Õ¦¨. 
   ¼Æ¿Wªº¨C¤@ÂI¥]§t¤T­Ó¾ã¼Æ, ¤À§O¬°ÂI®y¼Ð i j  »P¼Æ¦r n. 
   ¼Æ¿W¸ê®Æ n ¦b [1,M] ¤§¶¡,  i »P j ³£¦b [0,M-1].
   M ¬°¾ã¼Æªº¥­¤è¼Æ, ¨Ò¦p : 9, 16, 25 µ¥µ¥

   ¥»µ{¦¡¥iÅª¨ú¨âºØ¿é¤JÀÉ®×®æ¦¡

   (1)  sudoku.dat ¸ê®ÆÀÉ¦p¤U ( Coordinate ¼Ò¦¡ )

       0 2 1   0 3 8   0 5 7   0 6 3  
       1 1 7   1 4 2   1 7 9   
       2 0 4   2 4 1   2 8 5   
       3 0 3   3 3 4   3 5 5   3 8 2
       4 1 5   4 2 6   4 6 1   4 7 3
       5 0 9   5 3 6   5 5 1   5 8 7
       6 0 2   6 4 5   6 8 8   
       7 1 8   7 4 6   7 7 4   
       8 2 9   8 3 1   8 5 2   8 6 5


    (2)  dudoku.dat2 ¸ê®ÆÀÉ¦p¤U ( Entire_Map ¼Ò¦¡ )

       0 0 1 8 0 7 3 0 0 
       0 7 0 0 2 0 0 9 0 
       4 0 0 0 1 0 0 0 5
       3 0 0 4 0 5 0 0 2
       0 5 6 0 0 0 1 3 0
       9 0 0 6 0 1 0 0 7
       2 0 0 0 5 0 0 0 8
       0 8 0 0 6 0 0 4 0 
       0 0 9 1 0 2 5 0 0 

   NOTE : 
     ¶·¨Ï¥Î²Ä 19 ³¹ªº¶°¦X®e¾¹

**************************************************************/

#include <iostream>
#include <fstream>
#include <iomanip>
#include <set>
#include <cassert>

using namespace std ;


enum  DataFile_Type { Coordinate , Entire_Map };


template <int S = 3>
class  Sudoku {
  private :

    static  const  int  M = S*S ;
    
    set<int>   v[M], h[M] , m[M] ;

    // store number
    int        no[M][M] ;

    // store whether number is fixed
    bool       fixed[M][M] ;




    // (i,j) --> m 
    int  index( int i , int j ) const {  return  (i/S) * S + (j/S) ;  }
    
    // check whether number n at position (i,j) is a valid number 
    bool  valid_number( int n , int i , int j ) const {

        assert( i > -1 && i < M && j > -1 && j < M ) ;
        assert( n >= 1 && n <= M ) ;
        
        if ( h[i].find(n) != h[i].end() ) return false ;
        if ( v[j].find(n) != v[j].end() ) return false ;
        
        int s = index(i,j) ;
        if ( m[s].find(n) != m[s].end() ) return false ;
        
        return true ;
    }

    // insert number n at position (i,j) to all related sets
    void  insert_number( int n , int i , int j ) {

        assert( i > -1 && i < M && j > -1 && j < M ) ;
        assert( n >= 1 && n <= M ) ;

        h[i].insert(n) ;
        v[j].insert(n) ;
        m[index(i,j)].insert(n) ;
    }
    
    // delete number n at position (i,j) from all related sets
    void  delete_number( int n , int i , int j ) {

        assert( i > -1 && i < M && j > -1 && j < M ) ;
        assert( n >= 1 && n <= M ) ;

        h[i].erase(n) ;
        v[j].erase(n) ;
        m[index(i,j)].erase(n) ;
    }

  public :

    // read data from datafile
    Sudoku( char* datafile , DataFile_Type data_type = Coordinate ) {

        int i , j ;
        for ( i = 0 ; i < M ; ++i ) {
            for ( j = 0 ; j < M ; ++j ) {
                no[i][j] = 0 ;
                fixed[i][j] = false ;
            }
        }
        
        // read data file 
        ifstream  infile(datafile) ;

        int n ;

        if ( data_type == Coordinate ) {
            
            // read  position : (i,j) with value : n
            while ( infile ) {
                infile >> i >> j >> n ;  
                if ( i >= 0 && i < M && j >= 0 && j < M && n >= 1 && n <= M ) {
                    no[i][j] = n ;
                    fixed[i][j] = true ;
                    insert_number(n,i,j) ;
                }
            }

        } else if ( data_type == Entire_Map ) {

            // read entire map 
            for ( i = 0 ; i < M ; ++i ) {
                for ( j = 0 ; j < M ; ++j ) {
                    infile >> n ;
                    if ( n > 0 ) {
                        no[i][j] = n ;
                        fixed[i][j] = true ;
                        insert_number(n,i,j) ;
                    }
                }
            }

        }

        cout << "initial chart : \n" << *this << endl ;

        infile.close() ;
        
    }

    // find next position (i,j)
    void  next_position( int& i , int& j ) const {
        if ( i == M ) return ;
        do {
            ++j ;
            if ( j == M ) { ++i ; j = 0 ; }
            if ( i == M ) return ;
        } while ( fixed[i][j] ) ;
    }
    

    // find proper number at position (s,t)
    bool  find_solution( int s = 0 , int t = 0 ) {

        if ( s == M ) {

            return true ;

        } else {

            if ( fixed[s][t] ) next_position(s,t) ;
            
            int i = s , j = t ;

            // find the next possible position (i,j)           
            next_position(i,j) ;

            // fill possible numbers 
            int  n ;
            for ( n = 1 ; n <= M ; ++n ) {
                if ( valid_number(n,s,t) ) {
                    no[s][t] = n ;
                    insert_number(n,s,t) ;
                    if ( find_solution(i,j) ) return true ;
                    no[s][t] = 0 ;
                    delete_number(n,s,t) ;
                } 
            }

            return false ;
            
        }
        
    }
    

    // output 
    friend  ostream& operator<< ( ostream& out , const Sudoku<S>& foo ) {

        char * red = "[0,31m" ;  // use ANSI terminal escape sequence
        char * ec  = "[0m" ;
        
        int i , j ;
        for ( i = 0 ; i < Sudoku<S>::M ; ++i ) {
            if ( i % S == 0 ) 
                out << "  " << setw(3*(M+S)+1) << setfill('-') << "-" << setfill(' ') << endl ;
            for ( j = 0 ; j < Sudoku<S>::M ; ++j ) {
                if ( j % S == 0 ) out << setw(3) << "|" ;
                if ( foo.fixed[i][j] ) out << red ;
                if ( foo.no[i][j] ) 
                    out << setw(3) << foo.no[i][j] ;
                else 
                    out << setw(3) << " " ;

                if ( foo.fixed[i][j] ) out << ec ;
            }
            
            out << setw(3) << "|" << endl ;
        }
        out << "  " << setw(3*(M+S)+1) << setfill('-') << "-" << setfill(' ') << endl ;
        return out ;
    }
            
};



int main() {

    Sudoku<3>  foo("sudoku.dat")  ;
    if ( foo.find_solution() )   cout << "solution :\n" << foo << endl ;


    Sudoku<3>  bar("sudoku.dat2",Entire_Map)  ;
    if ( bar.find_solution() )   cout << "solution :\n" << bar << endl ;

    /*
    Sudoku<4>  foo4("sudoku2.dat")  ;
    if ( foo4.find_solution() )   cout << foo4 << endl ;
    */

    return 0 ;
    
}




/***********************************************************************
  OUTPUT   OUTPUT   OUTPUT   OUTPUT   OUTPUT   OUTPUT   OUTPUT   OUTPUT
 **********************************************************************

initial chart : 
  -------------------------------------
  |        1  |  8     7  |  3        |
  |     7     |     2     |     9     |
  |  4        |     1     |        5  |
  -------------------------------------
  |  3        |  4     5  |        2  |
  |     5  6  |           |  1  3     |
  |  9        |  6     1  |        7  |
  -------------------------------------
  |  2        |     5     |        8  |
  |     8     |     6     |     4     |
  |        9  |  1     2  |  5        |
  -------------------------------------

solution :
  -------------------------------------
  |  5  9  1  |  8  4  7  |  3  2  6  |
  |  8  7  3  |  5  2  6  |  4  9  1  |
  |  4  6  2  |  3  1  9  |  7  8  5  |
  -------------------------------------
  |  3  1  8  |  4  7  5  |  9  6  2  |
  |  7  5  6  |  2  9  8  |  1  3  4  |
  |  9  2  4  |  6  3  1  |  8  5  7  |
  -------------------------------------
  |  2  3  7  |  9  5  4  |  6  1  8  |
  |  1  8  5  |  7  6  3  |  2  4  9  |
  |  6  4  9  |  1  8  2  |  5  7  3  |
  -------------------------------------


initial chart : 
  -------------------------------------
  |        1  |  8     7  |  3        |
  |     7     |     2     |     9     |
  |  4        |     1     |        5  |
  -------------------------------------
  |  3        |  4     5  |        2  |
  |     5  6  |           |  1  3     |
  |  9        |  6     1  |        7  |
  -------------------------------------
  |  2        |     5     |        8  |
  |     8     |     6     |     4     |
  |        9  |  1     2  |  5        |
  -------------------------------------

solution :
  -------------------------------------
  |  5  9  1  |  8  4  7  |  3  2  6  |
  |  8  7  3  |  5  2  6  |  4  9  1  |
  |  4  6  2  |  3  1  9  |  7  8  5  |
  -------------------------------------
  |  3  1  8  |  4  7  5  |  9  6  2  |
  |  7  5  6  |  2  9  8  |  1  3  4  |
  |  9  2  4  |  6  3  1  |  8  5  7  |
  -------------------------------------
  |  2  3  7  |  9  5  4  |  6  1  8  |
  |  1  8  5  |  7  6  3  |  2  4  9  |
  |  6  4  9  |  1  8  2  |  5  7  3  |
  -------------------------------------

 ***********************************************************************/
