#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return res;
}

const int MAXN=5e3+5;

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

int n;
Node p[MAXN];
double ans;

inline bool cmp(const Node& a,const Node& b){
	return a.x<b.x||(a.x==b.x&&a.y<b.y);
}

int main(void){
	n=read();
	for(reg int i=1;i<=n;++i)
		scanf("%lf%lf",&p[i].x,&p[i].y);
	sort(p+1,p+n+1,cmp);
	reg int top=0;
	static int S[MAXN];
	for(reg int i=1;i<=n;++i){
		while(top>1&&cross(p[S[top]]-p[S[top-1]],p[i]-p[S[top-1]])<0.0)
			--top;
		S[++top]=i;
	}
	reg int tmp=top;
	for(reg int i=n-1;i>=1;--i){
		while(top>tmp&&cross(p[S[top]]-p[S[top-1]],p[i]-p[S[top-1]])<0.0)
			--top;
		S[++top]=i;
	}
	for(reg int i=1;i<=top-1;++i)
		ans+=getDis(p[S[i]],p[S[i+1]]);
	printf("%.2lf\n",ans);
	return 0;
}