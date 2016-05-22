enum Type {NOVEL,COMICS,MANUAL,TEXTBOOK};
typedef struct{
  char title[128];
  enum Type t;
  char ISBN[128];
  char authors[128];
  unsigned v;
}Book;
typedef struct{
  unsigned y;
  unsigned m;
  unsigned d;
}Date;
int today(int y,int m,int d)
{
    static int day[]={0,31,28,31,30,31,30,31,31,30,31,30,31};
    y--;
    int i,num=y*365+y/4-y/100+y/400;
    y++;
    if((y%4==0 && y%100)|| y%400==0)day[2]=29;
    else day[2]=28;
    for(i=1;i<m;i++)
        num+=day[i];
    return num+=d;
}
unsigned library_fine(Book b,Date st,Date ed)
{
    static int l[]={89,9,99,4};
    int i=today(st.y,st.m,st.d),j=today(ed.y,ed.m,ed.d);
    if((j-=i+l[b.t])<=0)return 0;
    while(b.v%2==0)b.v/=2;
    for(i=-2;b.v;i++,b.v/=2);
    return i*j;
}
