#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
static char buf[1<<21],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch)) ch=getchar();
	while(isdigit(ch)) res=10*res+(ch^'0'),ch=getchar();
	return res;
}

inline ll readll(void){
	reg char ch=getchar();
	reg ll res=0;
	while(!isdigit(ch)) ch=getchar();
	while(isdigit(ch)) res=10*res+(ch^'0'),ch=getchar();
	return res;
}

const int MAXN=1e5+5;

struct Point{
	ll x,y;
	inline Point(reg ll x=0,reg ll y=0):x(x),y(y){
		return;
	}
};

int n;
ll d;
ll x[MAXN];
ll sum[MAXN];

inline double slope(const Point& a,const Point& b){
	return 1.0*(b.y-a.y)/(b.x-a.x);
}

int main(void){
	n=read(),d=readll();
	for(reg int i=1;i<=n;++i){
		sum[i]=sum[i-1]+readll(),x[i]=readll();
	}
	reg int top=0;
	static Point S[MAXN];
	reg double ans=0;
	for(reg int i=1;i<=n;++i){
		while(top>=2&&slope(S[top],S[top-1])>slope(Point(d*i,sum[i-1]),S[top]))
			--top;
		S[++top]=Point(d*i,sum[i-1]);
		reg int l=1,r=top,mid;
		while(l<r){
			mid=(l+r)>>1;
			if(slope(S[mid],Point(x[i]+d*i,sum[i]))<slope(S[mid+1],Point(x[i]+d*i,sum[i])))
				l=mid+1;
			else
				r=mid;
		}
		ans+=slope(S[l],Point(x[i]+d*i,sum[i]));
	}
	printf("%.0lf\n",ans);
	return 0;
}