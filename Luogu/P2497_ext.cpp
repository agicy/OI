#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
typedef unsigned long long ull;
typedef long double ldb;
#define INF 0X3F3F3F3F
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline ll read(void){
	reg bool f=false;
	reg char ch=getchar();
	reg ll res=0;
	while(ch<'0'||'9'<ch)f|=(ch=='-'),ch=getchar();
	while('0'<=ch&&ch<='9')res=10*res+ch-'0',ch=getchar();
	return f?-res:res;
}

const int MAXN=5000000+5;

inline void Read(void);
inline void Work(void);

int main(void){
	Read();
	Work();
	return 0;
}

struct Node{
	ll x,r;
	int v;
	inline void Read(void){
		x=read(),r=read(),v=read();
	}
};

inline ldb GetR(const Node& a,reg ldb x){
	reg ldb dx2=(x-a.x)*(x-a.x);
	reg ldb k=4.0*a.r;
	return dx2/k;
}

int n;
ll m;
Node a[MAXN];

inline void Read(void){
	n=read(),m=read();
	for(reg int i=1;i<=n;++i)
		a[i].Read();
	return;
}

ldb dp[MAXN];

inline ldb val(reg int j,reg int i){
	return dp[j]+a[i].v+sqrt(GetR(a[j],a[i].x));
}

int f[MAXN];

inline void Work(void){
	dp[1]=a[1].v;
	deque<int> Q;
	Q.push_back(1);
	ldb ans=1e36;
	for(reg int i=2;i<=n;++i){
		dp[i]=1e36;
		for(reg int j=1;j<i;++j){
			if(val(j,i)<dp[i]){
				f[i]=j;
				dp[i]=min(dp[i],val(j,i));
			}
		}
		if(a[i].x-a[i].r<=m&&m<=a[i].x+a[i].r)
			ans=min(ans,dp[i]);
		Q.push_back((int)i);
	}
	for(reg int i=1;i<=n;++i)
		printf("%.3Lf\n",dp[i]);
	for(reg int i=1;i<=n;++i)
		printf("%d->%d\n",f[i],i);
	return;
}
