#include <iostream>
#include <string>
using namespace std;

int main()
{
   string response;
   int    width, height;

   do {
      cout << "left" << endl; // endl auto-flushes
      cin >> response;
   } while (response != "fail");

   width = 0;
   do {
      ++width;
      cout << "right" << endl;
      cin >> response;
   } while (response != "fail");

   do {
      cout << "up" << endl;
      cin >> response;
   } while (response != "fail");

   height = 0;
   do {
      ++height;
      cout << "down" << endl;
      cin >> response;
   } while (response != "fail");

   cout << width*height << endl;
   return 0;
}
