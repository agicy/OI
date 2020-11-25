#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg bool f=false;
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))f|=(ch=='-'),ch=getchar();
	while(isdigit(ch))res=10*res+ch-'0',ch=getchar();
	return f?-res:res;
}

const int MAXN=1e4+5;
const int MAXM=5e4+5;

struct Point{
	int x,y;
	inline Point(reg int x=0,reg int y=0):x(x),y(y){
		return;
	}
};

inline double sqr(reg double x){
	return x*x;
}

inline double getDis(const Point& a,const Point& b){
	return sqrt(sqr(a.x-b.x)+sqr(a.y-b.y));
}

int n,m;
Point p[MAXN];

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
	inline void merge(reg int a,reg int b){
		reg int ra=find(a),rb=find(b);
		if(ra!=rb)
			fa[rb]=ra;
		return;
	}
	inline bool search(reg int a,reg int b){
		return find(a)==find(b);
	}
}

struct Edge{
	int u,v;
	double val;
	inline Edge(reg int u=0,reg int v=0,reg double val=0):u(u),v(v),val(val){
		return;
	}
	inline bool operator<(const Edge& a)const{
		return val<a.val;
	}
};

Edge E[MAXM];

int main(void){
	n=read(),m=read();
	for(reg int i=1;i<=n;++i)
		p[i].x=read(),p[i].y=read();
	reg double sum=0;
	for(reg int i=1;i<=m;++i){
		static int u,v;
		u=read(),v=read();
		reg double val=getDis(p[u],p[v]);
		E[i]=Edge(u,v,val);
		sum+=val;
	}
	sort(E+1,E+m+1);
	UnionFind::Init(n);
	for(reg int i=m;i>=1;--i)
		if(!UnionFind::search(E[i].u,E[i].v)){
			UnionFind::merge(E[i].u,E[i].v);
			sum-=E[i].val;
		}
	printf("%.9lf\n",sum);
	return 0;
}