#include<bits/stdc++.h>
using namespace std;
#define reg register

const int MAXN=10+5;
const int MAXM=1000+5;

struct Point{
	double x,y;
	inline Point(reg double x=0,reg double y=0):x(x),y(y){
		return;
	}
	inline void Read(void){
		scanf("%lf%lf",&x,&y);
		return;
	}
};

struct Node{
	Point p;
	double r;
	inline void Read(void){
		p.Read(),scanf("%lf",&r);
		return;
	}
};


int n,m,r;
Node B[MAXN];
Point E[MAXM];
double x,y;
int ans;

inline double GetDis(const Point& a,const Point& b){
	reg double dx=a.x-b.x,dy=a.y-b.y;
	return sqrt(dx*dx+dy*dy);
}

inline int GetAns(reg double x,reg double y){
	static Point p;
	p=Point(x,y);
	double R=r;
	for(reg int i=1;i<=n;++i)
		R=min(R,GetDis(p,B[i].p)-B[i].r);
	reg int res=0;
	for(reg int i=1;i<=m;++i)
		if(GetDis(E[i],p)<=R)
			++res;
	return res;
}

inline void SA(reg double x,reg double y){
	int ansnow=GetAns(x,y);
	const double delta=0.985;
	for(reg double T=2000;T>1e-10;T*=delta){
		reg double dx=(rand()*2-RAND_MAX)*T,dy=(rand()*2-RAND_MAX)*T;
		int now=GetAns(x+dx,y+dy),delta=now-ansnow;
		if(delta>0){
			ansnow=now;
			ans=max(ans,ansnow);
			x=x+dx;
			y=y+dy;
		}
		else if(exp((double)-delta/T)*RAND_MAX<rand()){
			x=x+dx;
			y=y+dy;
			ansnow=now;
		}
	}
	return;
}

int main(void){
	scanf("%d%d%d",&n,&m,&r);
	for(reg int i=1;i<=n;++i)
		B[i].Read();
	for(reg int i=1;i<=m;++i){
		E[i].Read();
		x+=E[i].x,y+=E[i].y;
	}
	x=x/m,y=y/m;
	ans=GetAns(x,y);
	while(clock()<0.75*CLOCKS_PER_SEC)
		SA(x,y);
	printf("%d\n",ans);
	return 0;
}