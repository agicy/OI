#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg bool f=false;
	reg char ch=getchar();
	reg int ans=0;
	while(!isdigit(ch))f|=(ch=='-'),ch=getchar();
	while(isdigit(ch))ans=10*ans+(ch^'0'),ch=getchar();
	return f?-ans:ans;
}

inline ll max(reg ll a,reg ll b){
	return a>b?a:b;
}

struct Vector{
	int x,y;
	inline Vector(reg int x=0,reg int y=0):x(x),y(y){
		return;
	}
	inline Vector operator+(const Vector& a)const{
		return Vector(x+a.x,y+a.y);
	}
	inline Vector operator-(const Vector& a)const{
		return Vector(x-a.x,y-a.y);
	}
};

inline ll dot(const Vector& a,const Vector& b){
	return 1ll*a.x*b.x+1ll*a.y*b.y;
}

inline ll cross(const Vector& a,const Vector& b){
	return 1ll*a.x*b.y-1ll*a.y*b.x;
}

typedef Vector Point;

inline bool cmp(const Point& a,const Point& b){
	return a.x<b.x||(a.x==b.x&&a.y<b.y);
}

inline ll getDis(const Point& a,const Point& b){
	return dot(a-b,a-b);
}

const int MAXN=5e4+5;

int n;
Point p[MAXN];
int tot;
Point q[MAXN];

int main(void){
	n=read();
	for(reg int i=1;i<=n;++i)
		p[i].x=read(),p[i].y=read();
	sort(p+1,p+n+1,cmp);
	reg int top=0;
	static int S[MAXN];
	for(reg int i=1;i<=n;++i){
		while(top>1&&cross(p[S[top]]-p[S[top-1]],p[i]-p[S[top-1]])<=0)
			--top;
		S[++top]=i;
	}
	reg int tmp=top;
	for(reg int i=n-1;i>=1;--i){
		while(top>tmp&&cross(p[S[top]]-p[S[top-1]],p[i]-p[S[top-1]])<=0)
			--top;
		S[++top]=i;
	}
	if(n>1)
		--top;
	for(reg int i=0;i<top;++i)
		q[i]=p[S[i+1]];
	tot=top;
	q[tot]=q[0];
	reg ll ans=0;
	reg int j=1;
	for(reg int i=0;i<tot;++i){
		while(cross(q[i+1]-q[i],q[j]-q[i])<cross(q[i+1]-q[i],q[j+1]-q[i]))
			j=(j+1)%tot;
		ans=max(ans,max(getDis(q[i],q[j]),getDis(q[i+1],q[j])));
	}
	printf("%lld\n",ans);
	return 0;
}