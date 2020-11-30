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

const int MAXN=1e5+5;

int n;

struct Node{
	int x,y,t;
	inline Node(reg int x=0,reg int y=0,reg int t=0):x(x),y(y),t(t){
		return;
	}
};

Node a[MAXN],b[MAXN],c[MAXN];

inline bool cmpx(const Node& a,const Node& b){
	return a.x<b.x;
}

inline bool cmpy(const Node& a,const Node& b){
	return a.y<b.y;
}

ll sum[MAXN];

inline Node solve(reg Node a[]){
	reg int l=1,r=n;
	while(l<r){
		if(a[l].t>a[r].t)
			a[l].t-=a[r--].t;
		else if(a[l].t<a[r].t)
			a[r].t-=a[l++].t;
		else
			++l,--r;
	}
	return a[l];
}

ll ansx,ansy;
double Min=1e20;

inline void check(reg ll x,reg ll y){
	reg double sum=0;
	for(reg int i=1;i<=n;++i)
		sum+=1.0*c[i].t*max(abs(c[i].x-x),abs(c[i].y-y));
	if(sum<Min){
		Min=sum;
		ansx=x,ansy=y;
	}
	return;
}

int main(void){
	n=read();
	for(reg int i=1;i<=n;++i){
		static int x,y,t;
		x=read(),y=read(),t=read();
		a[i]=Node(x+y,x-y,t);
		b[i]=Node(x+y,x-y,t);
		c[i]=Node(x,y,t);
	}
	sort(a+1,a+n+1,cmpx);
	Node x=solve(a);
	sort(b+1,b+n+1,cmpy);
	Node y=solve(b);
	ll px=(x.x+y.y)/2,py=(x.x-y.y)/2;
	ansx=px,ansy=py;
	check(px,py);
	check(px+1,py+1);
	check(px,py+1);
	check(px+1,py);
	printf("%lld %lld\n",ansx,ansy);
	return 0;
}