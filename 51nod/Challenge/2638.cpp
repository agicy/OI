#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

int a,b;

inline int gcd(reg int a,reg int b){
	return b?gcd(b,a%b):a;
}

int main(void){
	scanf("%d%d",&a,&b);
	reg int d=gcd(a,b);
	printf("%d %d\n",a/d,b/d);
	return 0;
}