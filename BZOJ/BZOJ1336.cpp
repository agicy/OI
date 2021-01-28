#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define double long double

const int MAXN=1e5+5;

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

inline double sqr(reg double x){
	return x*x;
}

typedef Vector Point;

inline double getDis(const Point& a,const Point& b){
	return sqrt(sqr(a.x-b.x)+sqr(a.y-b.y));
}

struct Line{
	Point s;
	Vector v;
	inline Line(const Point& s,const Vector& v):s(s),v(v){
		return;
	}
};

inline Point getPoint(const Line& a,const Line& b){
	return a.s+a.v*(cross(b.v,b.s-a.s)/cross(b.v,a.v));
}

struct Circle{
	Point p;
	double r;
	inline Circle(const Point& p,reg double r=0):p(p),r(r){
		return;
	}
	inline bool isIn(const Point& a)const{
		return getDis(p,a)<r;
	}
};

inline Circle getCirc(const Point& a){
	return Circle(a,0);
}

inline Circle getCirc(const Point& a,const Point& b){
	return Circle((a+b)*0.5,getDis(a,b)*0.5);
}

inline Circle getCirc(const Point& a,const Point& b,const Point& c){
	Point ab=(a+b)*0.5,ac=(a+c)*0.5;
	Vector vab=a-b,vac=a-c;
	Vector hab=Vector(vab.y,-vab.x),hac=Vector(-vac.y,vac.x);
	Point p=getPoint(Line(ab,hab),Line(ac,hac));
	return Circle(p,getDis(p,a));
}

int n;
Point p[MAXN];

int main(void){
	srand(time(0));
	scanf("%d",&n);
	for(reg int i=1;i<=n;++i)
		scanf("%Lf%Lf",&p[i].x,&p[i].y);
	random_shuffle(p+1,p+n+1);
	Circle ans=Circle(Point(0,0),0);
	for(reg int i=2;i<=n;++i)
		if(!ans.isIn(p[i])){
			ans=getCirc(p[i]);
			for(reg int j=1;j<i;++j)
				if(!ans.isIn(p[j])){
					ans=getCirc(p[i],p[j]);
					for(reg int k=1;k<j;++k)
						if(!ans.isIn(p[k]))
							ans=getCirc(p[i],p[j],p[k]);
				}
		}
	printf("%.10Lf\n%.10Lf %.10Lf\n",ans.r,ans.p.x,ans.p.y);
	return 0;
}