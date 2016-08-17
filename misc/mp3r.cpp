#include <iostream>
#include <fstream>
using namespace std;
char TAG[3];
char title[30],artist[30],album[30],comment[30],year[4];
char *list[]= {"Blues","Classic Rock","Country","Dance","Disco",
"Funk","Grunge","Hip-Hop","Jazz","Metal","NewAge","Oldies","Other",
"Pop","R&B","Rap","Reggae","Rock","Techno","Industrial",
"Alternative","Ska","DeathMetal","Pranks","Soundtrack",
"Euro-Techno","Ambient","Trip-Hop","Vocal","Jazz+Funk","Fusion",
"Trance","Classical","Instrumental","Acid","House","Game",
"Sound Clip","Gospel","Noise","Alt.Rock","Bass","Soul","Punk",
"Space","Meditative","Instrum.Pop","Instrum.Rock","Ethnic","Gothic",
"Darkwave","Techno-Indust.","Electronic","Pop-Folk","Eurodance",
"Dream","SouthernRock","Comedy","Cult","Gangsta","Top40",
"ChristianRap","Pop/Funk","Jungle","NativeAmerican","Cabaret",
"NewWave","Psychadelic","Rave","Showtunes","Trailer",
"Lo-Fi","Tribal","Acid Punk","Acid Jazz","Polka","Retro","Musical",
"Rock&Roll","HardRock","Folk","Folk/Rock","NationalFolk","Swing",
"Fusion","Bebob","Latin","Revival","Celtic","Bluegrass",
"Avantgarde","Gothic Rock","Progress. Rock","Psychadel. Rock",
"Symphonic Rock","Slow Rock","Big Band","Chorus","Easy Listening",
"Acoustic","Humour","Speech","Chanson","Opera","Chamber Music",
"Sonata","Symphony","Booty Bass","Primus","Porn Groove","Satire",
"Slow Jam","Club","Tango","Samba","Folklore","Ballad",
"Power Ballad","Rhythmic Soul","Freestyle","Duet","Punk Rock",
"Drum Solo","A Capella","Euro-House","DanceHall","Goa","Drum&Bass",
"Club-House","Hardcore","Terror","Indie","BritPop","Negerpunk",
"Polsk Punk","Beat","Christian Gangsta Rap","Heavy Metal",
"BlackMetal","Crossover","ContemporaryChristian","ChristianRock",
"Merengue","Salsa","Thrash Metal","Anime","Jpop","Synthpop"}; 
int order,kind,i=0;
main(int argc, char *argv[])
{// ���з|�ۦ�P�_�ϥΪ̿�J������ *argv[]���|�����׼v�T
    ifstream infile; //infile�~��ifstream����S��
    infile.open(argv[1],ifstream::out); //�}���ɮ�argv[1]
    if(!infile.good())
    {
        cout << "�ɮ׵L�k�}��!!";
        return 0;
    }
    //�q�ɮת����ݶ}�l���eŪ128bytes
    infile.seekg(-128,ifstream::end);
    while(i<3)
        //cout << (char) infile.get();
        TAG[i++]=infile.get();  //�x�sTAG �r�� �H�K��ӧP�_
    infile.seekg(0,ifstream::cur);
    //0 �N�����Z��  cur �N��ثe��m�}�l
    // �o�̥Ψӱq�ثe����m����Ū
    for(i=0;i<30;i++)
        title[i]=infile.get(); //  �x�s�q���W��30�Ӧ�m
    infile.seekg(0,ifstream::cur);
    for(i=0;i<30;i++)
        artist[i]=infile.get(); //  �x�s�q��W��30�Ӧ�m
    infile.seekg(0,ifstream::cur);
    for(i=0;i<30;i++)
        album[i]=infile.get(); //  �x�s�M��W��30�Ӧ�m
    infile.seekg(0,ifstream::cur);
    for(i=0;i<4;i++)
        year[i]=infile.get(); //  �x�s�~��4�Ӧ�m
    infile.seekg(0,ifstream::cur);
    for(i=0;i<30;i++)
        comment[i]=infile.get(); //  �x�s����30�Ӧ�m
    infile.seekg(0,ifstream::cur);
    kind=infile.get();
    infile.close();//���ɮ�
    if(TAG[0]!='T' || TAG[1]!='A' || TAG[2]!='G' )
        return 0;//�P�_�O�_��ID3(v1������)
        //��X���e
    title[30]=0;
    cout << "�q���W��:"<< title<< '\n';
    artist[30]=0;
    cout << "�q��W��:" << artist<< '\n';
    album[30]=0;
    cout << "�M��W�� :" << album << '\n';
    year[4]=0;
    cout << "�X���~�� :"<< year<<'\n';
    cout << "���Ѥ��e:";
    if(comment[28]==0)
    {
        order=comment[29];
        cout << comment << '\n';
        cout << "�q������ :" << order << '\n';
    }
    else
    {
        comment[30]=0;
        cout << comment << '\n';
    }
    cout << "�������O :" << list[kind];
}
