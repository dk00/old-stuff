#include <iostream>
#include <cstdlib>
using namespace std;

int cmp_int(const void *a, const void *b) {

const int *ia = (const int *) a;
const int *ib = (const int *) b;

return (*ia > *ib) - (*ia < *ib);
}

int main () {

int numberOfCases;
cin >> numberOfCases;

for(int cases = 0; cases < numberOfCases; cases++) {

int n;
cin >> n;

int people[n];
// reading the vector
for(int i = 0; i < n ; i++) {
int time;
cin >> time;
people[i] = time;
}
if(n<=1){
    cout<<people[0]<<'\n';
    cout<<people[0]<<'\n';
    continue;
}
// sorting
qsort(people, n, sizeof(int), cmp_int);

int peopleLeft = n;
int timeSpent = 0;
int moves[3*n];
int pos = 0;
while(peopleLeft > 3) {
int a, b, x, y;
a = people[0];
b = people[1];
x = people[peopleLeft-2];
y = people[peopleLeft-1];

int time1 = b + a + y + b;
int time2 = x + a + y + a;

peopleLeft -=2;
if(time1 < time2) {
moves[pos] = a;
moves[pos+1] = b;

moves[pos+2] = a;

moves[pos+3] = x;
moves[pos+4] = y;

moves[pos+5] = b;
pos += 6;

timeSpent += time1;
}
else {
moves[pos] = a;
moves[pos+1] = x;

moves[pos+2] = a;

moves[pos+3] = a;
moves[pos+4] = y;

moves[pos+5] = a;
pos += 6;

timeSpent += time2;
}
}

if(peopleLeft == 3) {
moves[pos] = people[0];
moves[pos+1] = people[2];

moves[pos+2] = people[0];

moves[pos+3] = people[0];
moves[pos+4] = people[1];

timeSpent += people[2] + people[1] + people[0];
}
else {
moves[pos] = people[0];
moves[pos+1] = people[1];

timeSpent += people[1];
}

if(cases > 0 ) {
cout << endl;
}
cout << timeSpent << endl;

peopleLeft = n;
int i = 0;
while(peopleLeft > 2){
cout << moves[i] << " " << moves[i+1] << endl << moves[i+2] << endl;
i +=3;
peopleLeft--;
}
cout << moves[i] << " " << moves[i+1] << endl;
}
return 1;

}
