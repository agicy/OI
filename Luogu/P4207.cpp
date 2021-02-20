#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

inline double max(reg double a,reg double b){
	return a>b?a:b;
}

inline double min(reg double a,reg double b){
	return a<b?a:b;
}

const int MAXN=500+5;
const double inf=1e20;
const double eps=1e-6;

struct Circle{
	double x,r;
};

struct Line{
	double k,b,l,r;
};

int n;
double alpha;
Circle C[MAXN];
Line L[MAXN];

inline double sqr(reg double x){
	return x*x;
}

inline double getH(reg double dis,reg double del){
	return sqrt(sqr(dis)-sqr(del));
}

inline void getLine(reg int x,reg int y){
	if(fabs(C[x].r-C[y].r)<eps){
		L[x].l=C[x].x,L[x].r=C[y].x;
		L[x].k=0;
		L[x].b=C[x].r;
		return;
	}
	reg double dx=C[y].x-C[x].x,dr=C[y].r-C[x].r;
	L[x].l=C[x].x-C[x].r*dr/dx,L[x].r=C[y].x-C[y].r*dr/dx;
	reg double lef=getH(C[x].r,-C[x].r*dr/dx),rig=getH(C[y].r,-C[y].r*dr/dx);
	L[x].k=(lef-rig)/(L[x].l-L[x].r);
	L[x].b=lef-L[x].l*L[x].k;
	return;
}

inline double f(reg double x){
	reg double res=0;
	for(reg int i=1;i<=n;++i)
		if(C[i].x-C[i].r<x&&x<C[i].x+C[i].r)
			res=max(res,getH(C[i].r,x-C[i].x));
	for(reg int i=1;i<n;++i)
		if(L[i].l<=x&&x<=L[i].r)
			res=max(res,L[i].k*x+L[i].b);
	return res;
}

inline double simpson(reg double l,reg double r){
	reg double mid=0.5*(l+r);
	return (r-l)*(f(l)+4.0*f(mid)+f(r))/6.0;
}

inline double asr(reg double l,reg double r,reg double res){
	reg double mid=0.5*(l+r);
	reg double lef=simpson(l,mid),rig=simpson(mid,r);
	if(fabs(lef+rig-res)<eps)
		return lef+rig;
	else
		return asr(l,mid,lef)+asr(mid,r,rig);
}

int main(void){
	scanf("%d%lf",&n,&alpha);
	++n;
	alpha=1.0/tan(alpha);
	scanf("%lf",&C[1].x);
	C[1].x*=alpha;
	for(reg int i=2;i<=n;++i){
		static double h;
		scanf("%lf",&h);
		C[i].x=h*alpha+C[i-1].x;
	}
	for(reg int i=1;i<n;++i)
		scanf("%lf",&C[i].r);
	C[n].r=0.0;
	for(reg int i=1;i<n;++i)
		getLine(i,i+1);
	reg double l=inf,r=-inf;
	for(reg int i=1;i<=n;++i)
		l=min(l,C[i].x-C[i].r),r=max(r,C[i].x+C[i].r);
	printf("%.2lf\n",2.0*asr(l,r,simpson(l,r)));
	return 0;
}