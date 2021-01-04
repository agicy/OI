#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return res;
}

const int MAXN=2e5+5;
const int inf=1<<30;

int n;
int a[MAXN];

namespace Trie{
	const int MAXS=MAXN*32;
	struct Node{
		int ch[2];
		#define ch(x) unit[(x)].ch
	};
	int tot;
	Node unit[MAXS];
	int L[MAXS],R[MAXS];
	inline void insert(reg int &k,reg int id,reg int dep){
		if(!k)
			k=++tot;
		if(!L[k])
			L[k]=id;
		R[k]=id;
		if(dep==-1)
			return;
		insert(ch(k)[(a[id]>>dep)&1],id,dep-1);
		return;
	}
	inline ll query(reg int k,reg int val,reg int dep){
		if(dep==-1)
			return 0;
		reg int c=(val>>dep)&1;
		if(ch(k)[c])
			return query(ch(k)[c],val,dep-1);
		else
			return query(ch(k)[c^1],val,dep-1)|(1<<dep);
	}
	inline ll dfs(reg int k,reg int dep){
		if(dep==-1)
			return 0;
		if(ch(k)[0]&&ch(k)[1]){
			ll ans=inf;
			for(reg int i=L[ch(k)[0]];i<=R[ch(k)[0]];++i)
				ans=min(ans,query(ch(k)[1],a[i],dep-1)|(1<<dep));
			return dfs(ch(k)[0],dep-1)+dfs(ch(k)[1],dep-1)+ans;
		}
		else if(ch(k)[0])
			return dfs(ch(k)[0],dep-1);
		else if(ch(k)[1])
			return dfs(ch(k)[1],dep-1);
		else
			return 0;
	}
}

int main(void){
	n=read();
	for(reg int i=1;i<=n;++i)
		a[i]=read();
	sort(a+1,a+n+1);
	int rt=0;
	for(reg int i=1;i<=n;++i)
		Trie::insert(rt,i,30);
	printf("%lld\n",Trie::dfs(rt,30));
	return 0;
}