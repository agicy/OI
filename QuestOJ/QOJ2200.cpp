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

struct FengHuo{
	Point p;
};

struct Shan{
	Point p;
	int r;
};

inline int sqr(reg int x){
	return x*x;
}

inline double getDis(const Point& a,const Point& b){
	return sqrt(sqr(a.x-b.x)+sqr(a.y-b.y));
}

struct Event{
	double angle,dis;
	int opt,id;
	inline Event(reg double angle=0,reg double dis=0,reg int opt=0,reg int id=0):angle(angle),dis(dis),opt(opt),id(id){
		return;
	}
	inline bool operator<(const Event& a)const{
		return angle<a.angle;
	}
};

const int MAXN=1e3+5;
const int MAXM=1e3+5;
const double pi=acos(-1.0);
const double cir=2.0*pi;

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
		fa[rb]=ra;
		return;
	}
	inline bool search(reg int a,reg int b){
		return find(a)==find(b);
	}
}

int n,m;
FengHuo a[MAXN];
Shan b[MAXM];
bool vis[MAXN];
Event E[(MAXN+MAXM*2)*2];
set<pair<double,int>/**/> S;

int main(void){
	n=read(),m=read();
	UnionFind::Init(n);
	for(reg int i=1;i<=n;++i)
		a[i].p.x=read(),a[i].p.y=read();
	for(reg int i=1;i<=m;++i)
		b[i].p.x=read(),b[i].p.y=read(),b[i].r=read();
	for(reg int i=1,j,tot;i<=n;++i){
		tot=0;
		for(j=i+1;j<=n;++j)
			if(!UnionFind::search(i,j)){
				vis[j]=true;
				E[++tot]=Event(atan2(a[j].p.y-a[i].p.y,a[j].p.x-a[i].p.x),getDis(a[i].p,a[j].p),1,j);
			}
			else
				vis[j]=false;
		double len,val_cos,delta,angle,angle_in,angle_out,dis;
		Vector v;
		for(j=1;j<=m;++j){
			v=b[j].p-a[i].p;
			len=getDis(a[i].p,b[j].p);
			val_cos=sqrt(dot(v,v)-b[j].r*b[j].r)/len;
			delta=acos(val_cos),angle=atan2(v.y,v.x);
			angle_in=angle-delta,angle_out=angle+delta;
			dis=len-b[j].r;
			if(angle_in<-pi)
				angle_in+=cir;
			if(angle_out>pi)
				angle_out-=cir;
			E[++tot]=Event(angle_in,dis,2,j);
			E[++tot]=Event(angle_out,dis,3,j);
		}
		sort(E+1,E+tot+1);
		for(j=1;j<=tot;++j)
			E[j+tot]=E[j];
		S.clear();
		for(j=1;j<=tot*2;++j)
			switch(E[j].opt){
				case 1:{
					if(vis[E[j].id]){
						for(auto x:S)
							if(dot(a[i].p-a[E[j].id].p,b[x.second].p-a[E[j].id].p)>0){
								vis[E[j].id]=false;
								break;
							}
							else if(x.first>E[j].dis)
								break;
					}
					break;
				}
				case 2:{
					S.insert(make_pair(E[j].dis,E[j].id));
					break;
				}
				case 3:{
					S.erase(make_pair(E[j].dis,E[j].id));
					break;
				}
			}
		for(j=i+1;j<=n;++j)
			if(vis[j])
				UnionFind::merge(i,j);
	}
	reg int ans=0;
	for(reg int i=1;i<=n;++i)
		if(i==UnionFind::find(i))
			++ans;
	printf("%d\n",ans-1);
	return 0;
}