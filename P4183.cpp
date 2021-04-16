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

const int MAXN=7e4+5;
const int inf=0x3f3f3f3f;

int n;
int cnt,head[MAXN],to[MAXN<<1],Next[MAXN<<1];

inline void Add_Edge(reg int u,reg int v){
	Next[++cnt]=head[u];
	to[cnt]=v;
	head[u]=cnt;
	return;
}

int fa[MAXN],dep[MAXN];
int siz[MAXN],son[MAXN];

inline void dfs1(reg int u,reg int father){
	siz[u]=1;
	fa[u]=father;
	dep[u]=dep[father]+1;
	for(reg int i=head[u];i;i=Next[i]){
		reg int v=to[i];
		if(v!=father){
			dfs1(v,u);
			siz[u]+=siz[v];
			if(siz[son[u]]<siz[v])
				son[u]=v;
		}
	}
	return;
}

bool del[MAXN];
int siz[MAXN];
int rt,MaxPart,sum;

inline void getRt(reg int u,reg int father){
	siz[u]=1;
	reg int Max=0;
	for(reg int i=head[u];i;i=Next[i]){
		reg int v=to[i];
		if(v!=father&&!del[v]){
			getRt(v,u);
			siz[u]+=siz[v];
			Max=max(Max,siz[v]);
		}
	}
	Max=max(Max,sum-siz[u]);
	if(Max<MaxPart)
		rt=u,MaxPart=Max;
	return;
}

inline void calc(reg int u){

	return;
}

inline void solve(reg int u){
	del[u]=true;
	calc(u);
	for(reg int i=head[u];i;i=Next[i]){
		reg int v=to[i];
		if(!del[v]){
			rt=0,MaxPart=inf,sum=siz[v];
			getRt(v,0),solve(rt);
		}
	}
	return;
}

int main(void){
	n=read();
	for(reg int i=1;i<=n;++i){
		static int u,v;
		u=read(),v=read();
		Add_Edge(u,v),Add_Edge(v,u);
	}
	rt=0,MaxPart=inf,sum=n;
	getRt(1,0),solve(rt);
	return 0;
}