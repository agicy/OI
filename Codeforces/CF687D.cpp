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

const int MAXN=1e3+5;
const int MAXM=MAXN*(MAXN-1)/2;
const int MAXQ=1e3+5;

struct Edge{
	int id,u,v,w;
	inline bool operator<(const Edge& a)const{
		return w>a.w;
	}
};

namespace UnionFind{
	int fa[MAXN<<1];
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
	inline void merge(reg int a,reg int b){
		reg int ra=find(a),rb=find(b);
		fa[rb]=ra;
		return;
	}
	inline bool search(reg int a,reg int b){
		return find(a)==find(b);
	}
}

int n,m,q;
Edge e[MAXM];

int main(void){
	n=read(),m=read(),q=read();
	for(reg int i=1;i<=m;++i)
		e[i].id=i,e[i].u=read(),e[i].v=read(),e[i].w=read();
	sort(e+1,e+m+1);
	while(q--){
		static int l,r;
		l=read(),r=read();
		UnionFind::Init(n<<1);
		reg int ans=-1;
		for(reg int i=1;i<=m;++i)
			if(l<=e[i].id&&e[i].id<=r){
				if(UnionFind::search(e[i].u,e[i].v)){
					ans=e[i].w;
					break;
				}
				else
					UnionFind::merge(e[i].u,e[i].v+n),UnionFind::merge(e[i].v,e[i].u+n);
			}
		printf("%d\n",ans);
	}
	return 0;
}