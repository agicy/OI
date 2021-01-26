#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

const int MAXN=1e5+5;
const double pi=acos(-1.0);

struct Node{
	double x,y;
	inline Node(reg double x=0,reg double y=0):x(x),y(y){
		return;
	}
	inline Node operator+(const Node& a){
		return Node(x+a.x,y+a.y);
	}
	inline Node operator-(const Node& a){
		return Node(x-a.x,y-a.y);
	}
};

inline double sqr(reg double x){
	return x*x;
}

inline double getDis(const Node& a,const Node& b){
	return sqrt(sqr(a.x-b.x)+sqr(a.y-b.y));
}

inline double cross(const Node& a,const Node& b){
	return a.x*b.y-a.y*b.x;
}

inline bool cmp(const Node& a,const Node& b){
	return a.x<b.x||(a.x==b.x&&a.y<b.y);
}

int n;
double a,b,r;
Node p[MAXN<<2];

int main(void){
	scanf("%d%lf%lf%lf",&n,&a,&b,&r);
	a-=2.0*r,b-=2.0*r;
	reg double len=0.5*sqrt(sqr(a)+sqr(b));
	const double angle[4]={atan(a/b),pi-atan(a/b),pi+atan(a/b),2*pi-atan(a/b)};
	for(reg int i=1;i<=n;++i){
		static double x,y,t;
		scanf("%lf%lf%lf",&x,&y,&t);
		for(reg int j=0;j<4;++j)
			p[i+j*n].x=cos(t+angle[j])*len+x,p[i+j*n].y=sin(t+angle[j])*len+y;
	}
	reg double ans=2.0*pi*r;
	n<<=2;
	sort(p+1,p+n+1,cmp);
	reg int top=0;
	static int S[MAXN];
	S[++top]=1,S[++top]=2;
	for(reg int i=3;i<=n;++i){
		while(top>1&&cross(p[S[top]]-p[S[top-1]],p[i]-p[S[top]])<0.0)
			--top;
		S[++top]=i;
	}
	reg int tmp=top;
	S[++top]=n,S[++top]=n-1;
	for(reg int i=n-2;i>=1;--i){
		while(top>tmp+1&&cross(p[S[top]]-p[S[top-1]],p[i]-p[S[top]])<0.0)
			--top;
		S[++top]=i;
	}
	for(reg int i=1;i<=top-1;++i)
		ans+=getDis(p[S[i]],p[S[i+1]]);
	printf("%.2lf\n",ans);
	return 0;
}