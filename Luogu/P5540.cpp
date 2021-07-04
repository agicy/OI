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

struct Vector{
	int x,y;
	inline Vector(reg int x=0,reg int y=0):x(x),y(y){
		return;
	}
	inline Vector operator+(const Vector& a)const{
		return Vector(x+a.x,y+a.y);
	}
	inline Vector operator-(const Vector& a)const{
		return Vector(x-a.x,y-a.y);
	}
};

inline int dot(const Vector& a,const Vector& b){
	return a.x*b.x+a.y*b.y;
}

inline int cross(const Vector& a,const Vector& b){
	return a.x*b.y-a.y*b.x;
}

typedef Vector Point;

const int MAXN=200;
const int MAXM=1e4;
const int inf=0x3f3f3f3f;

struct Edge{
	int u,v,w,a,b;
	inline bool operator<(const Edge& a)const{
		return w<a.w;
	}
};

namespace UnionFind{
	int fa[MAXN];
	inline void init(reg int n){
		for(reg int i=0;i<n;++i)
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

int n,m;
Point ans(inf,inf);
Edge e[MAXM];

inline Point kruskal(void){
	Point res(0,0);
	sort(e,e+m);
	UnionFind::init(n);
	reg int tot=0;
	for(reg int i=0;i<m&&tot<n-1;++i)
		if(!UnionFind::search(e[i].u,e[i].v)){
			++tot;
			res.x+=e[i].a,res.y+=e[i].b;
			UnionFind::merge(e[i].u,e[i].v);
		}
	reg ll Min=1ll*ans.x*ans.y,tmp=1ll*res.x*res.y;
	if(Min>tmp||(Min==tmp&&ans.x>res.x))
		ans=res;
	return res;
}

inline void solve(const Point& a,const Point& b){
	for(reg int i=0;i<m;++i)
		e[i].w=e[i].b*(b.x-a.x)+e[i].a*(a.y-b.y);
	Point c=kruskal();
	if(cross(b-a,c-a)<0)
		solve(a,c),solve(c,b);
	return;
}

bool ed;

int main(void){
	n=read(),m=read();
	for(reg int i=0;i<m;++i)
		e[i].u=read(),e[i].v=read(),e[i].a=read(),e[i].b=read();
	for(reg int i=0;i<m;++i)
		e[i].w=e[i].a;
	Point a=kruskal();
	for(reg int i=0;i<m;++i)
		e[i].w=e[i].b;
	Point b=kruskal();
	solve(a,b);
	printf("%d %d\n",ans.x,ans.y);
	fprintf(stderr,"%.3lf s\n",1.0*clock()/CLOCKS_PER_SEC);
	fprintf(stderr,"%.3lf MiB\n",(&ed-&st)/1048576.0);
	return 0;
}