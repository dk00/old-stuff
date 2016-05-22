#include<iostream>
#include<algorithm>
#include<iomanip>
#include<cmath>
#include<cstring>
#include<sstream>

using namespace std;

class bigint {
	public:
		unsigned int v[1000];
		int size;
		static const unsigned int N, Ndigit;
		bigint(int x) {
			memset(v, 0, sizeof(v));
			v[0] = x;
			size = 1;
		}
		bigint() {
			memset(v, 0, sizeof(v));
			size = 0;
		}

		bigint& operator+=(const bigint& x) {
			for(int i=0; i<x.size; i++) {
				v[i] += x.v[i];
				if(v[i] >= N) v[i]-=N, v[i+1]++;
			}
			size = max(size, x.size);
			if(v[size]!=0) size++;
			return *this;
		}
		bigint& operator*=(unsigned int x) {
			unsigned long long carry = 0;
			for(int i=0; i<size; i++) {
				carry += ((unsigned long long)v[i])*x;
				v[i] = carry%N;
				carry /= N;
			}
			if(carry>0) v[size++] = carry;
			return *this;
		}
		bigint& operator/=(unsigned int x) {
			unsigned long long r=0;
			for(int i=size-1; i>=0; i--) {
				unsigned long long a=r*N+v[i];
				v[i] = a/x;
				r = a%x;
			}
			if(v[size-1]==0) size--;
			return *this;
		}
};

const unsigned int bigint::N = 1000000000;
const unsigned int bigint::Ndigit=9;
const double e = exp(1.0);

ostream& operator<<(ostream& os, const bigint& b) {
	os << b.v[b.size-1];
	for(int i=b.size-2; i>=0; i--) 
		os << setw(bigint::Ndigit) << setfill('0') << b.v[i];
	return os;
}

const bigint& C(int n, int m) {
    printf("%d %d\n",n,m);
	static int last_n, last_m;
	static bigint c(1);
	if(m==0) {
		last_n = n, last_m = m;
		c = bigint(1);
	}
	else if(m==1) {
		last_n = n, last_m = m;
		c = bigint(n);
	}
	else {
		while(last_n > n) {
			(c *= (last_n-last_m)) /= last_n;
			last_n--;
		}
		while(last_m < m) {
			(c *= (last_n-last_m)) /= (last_m+1);
			last_m ++;
		}
	}

	return c;
}

bigint P(int n) {
	static const double pi=2*acos(0);
	bigint y;
	int limit=int((n-3+e)/e);
	for(int i=0; i<=limit; i++) 
		y += C(int(n-3+e-i*e)+i, i);
	return y;
}

int main() {
	int n;
	while(cin >> n, n>=0) {
		if(n < 3) cout << "1\n";
		else {
			ostringstream sout;
			cout << P(n) << endl;
		}
	}
	return 0;
}

