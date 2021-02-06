#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar()(p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg bool f=false;
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))f|=(ch=='-'),ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return f?-res:res;
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
		return res;
	}
}

using geometry::Line;
using geometry::Point;
using geometry::sgn;

int main(void){
	reg int n=read();
	geometry::poly p;
	p.resize(n);
	for(reg int i=0;i<n;++i){
		static int x,y;
		x=read(),y=read();
		p[i]=Point(x,y);
	}
	geometry::set S;
	for(reg int i=0;i<n;++i)
		S.push_back(Line(p[i],p[(i+1)%n]));
	for(reg int i=1;i<n;++i){
		reg double a=p[1].x-p[0].x+p[i].x-p[(i+1)%n].x;
		reg double b=p[1].y-p[0].y+p[i].y-p[(i+1)%n].y;
		reg double c=p[1].x*p[0].y+p[i].x*p[(i+1)%n].y-p[0].x*p[1].y-p[(i+1)%n].x*p[i].y;
		if(sgn(a)!=0) S.push_back(Line(Point(0,c/a),Point(-a,c/a-b)));
		else if(sgn(b)!=0) S.push_back(Line(Point(-c/b,0),Point(-c/b,-b)));
	}
	printf("%.4lf\n",getS(HalfPlane(S))/getS(p));
	return 0;
}