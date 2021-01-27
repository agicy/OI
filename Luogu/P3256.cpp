#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define double long double
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return res;
}

const int MAXN=1e4+5;
const double inf=1e11;
const double eps=1e-10;

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
	int id;
	Point s,v;
	double angle;
	inline Line(void){}
	inline Line(reg int x,const Point& a,const Point& b){id=x,s=a,v=b-a,angle=atan2(v.y,v.x);}
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

int n;
int k[MAXN],v[MAXN];
Line l[MAXN];

int main(void){
	n=read();
	for(reg int i=1;i<=n;++i)
		k[i]=read();
	for(reg int i=1;i<=n;++i)
		v[i]=read();
	for(reg int i=1;i<=n;++i)
		l[i]=Line(i,Vector(0.0,k[i]),Vector(1.0,k[i]+v[i]));
	l[++n]=Line(0,Vector(-eps,inf),Vector(-eps,-eps));
	l[++n]=Line(0,Vector(inf,inf),Vector(-eps,inf));
	l[++n]=Line(0,Vector(inf,inf),Vector(-eps,inf));
	l[++n]=Line(0,Vector(-eps,inf),Vector(-eps,-eps));
	sort(l+1,l+n+1);
	reg int head=0,tail=0;
	static int Q[MAXN];
	Q[tail++]=1;
	for(reg int i=2;i<=n;++i){
		while(tail-head>=2&&l[i].isRight(getPoint(l[Q[tail-2]],l[Q[tail-1]])))
			--tail;
		while(tail-head>=2&&l[i].isRight(getPoint(l[Q[head]],l[Q[head+1]])))
			++head;
		if(head>=tail)
			Q[tail++]=i;
		else{
			if(sgn(l[i].angle-l[Q[tail-1]].angle)!=0)
				Q[tail++]=i;
			else{
				if(l[i].isRight(l[Q[tail-1]].s))
					Q[tail-1]=i;
				else
					Q[tail++]=i;
			}
		}
	}
	while(tail-head>2&&l[Q[head]].isRight(getPoint(l[Q[tail-2]],l[Q[tail-1]])))
		--tail;
	reg int tot=0;
	static int ans[MAXN];
	for(reg int i=head;i<tail;++i)
		if(l[Q[i]].id)
			ans[++tot]=l[Q[i]].id;
	sort(ans+1,ans+tot+1);
	printf("%d\n",tot);
	for(reg int i=1;i<=tot;++i)
		printf("%d%c",ans[i],i==tot?'\n':' ');
	return 0;
}