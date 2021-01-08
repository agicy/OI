#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

const int MAXS=5e4+5;

namespace SA{
	const int MAXN=MAXS;
	int sa[MAXN],rk[MAXN],oldrk[MAXN<<1],id[MAXN],px[MAXN],cnt[MAXN];
	int ht[MAXN];
	inline bool cmp(reg int a,reg int b,reg int w){
		return oldrk[a]==oldrk[b]&&oldrk[a+w]==oldrk[b+w];
	}
	inline void build(reg char s[],reg int n){
		memset(cnt,0,sizeof(cnt));
		int m=300;
		for(reg int i=1;i<=n;++i)
			++cnt[rk[i]=s[i]];
		for(reg int i=1;i<=m;++i)
			cnt[i]+=cnt[i-1];
		for(reg int i=n;i>=1;--i)
			sa[cnt[rk[i]]--]=i;
		for(reg int w=1,p,i;w<n;w<<=1,m=p){
			for(p=0,i=n;i>n-w;--i)
				id[++p]=i;
			for(i=1;i<=n;++i)
				if(sa[i]>w)
					id[++p]=sa[i]-w;
			memset(cnt,0,sizeof(cnt));
			for(i=1;i<=n;++i)
				++cnt[px[i]=rk[id[i]]];
			for(i=1;i<=m;++i)
				cnt[i]+=cnt[i-1];
			for(i=n;i>=1;--i)
				sa[cnt[px[i]]--]=id[i];
			memcpy(oldrk,rk,sizeof(rk));
			for(p=0,i=1;i<=n;++i)
				rk[sa[i]]=cmp(sa[i],sa[i-1],w)?p:++p;
		}
		for(reg int i=1,k=0;i<=n;++i){
			if(k)
				--k;
			while(s[i+k]==s[sa[rk[i]-1]+k])
				++k;
			ht[rk[i]]=k;
		}
		return;
	}
}

char s[MAXS];

int main(void){
	int T;
	scanf("%d",&T);
	while(T--){
		scanf("%s",s+1);
		reg int n=strlen(s+1);
		SA::build(s,n);
		reg ll ans=1ll*n*(n+1)/2;
		for(reg int i=1;i<=n;++i)
			ans-=SA::ht[i];
		printf("%lld\n",ans);
	}
	return 0;
}