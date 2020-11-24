#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

int main(void){
	int t;
	scanf("%d",&t);
	while(t--){
		int n,m;
		scanf("%d%d",&n,&m);
		if(n<1ll*m*(m+1)/2)
			puts("impossible");
		else
			puts("possible");
	}
	return 0;
}