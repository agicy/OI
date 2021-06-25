#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
static char buf[1<<21],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch)) ch=getchar();
	while(isdigit(ch)) res=10*res+(ch^'0'),ch=getchar();
	return res;
}

inline int max(reg int a,reg int b){
	return a>b?a:b;
}

const int MAXN=1e5+5;

int n;
int cnt,head[MAXN],to[MAXN<<1],w[MAXN<<1],Next[MAXN<<1];

inline void Add_Edge(reg int u,reg int v,reg int len){
	Next[++cnt]=head[u];
	to[cnt]=v,w[cnt]=len;
	head[u]=cnt;
	return;
}

int dis[MAXN];

inline void dfs(reg int u,reg int father){
	for(reg int i=head[u];i;i=Next[i]){
		reg int v=to[i];
		if(v!=father){
			dis[v]=dis[u]^w[i];
			dfs(v,u);
		}
	}
	return;
}

const int MAXLOG2A=31;

namespace Trie{
	const int MAXSIZE=MAXN*50;
	struct Node{
		int ch[2];
		#define ch(x) unit[(x)].ch
	};
	int tot=1;
	Node unit[MAXSIZE];
	inline void insert(reg int val){
		reg int p=1;
		for(reg int i=MAXLOG2A-1;i>=0;--i){
			reg int c=(val>>i)&1;
			if(!ch(p)[c])
				ch(p)[c]=++tot;
			p=ch(p)[c];
		}
		return;
	}
	inline int query(reg int val){
		reg int res=0;
		reg int p=1;
		for(reg int i=MAXLOG2A-1;i>=0;--i){
			reg int c=(val>>i)&1;
			if(ch(p)[c^1]){
				res|=(1<<i);
				p=ch(p)[c^1];
			}
			else
				p=ch(p)[c];
		}
		return res;
	}
}

int main(void){
	n=read();
	for(reg int i=1;i<n;++i){
		static int u,v,w;
		u=read(),v=read(),w=read();
		Add_Edge(u,v,w),Add_Edge(v,u,w);
	}
	dfs(1,0);
	reg int ans=0;
	for(reg int i=1;i<=n;++i){
		ans=max(ans,Trie::query(dis[i]));
		Trie::insert(dis[i]);
	}
	printf("%d\n",ans);
	return 0;
}