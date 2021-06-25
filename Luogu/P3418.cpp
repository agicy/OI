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

inline double max(reg double a,reg double b){
	return a>b?a:b;
}

inline double sqr(reg double x){
	return x*x;
}

const int MAXN=2.5e4+5;
const double eps=1e-10;
const double pi=acos(-1.0);

struct Vector{
	double x,y;
	inline Vector(reg double x=0,reg double y=0):x(x),y(y){
		return;
	}
	inline Vector operator+(const Vector& a)const{
		return Vector(x+a.x,y+a.y);
	}
	inline Vector operator-(const Vector& a)const{
		return Vector(x-a.x,y-a.y);
	}
	inline Vector operator/(reg double a)const{
		return Vector(x/a,y/a);
	}
	inline double len(void)const{
		return sqrt(sqr(x)+sqr(y));
	}
	inline bool operator==(const Vector& a)const{
		return fabs(x-a.x)<eps&&fabs(y-a.y)<eps;
	}
};

inline double dot(const Vector& a,const Vector& b){
	return 1ll*a.x*b.x+1ll*a.y*b.y;
}

inline double cross(const Vector& a,const Vector& b){
	return 1ll*a.x*b.y-1ll*a.y*b.x;
}

typedef Vector Point;

struct Node{
	double len,ang;
	inline bool operator==(const Node &a)const{
		return fabs(len-a.len)<eps&&fabs(ang-a.ang)<eps;
	}
	inline bool operator!=(const Node &a)const{
		return fabs(len-a.len)>eps||fabs(ang-a.ang)>eps;
	}
	inline bool operator<(const Node &a)const{
		return fabs(ang-a.ang)<eps?len<a.len:ang<a.ang;
	}
};

int n,m;
Point a[MAXN],b[MAXN];
Node f[MAXN],revf[MAXN],g[MAXN];

inline bool cmpd(const Node &a,const Node &b){
	return fabs(a.ang-b.ang)<eps?a.len<b.len:a.ang>b.ang;
}

inline bool check(reg Node *f,reg Node *g,reg int len){
	for(reg int delta=0;delta<len;++delta){
		reg bool flag=true;
		for(reg int i=1;i<=len;++i)
			if(f[i]!=g[(i+delta-1)%len+1]){
				flag=false;
				break;
			}
		if(flag)
			return true;
	}
	return false;
}

int main(void){
	n=read();
	Point suma(0,0);
	for(reg int i=1;i<=n;++i){
		a[i].x=read(),a[i].y=read();
		suma=suma+a[i];
	}
	suma=suma/n;
	reg int flag1=0;
	for(reg int i=1;i<=n;++i){
		a[i]=a[i+flag1]-suma;
		if(a[i]==Point(0,0))
			++flag1,--i,--n;
		else{
			f[i].len=sqrt(sqr(a[i].x)+sqr(a[i].y)),f[i].ang=acos(a[i].x/f[i].len);
			if(a[i].y<0)
				f[i].ang=2*pi-f[i].ang;
		}
	}
	reg double Maxl=0;
	for(reg int i=1;i<=n;++i)
		Maxl=max(Maxl,f[i].len);
	for(reg int i=1;i<=n;++i){
		f[i].len/=Maxl;
		revf[i]=f[i];
	}
	sort(f+1,f+n+1);
	sort(revf+1,revf+n+1,cmpd);
	reg double Maxa=f[n].ang;
	for(reg int i=n;i>=2;--i){
		f[i].ang-=f[i-1].ang;
		revf[n-i+2].ang=f[i].ang;
	}
	f[1].ang+=2*pi-Maxa;
	revf[1].ang=f[1].ang;
	reg int t=read();
	while(t--){
		m=read();
		Point sumb(0,0);
		for(reg int i=1;i<=m;++i){
			b[i].x=read(),b[i].y=read();
			sumb=sumb+b[i];
		}
		sumb=sumb/m;
		reg int flag2=0;
		for(reg int i=1;i<=m;++i){
			b[i]=b[i+flag2]-sumb;
			if(b[i]==Point(0,0))
				++flag2,--i,--m;
			else{
				g[i].len=sqrt(sqr(b[i].x)+sqr(b[i].y)),g[i].ang=acos(b[i].x/g[i].len);
				if(b[i].y<0)
					g[i].ang=2*pi-g[i].ang;
			}
		}
		if(m!=n)
			puts("NIE");
		else if(n==0)
			puts("TAK");
		else{
			reg double Maxl=0;
			for(reg int i=1;i<=m;++i)
				Maxl=max(Maxl,g[i].len);
			for(reg int i=1;i<=m;++i)
				g[i].len/=Maxl;
			sort(g+1,g+m+1);
			reg double Maxa=g[m].ang;
			for(reg int i=m;i>=2;--i)
				g[i].ang-=g[i-1].ang;
			g[1].ang+=2*pi-Maxa;
			reg bool f1=check(f,g,n),f2=check(revf,g,n);
			if((flag1==flag2)&&(f1||f2))
				puts("TAK");
			else
				puts("NIE");
		}
	}
	return 0;
}