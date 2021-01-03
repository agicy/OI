#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

inline ll gcd(reg ll a,reg ll b){
	return b?gcd(b,a%b):a;
}

ll a,b;

int main(void){
	scanf("%lld%lld",&a,&b);
	reg ll up=2*a*b-a-b-1;
	reg ll dn=6;
	reg ll d=gcd(up,dn);
	printf("%lld/%lld\n",up/d,dn/d);
	return 0;
}