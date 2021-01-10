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
const int MAXA=4e5+5;

namespace UnionFind{
	int fa[MAXA];
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

int n;
bool vis[MAXA];

int main(void){
	n=read();
	reg int ans=0;
	UnionFind::Init(4e5);
	for(reg int i=1;i<=n;++i){
		static int a,b;
		a=read(),b=read();
		reg int u=UnionFind::find(a),v=UnionFind::find(b);
		if(u!=v&&(!vis[u]||!vis[v])){
			UnionFind::fa[v]=u;
			vis[u]|=vis[v];
			++ans;
		}
		else if(!vis[u])
			vis[u]=true,++ans;
	}
	printf("%d\n",ans);
	return 0;
}