#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

bool st;

#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
static char buf[1<<21],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch)) ch=getchar();
	while(isdigit(ch)) res=10*res+(ch^'0'),ch=getchar();
	return res;
}

const int MAXN=2e5+5;
const int MAXM=5e5+5;

struct UnionFind{
	int *fa;
	inline UnionFind(const int& N){
		fa=new int[N];
		for(reg int i=0;i<N;++i)
			fa[i]=i;
		return;
	}
	inline ~UnionFind(void){
		delete[] fa;
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
		if(ra!=rb)
			fa[rb]=ra;
		return;
	}
	inline bool search(reg int a,reg int b){
		return find(a)==find(b);
	}
};

struct Edge{
	int u,v,w;
	inline Edge(void){return;};
	inline Edge(const int& u,const int& v,const int& w):u(u),v(v),w(w){return;}
	inline bool operator<(const Edge& a)const{return w<a.w;}
};

int n,m;
Edge e[MAXM];

bool ed;

int main(void){
	n=read(),m=read();
	for(reg int i=0;i<m;++i){
		static int u,v,w;
		u=read()-1,v=read()-1,w=read();
		e[i]=Edge(u,v,w);
	}
	UnionFind U(n);
	sort(e,e+m);
	reg ll ans=0;
	for(reg int i=0,cnt=0;i<m&&cnt<n-1;++i)
		if(!U.search(e[i].u,e[i].v)){
			++cnt;
			ans+=e[i].w;
			U.merge(e[i].u,e[i].v);
		}
	printf("%lld\n",ans);
	fprintf(stderr,"%.3lf s\n",1.0*clock()/CLOCKS_PER_SEC);
	fprintf(stderr,"%.3f MiB\n",(&ed-&st)/1048576.0);
	return 0;
}