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

const int MAXN=5e5+5;
const double R=1.42e6;
const double eps=1e-6;

inline int sgn(reg double x){
	if(fabs(x)<eps)
		return 0;
	else
		return x<0?-1:1;
}

struct Vector{
	ll x,y;
	inline Vector(reg ll x=0,reg ll y=0):x(x),y(y){
		return;
	}
	inline Vector operator+(const Vector& a){
		return Vector(x+a.x,y+a.y);
	}
	inline Vector operator-(const Vector& a){
		return Vector(x-a.x,y-a.y);
	}
	inline double getLen(void){
		return sqrt(1.0*x*x+1.0*y*y);
	}
	inline void print(void){
		printf("(%lld,%lld)\n",x,y);
		return;
	}
};

inline double cross(const Vector& a,const Vector& b){
	return 1.0*a.x*b.y-1.0*a.y*b.x;
}

inline double dot(const Vector& a,const Vector& b){
	return 1.0*a.x*b.x+1.0*a.y*b.y;
}

int n;
Vector V[MAXN];
int ans[MAXN];

namespace Subtask2{

	const double pi=acos(-1.0);
	const double Ang=pi/20.0;
	const double inf=1e20;

	struct Node{
		int id;
		double ang,len;
		inline bool operator<(const Node& a)const{
			return ang<a.ang;
		}
		inline Node(reg int id=0,reg double ang=0,reg double len=0):id(id),ang(ang),len(len){
			return;
		}
	};

	Node v[MAXN];

	double f[MAXN][2];
	int from[MAXN][2];

	Vector COMB[21];

	int block_id[MAXN];

	int c[MAXN];

	inline void solve(reg int id,reg int l,reg int r){
		for(reg int j=l;j<=r;++j)
			block_id[v[j].id]=id;
		f[l][0]=v[l].len,f[l][1]=-v[l].len;
		from[l][0]=+1,from[l][1]=-1;
		for(reg int i=l+1;i<=r;++i){
			reg double x=v[i].len;
			for(reg int fr=1;fr<=2;++fr){
				if(f[i][0]<f[i-1][fr-1]+x){
					f[i][0]=f[i-1][fr-1]+x;
					from[i][0]=+fr;
				}
				if(f[i][1]>f[i-1][fr-1]+x){
					f[i][1]=f[i-1][fr-1]+x;
					from[i][1]=+fr;
				}
				if(f[i][0]<f[i-1][fr-1]-x){
					f[i][0]=f[i-1][fr-1]-x;
					from[i][0]=-fr;
				}
				if(f[i][1]>f[i-1][fr-1]-x){
					f[i][1]=f[i-1][fr-1]-x;
					from[i][1]=-fr;
				}
			}
		}
		reg int ptr;
		if(fabs(f[r][0])<fabs(f[r][1]))
			ptr=0;
		else
			ptr=1;
		for(reg int i=r;i>=l;--i){
			reg int sign=sgn(from[i][ptr]);
			if(sign)
				c[v[i].id]*=-1;
			if(c[v[i].id]==1)
				COMB[id]=COMB[id]+V[v[i].id];
			else if(c[v[i].id]==-1)
				COMB[id]=COMB[id]-V[v[i].id];
			ptr=abs(from[i][ptr])-1;
		}
		return;
	}
	inline void Solve(void){
		for(reg int i=1;i<=n;++i)
			f[i][0]=-inf,f[i][1]=+inf;
		for(reg int i=1;i<=n;++i)
			c[i]=1;
		for(reg int i=1;i<=n;++i){
			reg double ang=atan2(V[i].y,V[i].x);
			if(ang<0)
				ang+=pi,c[i]*=-1;
			v[i]=Node(i,ang,V[i].getLen());
		}
		sort(v+1,v+n+1);
		v[n+1].ang=inf;
		for(reg int i=0,l=1,r;i<20;++i,l=r+1){
			reg double L=i*Ang,R=(i+1)*Ang;
			while(l<=n&&sgn(v[l].ang-L)<0)
				++l;
			r=l-1;
			while(r<=n&&sgn(v[r+1].ang-R)<=0)
				++r;
			if(l<=r)
				solve(i,l,r);
		}
		reg int U=(1<<20)-1;
		for(reg int S=0;S<=U;++S){
			Vector res(0,0);
			for(reg int i=0;i<20;++i)
				if((S>>i)&1)
					res=res-COMB[i];
				else
					res=res+COMB[i];
			if(res.getLen()<R){
				for(reg int i=1;i<=n;++i){
					reg int inter=c[i];
					reg int out=((S>>block_id[i])&1)?-1:1;
					ans[i]=inter*out;
				}
				break;
			}
		}
		return;
	}
}

int main(void){
	n=read();
	for(reg int i=1;i<=n;++i){
		static int a,b;
		a=read(),b=read();
		V[i]=Vector(a,b);
	}
	Subtask2::Solve();
	for(reg int i=1;i<=n;++i)
		printf("%d\n",ans[i]);
	return 0;
}