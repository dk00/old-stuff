#include<iostream>
#include<fstream>
#include<iomanip>
#include<set>
#include<cassert>
using namespace std;
enum  DataFile_Type{Coordinate,Entire_Map};
template<int S=3>
class Sudoku
{
    static const int M=S*S;
    set<int> v[M],h[M],m[M];
    // store number
    int no[M][M];
    // store whether number is fixed
    bool fixed[M][M];
    //(i,j) --> m
    int index(int i,int j)const{return (i/S)*S +(j/S);}
    // check whether number n at position(i,j) is a valid number
    bool valid_number(int n,int i,int j)const
    {
        assert(i>-1 && i<M && j>-1 && j<M);
        assert(n>=1 && n<=M);
        if(h[i].find(n)!=h[i].end())return false;
        if(v[j].find(n)!=v[j].end())return false;
        int s=index(i,j);
        if(m[s].find(n)!=m[s].end())return false;
        return true;
    }
    // insert number n at position(i,j) to all related sets
    void insert_number(int n,int i,int j)
    {
        assert(i>-1 && i<M && j>-1 && j<M);
        assert(n>=1 && n<=M);
        h[i].insert(n);
        v[j].insert(n);
        m[index(i,j)].insert(n);
    }
    // delete number n at position(i,j) from all related sets
    void delete_number(int n,int i,int j)
    {
        assert(i>-1 && i<M && j>-1 && j<M);
        assert(n >=1 && n<=M);
        h[i].erase(n);
        v[j].erase(n);
        m[index(i,j)].erase(n);
    }
public :
    // read data from datafile
    Sudoku(char* datafile,DataFile_Type data_type=Coordinate)
    {
        int i,j;
        for(i=0;i<M;++i)
        
            for(j=0;j<M;++j)
            {
                no[i][j]=0;
                fixed[i][j]=false;
            }
        // read data file
        ifstream infile(datafile);
        int n;
        if(data_type==Coordinate)
        {   // read  position :(i,j) with value : n
            while(infile)
            {
                infile>>i>>j>>n;
                if(i>=0 && i<M && j>=0 && j<M && n>=1 && n<=M)
                {
                    no[i][j]=n;
                    fixed[i][j]=true;
                    insert_number(n,i,j);
                }
            }

        }
        else if(data_type==Entire_Map)
        {   // read entire map
            for(i=0;i<M;++i)
                for(j=0;j<M;++j)
                {
                    infile >> n;
                    if(n>0)
                    {
                        no[i][j]=n;
                        fixed[i][j]=true;
                        insert_number(n,i,j);
                    }
                }
        }
        cout<<"initial chart : \n"<<*this<<endl;
        infile.close();

    }// find next position(i,j)
    void next_position(int& i,int& j)const
    {
        if(i==M)return;
        do
        {
            j++;
            if(j==M)i++,j=0;
            if(i==M)return;
        }while(fixed[i][j]);
    }// find proper number at position(s,t)
    bool find_solution(int s=0,int t=0)
    {
        if(s==M)
            return true;
        else
        {
            if(fixed[s][t])next_position(s,t);
            int i=s,j=t;
            // find the next possible position(i,j)
            next_position(i,j);
            // fill possible numbers
            int n;
            for(n=1;n<=M;++n)
                if(valid_number(n,s,t))
                {
                    no[s][t]=n;
                    insert_number(n,s,t);
                    if(find_solution(i,j))return true;
                    no[s][t]=0;
                    delete_number(n,s,t);
                }
            return false;
        }
    }// output
    friend ostream& operator<<(ostream& out,const Sudoku<S>& foo)
    {
        char *red="[0,31m"; // use ANSI terminal escape sequence
        char *ec="[0m";
        int i,j;
        for(i=0;i<Sudoku<S>::M;++i)
        {
            if(i%S==0)
                out<<"  "<<setw(3*(M+S)+1)<<setfill('-')<<"-"
                <<setfill(' ')<<endl;
            for(j=0;j<Sudoku<S>::M;++j){
                if(j%S==0)out<<setw(3)<<"|";
                if(foo.fixed[i][j])out<<red;
                if(foo.no[i][j])
                    out<<setw(3)<<foo.no[i][j];
                else
                    out<<setw(3)<<" ";
                if(foo.fixed[i][j])out<<ec;
            }
            out<<setw(3)<<"|"<<endl;
        }
        out<<"  "<<setw(3*(M+S)+1)<<setfill('-')<<"-"<<
        setfill(' ')<<endl;
        return out;
    }
};
int main()
{
    Sudoku<3> foo("sudoku.dat");
    if(foo.find_solution())cout<<"solution :\n"<<foo<<endl;
    Sudoku<3> bar("sudoku.dat2",Entire_Map);
    if(bar.find_solution())cout<<"solution :\n"<<bar<<endl;
    return 0;
}

