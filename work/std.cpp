#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

const int MAXN=5e4+5;
const int MAXQ=5e4+5;

int n,q;
int a[MAXN],b[MAXN];
int opt[MAXQ],x[MAXQ],y[MAXQ];

const int mod=1e9+7;

inline int getVal(void){
	static int c[MAXN];
	c[0]=0;
	for(reg int i=1;i<=n;++i)
		c[i]=max(c[i-1],a[i]);
	reg int ans=1;
	for(reg int i=1;i<=n;++i)
		ans=1ll*ans*min(b[i],c[i])%mod;
	return ans;
}

int main(void){
	scanf("%d%d",&n,&q);
	for(reg int i=1;i<=n;++i)
		scanf("%d",&a[i]);
	for(reg int i=1;i<=n;++i)
		scanf("%d",&b[i]);
	for(reg int i=1;i<=q;++i){
		scanf("%d%d%d",&opt[i],&x[i],&y[i]);
		if(opt[i]==0)
			a[x[i]]=y[i];
		else
			b[x[i]]=y[i];
		printf("%d\n",getVal());
	}
	return 0;
}