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

const int MAXN=10+5;
const int MAXM=50+5;
const int MAXV=MAXN*MAXM;
const double eps=1e-8;

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
		return Vector(a*x,a*y);
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
	Point x,y;
	double angle;
	inline Line(void){}
	inline Line(const Point& x,const Point& y):x(x),y(y){angle=atan2(y.y-x.y,y.x-x.x);}
	inline bool operator<(const Line& a)const{
		return angle<a.angle||(sgn(angle-a.angle)==0&&sgn(cross(y-a.x,a.y-x))>0);
	}
};

inline Point getPoint(const Line& a,const Line& b){
	return b.x+(b.y-b.x)*(cross(b.x-a.x,a.y-a.x)/cross(a.y-a.x,b.y-b.x));
}

inline bool check(const Line& i,const Line& j,const Line& k){
	return sgn(cross(k.y-k.x,getPoint(i,j)-k.x))<0;
}

int n;
Point p[MAXV];
Line l[MAXV];
int tot;

inline double getS(void){
	sort(l+1,l+tot+1);
	reg int cnt=0;
	for(reg int i=1;i<=tot;++i){
		if(sgn(l[i].angle-l[i-1].angle))
			++cnt;
		l[cnt]=l[i];
	}
	reg int head=0,tail=0;
	static int Q[MAXV];
	Q[tail++]=1,Q[tail++]=2;
	for(reg int i=3;i<=cnt;++i){
		while(tail-head>=2&&check(l[Q[tail-2]],l[Q[tail-1]],l[i]))
			--tail;
		while(tail-head>=2&&check(l[Q[head+1]],l[Q[head]],l[i]))
			++head;
		Q[tail++]=i;
	}
	while(tail-head>=2&&check(l[Q[tail-2]],l[Q[tail-1]],l[Q[head]]))
		--tail;
	while(tail-head>=2&&check(l[Q[head+1]],l[Q[head]],l[Q[tail-1]]))
		++head;
	Q[tail]=Q[head];
	tot=0;
	for(reg int i=head;i<tail;++i)
		p[++tot]=getPoint(l[Q[i]],l[Q[i+1]]);
	p[tot+1]=p[1];
	reg double sum=0;
	for(reg int i=1;i<=tot;++i)
		sum+=cross(p[i],p[i+1]);
	return 0.5*fabs(sum);
}

int main(void){
	n=read();
	for(reg int i=1;i<=n;++i){
		static int m;
		m=read();
		for(reg int j=1;j<=m;++j)
			p[j].x=read(),p[j].y=read();
		p[m+1]=p[1];
		for(reg int j=1;j<=m;++j)
			l[++tot]=Line(p[j],p[j+1]);
	}
	reg double ans=getS();
	printf("%.3lf\n",ans);
	return 0;
}