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

inline int dot(const Vector& a,const Vector& b){
	return a.x*b.x+a.y*b.y;
}

inline int cross(const Vector& a,const Vector& b){
	return a.x*b.y-a.y*b.x;
}

typedef Vector Point;

inline bool operator<(const Point& a,const Point& b){
	return a.x<b.x||(a.x==b.x&&a.y<b.y);
}

const int mod=998244353;

inline int add(reg int a,reg int b){
	a+=b;
	return a>=mod?a-mod:a;
}

inline int sub(reg int a,reg int b){
	a-=b;
	return a<0?a+mod:a;
}

const int MAXN=200+5;

int n;
int bas[MAXN];
Point a[MAXN];

int main(void){
	n=read();
	for(reg int i=1;i<=n;++i)
		a[i].x=read(),a[i].y=read();
	sort(a+1,a+n+1);
	bas[0]=1;
	for(reg int i=1;i<=n;++i)
		bas[i]=add(bas[i-1],bas[i-1]);
	reg int sum=0;
	for(reg int i=1;i<n;++i)
		for(reg int j=i+1;j<=n;++j){
			reg int cnt=0;
			for(reg int k=i+1;k<j;++k)
				if(!cross(a[i]-a[k],a[k]-a[j]))
					++cnt;
			sum=add(sum,bas[cnt]);
		}
	reg int ans=sub(bas[n],add(sum,add(n,1)));
	printf("%d\n",ans);
	return 0;
}