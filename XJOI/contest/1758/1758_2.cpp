#pragma GCC optimize("Ofast")
#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
static char buf[1<<21],*p1=buf,*p2=buf;
inline int read(void){
	reg bool f=false;
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch)) f|=(ch=='-'),ch=getchar();
	while(isdigit(ch)) res=10*res+(ch^'0'),ch=getchar();
	return f?-res:res;
}

const int MAXN=1e3+5;
const int MAXD=10;
const long double eps=1e-9;

int n,d;

struct Vector{
	long double x[MAXD];
	inline Vector operator+(const Vector& a)const{
		Vector res;
		for(reg int i=0;i<d;++i)
			res.x[i]=x[i]+a.x[i];
		return res;
	}
	inline Vector operator-(const Vector& a)const{
		Vector res;
		for(reg int i=0;i<d;++i)
			res.x[i]=x[i]-a.x[i];
		return res;
	}
	inline Vector operator*(reg long double a)const{
		Vector res;
		for(reg int i=0;i<d;++i)
			res.x[i]=x[i]*a;
		return res;
	}
	inline Vector operator/(reg long double a)const{
		Vector res;
		for(reg int i=0;i<d;++i)
			res.x[i]=x[i]/a;
		return res;
	}
};

inline long double dot(const Vector& a,const Vector& b){
	reg long double res=0;
	for(reg int i=0;i<d;++i)
		res+=a.x[i]*b.x[i];
	return res;
}

typedef Vector Point;

Point p[MAXN];
Vector L;

inline void fix(Vector& L){
	reg long double val=sqrt(dot(L,L));
	L=L/val;
	return;
}

inline long double getDis(const Point& a,const Vector& v){
	Vector tmp=a-v*dot(a,v);
	return dot(tmp,tmp);
}

inline long double getVal(Vector& L){
	fix(L);
	reg long double res=0;
	for(reg int i=1;i<=n;++i)
		res+=getDis(p[i],L);
	return res;
}

inline int Rd() {return (rand()<<15)|rand();}
inline long double myrand() {return 1.0*Rd()/(1<<30)-0.5;}

long double ans=1e18;

inline void SA(void){
	for(reg int i=0;i<d;++i)
		L.x[i]=myrand();
	reg long double Min=getVal(L);
	const long double delta=0.985;
	for(reg long double T=1;T>eps;T*=delta){
		Vector tmp=L;
		for(reg int i=0;i<d;++i)
			tmp.x[i]+=myrand()*T;
		reg long double val=getVal(tmp);
		if(val<Min)
			Min=val,L=tmp;
	}
	if(Min<ans)
		ans=Min;
	return;
}

int main(void){
	srand(time(0));
	scanf("%d%d",&n,&d);
	for(reg int i=1;i<=n;++i)
		for(reg int j=0;j<d;++j)
			scanf("%Lf",&p[i].x[j]);
	SA();
	printf("%.10Lf\n",ans);
	return 0;
}