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
{// 指標會自行判斷使用者輸入的長度 *argv[]不會受長度影響
    ifstream infile; //infile繼承ifstream物件特性
    infile.open(argv[1],ifstream::out); //開啟檔案argv[1]
    if(!infile.good())
    {
        cout << "檔案無法開啟!!";
        return 0;
    }
    //從檔案的尾端開始往前讀128bytes
    infile.seekg(-128,ifstream::end);
    while(i<3)
        //cout << (char) infile.get();
        TAG[i++]=infile.get();  //儲存TAG 字元 以便後來判斷
    infile.seekg(0,ifstream::cur);
    //0 代表它的距離  cur 代表目前位置開始
    // 這裡用來從目前的位置往後讀
    for(i=0;i<30;i++)
        title[i]=infile.get(); //  儲存歌曲名稱30個位置
    infile.seekg(0,ifstream::cur);
    for(i=0;i<30;i++)
        artist[i]=infile.get(); //  儲存歌手名稱30個位置
    infile.seekg(0,ifstream::cur);
    for(i=0;i<30;i++)
        album[i]=infile.get(); //  儲存專輯名稱30個位置
    infile.seekg(0,ifstream::cur);
    for(i=0;i<4;i++)
        year[i]=infile.get(); //  儲存年份4個位置
    infile.seekg(0,ifstream::cur);
    for(i=0;i<30;i++)
        comment[i]=infile.get(); //  儲存註解30個位置
    infile.seekg(0,ifstream::cur);
    kind=infile.get();
    infile.close();//關檔案
    if(TAG[0]!='T' || TAG[1]!='A' || TAG[2]!='G' )
        return 0;//判斷是否為ID3(v1的標籤)
        //輸出內容
    title[30]=0;
    cout << "歌曲名稱:"<< title<< '\n';
    artist[30]=0;
    cout << "歌手名稱:" << artist<< '\n';
    album[30]=0;
    cout << "專輯名稱 :" << album << '\n';
    year[4]=0;
    cout << "出版年份 :"<< year<<'\n';
    cout << "註解內容:";
    if(comment[28]==0)
    {
        order=comment[29];
        cout << comment << '\n';
        cout << "歌曲順序 :" << order << '\n';
    }
    else
    {
        comment[30]=0;
        cout << comment << '\n';
    }
    cout << "音樂類別 :" << list[kind];
}
