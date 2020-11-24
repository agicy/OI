#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

const int MAXN=1e6+5;
const int MAXS=1e6+5;

char s[MAXN];
int n,m;
int sa[MAXN],rk[MAXN<<1],oldrk[MAXN<<1],id[MAXN];
int cnt[MAXS];

inline void build(void){
	reg int m=max(n,300);
	for(reg int i=1;i<=n;++i)
		++cnt[rk[i]=s[i]];
	for(reg int i=1;i<=m;++i)
		cnt[i]+=cnt[i-1];
	for(reg int i=n;i>=1;--i)
		sa[cnt[rk[i]]--]=i;
	for(reg int w=1;w<n;w<<=1){
		memset(cnt,0,sizeof(cnt));
		for(reg int i=1;i<=n;++i)
			id[i]=sa[i];
		for(reg int i=1;i<=n;++i)
			++cnt[rk[id[i]+w]];
		for(reg int i=1;i<=m;++i)
			cnt[i]+=cnt[i-1];
		for(reg int i=n;i>=1;--i)
			sa[cnt[rk[id[i]+w]]--]=id[i];
		memset(cnt,0,sizeof(cnt));
		for(reg int i=1;i<=n;++i)
			id[i]=sa[i];
		for(reg int i=1;i<=n;++i)
			++cnt[rk[id[i]]];
		for(reg int i=1;i<=m;++i)
			cnt[i]+=cnt[i-1];
		for(reg int i=n;i>=1;--i)
			sa[cnt[rk[id[i]]]--]=id[i];
		memcpy(oldrk,rk,sizeof(rk));
		reg int p=0;
		for(reg int i=1;i<=n;++i)
			if(oldrk[sa[i]]==oldrk[sa[i-1]]&&oldrk[sa[i]+w]==oldrk[sa[i-1]+w])
				rk[sa[i]]=p;
			else
				rk[sa[i]]=++p;
	}
	return;
}

int main(void){
	scanf("%s",s+1);
	n=strlen(s+1);
	build();
	for (reg int i=1;i<=n;++i)
		printf("%d%c",sa[i],i==n?'\n':' ');
	return 0;
}