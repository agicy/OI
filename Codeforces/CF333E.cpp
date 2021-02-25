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
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return f?-res:res;
}

const int MAXN=3e3+5;

struct Edge{
	int u,v;
	double w;
	inline Edge(reg int u=0,reg int v=0,reg double w=0):u(u),v(v),w(w){
		return;
	}
	inline bool operator<(const Edge& a)const{
		return w>a.w;
	}
};

struct Point{
	int x,y;
};

inline int sqr(reg int x){
	return x*x;
}

inline double getDis(const Point& a,const Point& b){
	return sqrt(sqr(a.x-b.x)+sqr(a.y-b.y));
}

int n;
Edge E[MAXN*MAXN];
Point p[MAXN];
bitset<MAXN> q[MAXN];

int main(void){
	n=read();
	for(reg int i=1;i<=n;++i)
		p[i].x=read(),p[i].y=read();
	reg int tot=0;
	for(reg int i=1;i<=n;++i)
		for(reg int j=1;j<i;++j)
			E[++tot]=Edge(i,j,getDis(p[i],p[j]));
	sort(E+1,E+tot+1);
	for(reg int i=1;i<=tot;++i){
		if((q[E[i].u]&q[E[i].v]).count()){
			printf("%.20lf\n",0.5*E[i].w);
			return 0;
		}
		q[E[i].u].set(E[i].v),q[E[i].v].set(E[i].u);
	}
	return 0;
}