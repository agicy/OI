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

const int MAXN=1e5+5;
const double inf=1e11;
const double eps=1e-11;

inline int sgn(reg double x){
	if(fabs(x)<eps)
		return 0;
	else
		return x<0?-1:1;
}

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
	inline Vector operator*(reg double a)const{
		return Vector(x*a,y*a);
	}
};

inline double dot(const Vector& a,const Vector& b){
	return a.x*b.x+a.y*b.y;
}

inline double cross(const Vector& a,const Vector& b){
	return a.x*b.y-a.y*b.x;
}

typedef Vector Point;

struct Line{
	Point s,v;
	double angle;
	inline Line(void){}
	inline Line(const Point& a,const Point& b){s=a,v=b-a,angle=atan2(v.y,v.x);}
	inline bool operator<(const Line& a)const{
		return angle<a.angle;
	}
	inline bool isRight(const Point& x){
		return sgn(cross(v,x-s))<0;
	}
};

inline Point getPoint(const Line& a,const Line& b){
	return a.s+a.v*(cross(b.v,b.s-a.s)/cross(b.v,a.v));
}

struct Data{
	int id;
	Line l;
	inline bool operator<(const Data& a)const{
		return l<a.l;
	}
};

int n;
int tot;
Data a[MAXN<<1];
Line l[MAXN<<1];

inline bool check(reg int mid){
	reg int cnt=0;
	for(reg int i=1;i<=tot;++i)
		if(a[i].id<=mid)
			l[++cnt]=a[i].l;
	reg int head=0,tail=0;
	static int Q[MAXN<<1];
	Q[tail++]=1;
	for(reg int i=2;i<=cnt;++i){
		while(tail-head>=2&&l[i].isRight(getPoint(l[Q[tail-2]],l[Q[tail-1]])))
			--tail;
		while(tail-head>=2&&l[i].isRight(getPoint(l[Q[head]],l[Q[head+1]])))
			++head;
		if(head<tail&&sgn(l[i].angle-l[Q[tail-1]].angle)!=0)
			Q[tail++]=i;
		else if(l[i].isRight(l[Q[tail-1]].s))
			Q[tail-1]=i;
	}
	while(tail-head>2&&l[Q[head]].isRight(getPoint(l[Q[tail-2]],l[Q[tail-1]])))
		--tail;
	return tail-head>2;
}

int main(void){
	n=read();
	for(reg int i=1;i<=n;++i){
		static double x,y1,y2;
		x=read(),y1=read(),y2=read();
		++tot;
		a[tot].id=i,a[tot].l=Line(Point(0.0,1.0*y1/x),Point(1.0,1.0*y1/x-x));
		++tot;
		a[tot].id=i,a[tot].l=Line(Point(1.0,1.0*y2/x-x),Point(0.0,1.0*y2/x));
	}
	++tot;
	a[tot].id=0,a[tot].l=Line(Point(-inf,eps),Point(-eps,eps));
	++tot;
	a[tot].id=0,a[tot].l=Line(Point(-eps,eps),Point(-eps,inf));
	++tot;
	a[tot].id=0,a[tot].l=Line(Point(-eps,inf),Point(-inf,inf));
	++tot;
	a[tot].id=0,a[tot].l=Line(Point(-inf,inf),Point(-inf,eps));
	sort(a+1,a+tot+1);
	reg int l=1,r=n,mid;
	while(l<r){
		mid=(l+r)>>1;
		if(check(mid+1))
			l=mid+1;
		else
			r=mid;
	}
	printf("%d\n",l);
	return 0;
}