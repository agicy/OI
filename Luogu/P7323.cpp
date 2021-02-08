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

const int MAXN=3e5+5;

namespace UnionFind{
	int fa[MAXN];
	inline void Init(reg int n){
		for(reg int i=1;i<=n;++i)
			fa[i]=i;
		return;
	}
	inline int find(reg int x){
		if(x==fa[x])
			return x;
		else
			return fa[x]=find(fa[x]);
	}
}

int n,m,k;
int siz[MAXN];
queue<pair<int,int>/**/> Q;
map<int,int> M[MAXN];

int main(void){
	n=read(),m=read(),k=read();
	UnionFind::Init(n);
	for(reg int i=1;i<=m;++i){
		static int u,v,w;
		u=read(),v=read(),w=read();
		if(M[v][w])
			Q.push(make_pair(u,M[v][w]));
		else
			M[v][w]=u;
	}
	while(!Q.empty()){
		static pair<int,int> p;
		static int x,y,w;
		p=Q.front();
		Q.pop();
		x=p.first,y=p.second;
		x=UnionFind::find(x),y=UnionFind::find(y);
		if(x==y)
			continue;
		if(x==y)
			continue;
		if(M[x].size()<M[y].size())
			swap(x,y);
		UnionFind::fa[y]=x;
		for(map<int,int>::iterator it=M[y].begin();it!=M[y].end()&&(w=it->first,true);++it)
			if(M[x][w])
				Q.push(make_pair(it->second,M[x][w]));
			else
				M[x][w]=it->second;
		M[y].clear();
	}
	for(reg int i=1;i<=n;++i)
		++siz[UnionFind::find(i)];
	reg ll ans=0;
	for(reg int i=1;i<=n;++i)
		ans+=(1ll*siz[i]*(siz[i]-1))>>1;
	printf("%lld\n",ans);
	return 0;
}