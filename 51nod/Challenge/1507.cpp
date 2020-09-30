#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

inline bool isPrime(reg int n){
	for(reg int i=2;1ll*i*i<=n;++i)
		if(n%i==0)
			return false;
	return true;
}

int n;

int main(void){
	scanf("%d",&n);
	for(reg int i=n+1;;++i)
		if(isPrime(i)){
			printf("%d ",i);
			break;
		}
	for(reg int i=n-1;;--i)
		if(isPrime(i)){
			printf("%d\n",i);
			break;
		}
	return 0;
}