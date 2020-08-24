#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

inline bool isPrime(reg int x){
	if(x<2)
		return false;
	for(reg int i=2;1ll*i*i<=x;++i)
		if(x%i==0)
			return false;
	return true;
}

int n;

int main(void){
	scanf("%d",&n);
	for(reg int i=1;i<=n;++i){
		static int x;
		scanf("%d",&x);
		puts(isPrime(x)?"Yes":"No");
	}
	return 0;
}