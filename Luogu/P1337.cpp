#include<bits/stdc++.h>
using namespace std;
#define reg register
#define eps 1e-8
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg bool f=false;
	reg char ch=getchar();
	reg int res=0;
	while(ch<'0'||'9'<ch)f|=(ch=='-'),ch=getchar();
	while('0'<=ch&&ch<='9')res=10*res+ch-'0',ch=getchar();
	return f?-res:res;
}

const int MAXN=1000+5;

struct Node{
	int x,y,w;
	inline void Read(void){
		x=read(),y=read(),w=read();
		return;
	}
};

int n;
long double ansx,ansy;
Node p[MAXN];

inline void Solve(void){
	reg long double t=1000;
	while(t>eps){
		reg long double x=0,y=0;
		for(reg int i=1;i<=n;++i){
			reg long double dx=p[i].x-ansx,dy=p[i].y-ansy;
			reg long double dis=sqrt(dx*dx+dy*dy);
			if(dis==0)
				continue;
			x+=(p[i].x-ansx)*p[i].w/dis;
			y+=(p[i].y-ansy)*p[i].w/dis;
		}
		ansx+=x*t,ansy+=y*t;
		if(t>0.5)
			t*=0.5;
		else
			t*=0.97;
	}
	return;
}

int main(void){
	n=read();
	for(reg int i=1;i<=n;++i){
		p[i].Read();
		ansx+=p[i].x;
		ansy+=p[i].y;
	}
	ansx/=n,ansy/=n;
	Solve();
	printf("%.3Lf %.3Lf\n",ansx,ansy);
	return 0;
}