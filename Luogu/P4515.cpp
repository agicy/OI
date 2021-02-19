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

namespace geometry{
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
		Point s;
		Vector v;
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
	typedef vector<Point> poly;
	typedef vector<Line> set;
	inline poly HalfPlane(set S){
		sort(S.begin(),S.end());
		deque<Line> Q;
		Q.push_back(S.front());
		reg int n=S.size();
		for(reg int i=1;i<n;++i){
			while(Q.size()>=2&&S[i].isRight(getPoint(*(Q.end()-2),Q.back())))
				Q.pop_back();
			while(Q.size()>=2&&S[i].isRight(getPoint(Q.front(),*(Q.begin()+1))))
				Q.pop_front();
			if(Q.size()&&sgn(S[i].angle-Q.back().angle)!=0)
				Q.push_back(S[i]);
			else if(S[i].isRight(Q.back().s))
				Q.back()=S[i];
		}
		while(Q.size()>=2&&Q.front().isRight(getPoint(*(Q.end()-2),Q.back())))
			Q.pop_back();
		reg int m=Q.size();
		poly res;
		res.resize(m);
		for(reg int i=0;i<m;++i)
			res[i]=getPoint(Q[i],Q[(i+1)%m]);
		return res;
	}
	inline double getS(const poly& p){
		reg int n=p.size();
		reg double res=0;
		for(reg int i=0;i<n;++i)
			res+=cross(p[i],p[(i+1)%n]);
		return res*0.5;
	}
}

using namespace geometry;

const int MAXN=10;

int n;
int x[MAXN],y[MAXN],r[MAXN];

int main(void){
	n=read();
	for(reg int i=0;i<n;++i)
		x[i]=read(),y[i]=read(),r[i]=read();
	reg double ans=0;
	for(reg int S=1;S<(1<<n);++S){
		reg double k=-0.5;
		geometry::set V;
		for(reg int i=0;i<n;++i){
			if((S>>i)&1){
				k*=-2.0;
				V.push_back(Line(Point(x[i],y[i]),Point(x[i]+r[i],y[i])));
				V.push_back(Line(Point(x[i]+r[i],y[i]),Point(x[i],y[i]+r[i])));
				V.push_back(Line(Point(x[i],y[i]+r[i]),Point(x[i],y[i])));
			}
		}
		ans+=k*getS(HalfPlane(V));
	}
	printf("%.1lf\n",ans);
	return 0;
}