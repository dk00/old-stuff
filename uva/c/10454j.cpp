#include<stdio.h>
#include<string.h>
#define Size 10
#define D 1000000000ll
char ___tmp[Size*10];
class bigint{
public:
long long d,s[Size];
            bigint    (               ){d=1,s[0]=0;}
    bigint& operator= (const int&    n){s[0]=n%D;s[1]=n/D;d=s[1]?2:1;}
    bigint& operator= (const char   *c);
    bigint& operator+=(const bigint& n);
//  bigint& operator-=(const bigint& n);
    bigint& operator*=(const int&    n);
    bigint  operator* (const bigint& n);
    bigint& operator*=(const bigint& b);
    bigint& operator/=(const int&    n);
    bool    operator< (const bigint& n);
    bool    operator<=(const bigint& n);
    bool    operator==(const bigint& n);
    char*   tostring  (char*    c=NULL);
};
bigint& bigint::operator=(const char *c){
    while(*c=='0' && c[1])c++;
int i,j=strlen(c);
    for(d=0;j>0;d++,j-=9)
        for(s[d]=0,i=j<9?0:j-9;i<j;i++)
            s[d]=s[d]*10+c[i]-'0';
    return *this;
}
char *bigint::tostring(char* c){
    if(c==NULL)
        c=___tmp;
int i,j;
    sprintf(c,"%lld",s[d-1]);
    j=strlen(c);
    for(i=d-2;i>=0;i--,j+=9)
        sprintf(c+j,"%09lld",s[i]);
    return c;
}
bigint& bigint::operator+=(const bigint& n){
int i;
    for(i=d;i<=n.d;i++)s[i]=0;
    if(d<n.d)d=n.d;
    for(i=0;i<d;i++){
        s[i]+=n.s[i];
        if(s[i]>=D)
            s[i]-=D,s[i+1]++;
    }
    if(s[d]>0)d++;
    return *this;
}
bigint& bigint::operator*=(const int& n){
int i;
    s[d]=0;
    for(i=0;i<d;i++)s[i]*=n;
    for(i=0;i<d;i++)
        if(s[i]>=D)
            s[i+1]+=s[i]/D,s[i]%=D;
    if(s[d]>0)d++;
    return *this;
}
bigint bigint::operator*(const bigint& b){
    bigint tmp;
    tmp=*this;
    tmp*=b;
    return tmp;
}
bigint& bigint::operator*=(const bigint& b){
bigint a=*this;
int i,j;
const long long *p=a.s,*q=(&b==this)?a.s:b.s;
    d=a.d+b.d;
    for(i=0;i<d;i++)s[i]=0;
    for(i=0;i<a.d;i++){
        for(j=0;j<b.d;j++)
            s[i+j]+=p[i]*q[j];
        for(j=0;j<d;j++)
            if(s[j]>=D)
                s[j+1]+=s[j]/D,s[j]%=D;
    }
    for(i=d-1;s[i]==0;i--);
    d=i+1;
    return *this;
}
bigint& bigint::operator/=(const int& n){
    for(int i=d-1;i>0;i--){
        s[i-1]+=(s[i]%n)*D;
        s[i]/=n;
    }
    s[0]/=n;
    while(d>1 && !s[d-1])d--;
    return *this;
}
bool bigint::operator<(const bigint& n){
    if(d<n.d)return true;
    if(d>n.d)return false;
    int i;
    for(i=d-1;i>0 && s[i]==n.s[i];i--);
    return(s[i]<n.s[i]);
}
bool bigint::operator<=(const bigint& n){
    if(d<n.d)return true;
    if(d>n.d)return false;
    int i;
    for(i=d-1;i>0 && s[i]==n.s[i];i--);
    return(s[i]<=n.s[i]);
}
bool bigint::operator==(const bigint& n){
    if(d-n.d)return false;
    int i;
    for(i=d-1;i>0 && s[i]==n.s[i];i--);
    return(s[i]==n.s[i]);
}

bigint C[101];
void setcnum(){
C[1]="1";C[2]="1";C[3]="2";C[4]="5";C[5]="14";C[6]="42";C[7]="132";
C[8]="429";C[9]="1430";C[10]="4862";C[11]="16796";C[12]="58786";
C[13]="208012";C[14]="742900";C[15]="2674440";C[16]="9694845";
C[17]="35357670";C[18]="129644790";C[19]="477638700";C[20]=
"1767263190";C[21]="6564120420";C[22]="24466267020";C[23]=
"91482563640";C[24]="343059613650";C[25]="1289904147324";
C[26]="4861946401452";C[27]="18367353072152";C[28]="69533550916004";
C[29]="263747951750360";C[30]="1002242216651368";
C[31]="3814986502092304";C[32]="14544636039226909";
C[33]="55534064877048198";C[34]="212336130412243110";
C[35]="812944042149730764";C[36]="3116285494907301262";
C[37]="11959798385860453492";C[38]="45950804324621742364";
C[39]="176733862787006701400";C[40]="680425371729975800390";
C[41]="2622127042276492108820";C[42]="10113918591637898134020";
C[43]="39044429911904443959240";C[44]="150853479205085351660700";
C[45]="583300119592996693088040";C[46]="2257117854077248073253720";
C[47]="8740328711533173390046320";
C[48]="33868773757191046886429490";
C[49]="131327898242169365477991900";
C[50]="509552245179617138054608572";
C[51]="1978261657756160653623774456";
C[52]="7684785670514316385230816156";
C[53]="29869166945772625950142417512";
C[54]="116157871455782434250553845880";
C[55]="451959718027953471447609509424";
C[56]="1759414616608818870992479875972";
C[57]="6852456927844873497549658464312";
C[58]="26700952856774851904245220912664";
C[59]="104088460289122304033498318812080";
C[60]="405944995127576985730643443367112";
C[61]="1583850964596120042686772779038896";
C[62]="6182127958584855650487080847216336";
C[63]="24139737743045626825711458546273312";
C[64]="94295850558771979787935384946380125";
C[65]="368479169875816659479009042713546950";
C[66]="1440418573150919668872489894243865350";
C[67]="5632681584560312734993915705849145100";
C[68]="22033725021956517463358552614056949950";
C[69]="86218923998960285726185640663701108500";
C[70]="337485502510215975556783793455058624700";
C[71]="1321422108420282270489942177190229544600";
C[72]="5175569924646105559418940193995065716350";
C[73]="20276890389709399862928998568254641025700";
C[74]="79463489365077377841208237632349268884500";
C[75]="311496878311103321137536291518809134027240";
C[76]="1221395654430378811828760722007962130791020";
C[77]="4790408930363303911328386208394864461024520";
C[78]="18793142726809884575211361279087545193250040";
C[79]="73745243611532458459690151854647329239335600";
C[80]="289450081175264899454283846029490767264392230";
C[81]="1136359577947336271931632877004667456667613940";
C[82]="4462290049988320482463241297506133183499654740";
C[83]="17526585015616776834735140517915655636396234280";
C[84]="68854441132780194707888052034668647142985206100";
C[85]="270557451039395118028642463289168566420671280440";
C[86]="1063353702922273835973036658043476458723103404520";
C[87]="4180080073556524734514695828170907458428751314320";
C[88]="16435314834665426797069144960762886143367590394940";
C[89]="64633260585762914370496637486146181462681535261000";
C[90]="254224158304000796523953440778841647086547372026600";
C[91]="1000134600800354781929399250536541864362461089950800";
C[92]="3935312233584004685417853572763349509774031680023800";
C[93]="15487357822491889407128326963778343232013931127835600";
C[94]="60960876535340415751462563580829648891969728907438000";
C[95]="239993345518077005168915776623476723006280827488229600";
C[96]="944973797977428207852605870454939596837230758234904050";
C[97]="3721443204405954385563870541379246659709506697378694300";
C[98]="14657929356129575437016877846657032761712954950899755100";
C[99]="57743358069601357782187700608042856334020731624756611000";
C[100]="227508830794229349661819540395688853956041682601541047340";
}
bigint calc(char *s)
{
    int i,j,n=0,cnt=0,star=1;
    bigint sum,num[100];
    if(s[0]=='(')
    {
        for(i=1,cnt=1;cnt && s[i];i++)
        {
            if(s[i]=='(')cnt++;
            if(s[i]==')')cnt--;
        }
        if(!s[i])
        {
            s[i-1]=0;
            return calc(s+1);
        }
    }
    for(cnt=0,i=0;s[i];i++)
    {
        if(s[i]=='(')cnt++;
        if(s[i]==')')cnt--;
        if(cnt)continue;
        if(s[i]=='+')star=0;
    }
    for(i=0;s[i];i++)
    {
        if(s[i]=='*' || s[i]=='+')continue;
        if(s[i]=='(')
        {
            cnt=1;
            for(j=i+1;cnt;j++)
            {
                if(s[j]=='(')cnt++;
                if(s[j]==')')cnt--;
            }
        }
        else j=i+1;
        if(star || s[j]!='*')
        {
            if(j==i+1)
                num[n++]=1;
            else
            {
                s[j-1]=0;
                num[n++]=calc(s+i+1);
                s[j-1]=')';
            }
        }
        else
        {
            for(cnt=0,j++;cnt || (s[j] && s[j]!='+');j++)
            {
                if(s[j]=='(')cnt++;
                if(s[j]==')')cnt--;
                if(cnt)continue;
            }
            char tmp;tmp=s[j],s[j]=0;
            num[n++]=calc(s+i);
            s[j]=tmp;
        }
        i=j-1;
    }
    for(i=0,sum=1;i<n;i++)
        sum*=num[i];
    return sum*C[n];
}
main()
{
    setcnum();
    char s[1000];
    while(scanf("%s",s)!=EOF)
        printf("%s\n",calc(s).tostring());
}
