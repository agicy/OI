#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

ll n;

int main(void){
	while(scanf("%lld",&n)!=EOF){
		reg ll row=ceil(0.5*(sqrt(1+8*n)-1));
		reg ll col=n-row*(row-1)/2;
		printf("%lld/%lld\n",row-col+1,col);
	}
	return 0;
}