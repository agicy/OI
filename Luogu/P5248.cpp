#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

ll m,f;
int n;
vector<ll> V;

int main(void){
	scanf("%lld%lld",&m,&f);
	while(f){
		++n;
		V.push_back(f%m);
		f/=m;
	}
	printf("%d\n",n);
	for(reg int i=0;i<n;++i)
		printf("%lld%c",V[i],i==n-1?'\n':' ');
	return 0;
}
