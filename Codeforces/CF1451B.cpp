#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

const int MAXN=100+5;

char str[MAXN];

int main(void){
	int t;
	scanf("%d",&t);
	while(t--){
		int n,q;
		scanf("%d%d%s",&n,&q,str+1);
		while(q--){
			static int l,r;
			scanf("%d%d",&l,&r);
			reg bool f=false;
			for(reg int i=1;i<l&&!f;++i)
				f|=(str[i]==str[l]);
			for(reg int i=r+1;i<=n&&!f;++i)
				f|=(str[i]==str[r]);
			puts(f?"YES":"NO");
		}
	}
	return 0;
}