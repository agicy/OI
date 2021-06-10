#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

const double eps=1e-6;

inline int sgn(reg double x){
	if(fabs(x)<eps)
		return 0;
	else
		return x<0?-1:1;
}

inline double sqr(reg double x){
	return x*x;
}

const int MAXN=2e3+5;

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
	inline Vector operator*(const double a)const{
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

inline double getDis2(const Point& a,const Point& b){
	return dot(a-b,a-b);
}

inline double getDis(const Point& a,const Point& b){
	return sqrt(getDis2(a,b));
}

inline bool isEmpty(const Point& a){
	return a.x!=a.x||a.y!=a.y;
}

struct Circle{
	Point o;
	double r;
	inline bool contain(const Point& x)const{
		return sgn(sqr(r)-getDis2(x,o))>=0;
	}
	inline Point getRig(void)const{
		return o+Vector(r,0);
	}
};

inline bool isCon(const Circle& a,const Circle& b){
	return sgn(sqr(a.r-b.r)-getDis2(a.o,b.o))>=0;
}

inline bool isSep(const Circle& a,const Circle& b){
	return sgn(getDis2(a.o,b.o)-sqr(a.r+b.r))>0;
}

inline Point getPot(const Circle &a,const Circle &b){
	if(isCon(a,b))
		if(sgn(b.getRig().x-a.getRig().x)>0)
			return a.getRig();
		else
			return b.getRig();
	else if(isSep(a,b))
		return Point(nan(""),nan(""));
	else{
		if(a.contain(b.getRig()))
			return b.getRig();
		else if(b.contain(a.getRig()))
			return a.getRig();
		else{
			reg double d=getDis(a.o,b.o);
			reg double ang=acos(((sqr(a.r)+sqr(d))-sqr(b.r))/(2*a.r*d));
			reg double delta=atan2(b.o.y-a.o.y,b.o.x-a.o.x);
			reg double ang1=delta+ang,ang2=delta-ang;
			Point p1=a.o+Vector(cos(ang1)*a.r,sin(ang1)*a.r);
			Point p2=a.o+Vector(cos(ang2)*a.r,sin(ang2)*a.r);
			Point res;
			if(sgn(p2.x-p1.x)>0)
				res=p2;
			else
				res=p1;
			return res;
		}
	}
}

int n;
Circle a[MAXN];

int main(void){
	scanf("%d",&n);
	Point lef(0,0);
	for(reg int i=1;i<=n;++i){
		static int x,y,r;
		scanf("%d%d%d",&x,&y,&r);
		a[i].o=Point(x,y),a[i].r=r;
		if(i==2)
			lef=getPot(a[1],a[2]);
		else if(i>2){
			for(reg int j=1;j<i&&!isEmpty(lef);++j){
				Point tmp=getPot(a[i],a[j]);
				if(isEmpty(tmp)||tmp.x<=lef.x)
					lef=tmp;
			}
			for(reg int j=1;j<=i&&!isEmpty(lef);++j)
				if(!a[j].contain(lef))
					lef=Point(nan(""),nan(""));
		}
		if(isEmpty(lef)){
			printf("%d\n",i);
			return 0;
		}
	}
	puts("NIE");
	return 0;
}