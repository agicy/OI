#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

inline int gcd(reg int a,reg int b){
	return b?gcd(b,a%b):a;
}

int n;

int main(void){
	scanf("%d",&n);
	while(n--){
		static int a,b;
		scanf("%d%d",&a,&b);
		printf("%d\n",gcd(a,b));
	}
	return 0;
}