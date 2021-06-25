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

const int MAXN=250+5;
const int inf=0x3f3f3f3f;

struct Edge{
	int fr,to;
	inline Edge(reg int fr=0,reg int to=0):fr(fr),to(to){
		return;
	}
};

int n;
Point p[MAXN];
Edge e[MAXN*MAXN];
int f[MAXN];

inline bool cmp(const Edge& a,const Edge& b){
	return cross(p[a.to]-p[a.fr],p[b.to]-p[b.fr])>0;
}

int main(void){
	n=read();
	for(reg int i=1;i<=n;++i)
		p[i].x=read(),p[i].y=read();
	reg int tot=0;
	for(reg int i=1;i<=n;++i)
		for(reg int j=1;j<=n;++j)
			if(i!=j)
				e[++tot]=Edge(i,j);
	sort(e+1,e+tot+1,cmp);
	reg int ans=0;
	for(reg int i=1;i<=n;++i){
		fill(f+1,f+n+1,-inf);
		f[i]=0;
		for(reg int j=1;j<=tot;++j)
			f[e[j].to]=max(f[e[j].to],f[e[j].fr]+1);
		ans=max(ans,f[i]);
	}
	printf("%d\n",ans);
	return 0;
}