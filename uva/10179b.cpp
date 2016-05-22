#include <stdio.h>
#include <math.h>
int isprime(long n){
    int r = ceil(sqrt(n));
    int i;
    if(n==2) return 1;
    if(!(n%2)) return 0;
    for(i=3; i<=r; i+=2)
    if(!(n%i)) return 0;
    return 1;
}
int main(){
long m, n;
double count;
long i, root;
while(scanf("%ld", &n) && n){
    count = n;
    root = ceil(sqrt(n));
    for(i=2; i<root; i++)
        if(!(n%i)){
            m = n / i;
            if(isprime(i))
                count *= (1.0 - 1.0 / (double)i);
            if(isprime(m))
                count *= (1.0 - 1.0 / (double)m);
        }
    if(!(n%root) && isprime(root))
        count *= (1.0 - 1.0 / (double)root);
    if(count==n) count--;
    printf("%.0lf\n", count);
}
}
