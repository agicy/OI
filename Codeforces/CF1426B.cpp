#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

int n,m;

int main(void){
	int t;
	scanf("%d",&t);
	while(t--){
		scanf("%d%d",&n,&m);
		reg bool f=false;
		for(reg int i=1;i<=n;++i){
			static int a,b;
			scanf("%*d%d%d%*d",&a,&b);
			f|=(a==b);
		}
		if((m&1)||!f)
			puts("NO");
		else
			puts("YES");
	}
	return 0;
}