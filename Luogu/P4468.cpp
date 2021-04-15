#include<bits/stdc++.h>
using namespace std;
#define reg register

const int MAXN=10;
const int MAXM=60;
const double eps=1e-6;

int n,m;

inline double sqr(reg double x){
	return x*x;
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
	inline Vector operator*(reg double a){
		return Vector(x*a,y*a);
	}
	inline Vector operator/(reg double a){
		return Vector(x/a,y/a);
	}
	inline double getLen(void)const{
		return sqrt(sqr(x)+sqr(y));
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
	Point a,b;
	inline Line(reg double x1=0,reg double y1=0,reg double x2=0,reg double y2=0):a(x1,y1),b(x2,y2){
		return;
	}
	inline Vector trans(void)const{
		return b-a;
	}
};

inline Point getPoint(const Point& a,const Line& L){
	Vector tmp=L.trans()*(2.0/L.trans().getLen());
	return a+Vector(tmp.y,-tmp.x)*cross(L.a-a,L.b-a)/L.trans().getLen();
}

vector<Line> L;

inline int query(const Point& a,reg int t){
	if(t==-1)
		return eps<=a.x&&a.x<=100-eps&&eps<=a.y&&a.y<=100-eps;
	reg double val=cross(L[t].a-a,L[t].b-a);
	if(val<-eps||(-eps<=val&&val<=eps))
		return 0;
	else
		return query(a,t-1)+query(getPoint(a,L[t]),t-1);
}

int main(void){
	scanf("%d",&n);
	L.resize(n);
	for(reg int i=0;i<n;++i){
		static double x1,y1,x2,y2;
		scanf("%lf%lf%lf%lf",&x1,&y1,&x2,&y2);
		L[i]=Line(x1,y1,x2,y2);
	}
	scanf("%d",&m);
	while(m--){
		static double x,y;
		scanf("%lf%lf",&x,&y);
		printf("%d\n",query(Point(x,y),n-1));
	}
	return 0;
}