#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
typedef unsigned long long ull;
#define INF 1e18
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

const int MAXN=100000+5;
const int MAXK=200+5;

inline void Read(void);
inline void Work(void);

int main(void){
	Read();
	Work();
	return 0;
}

int n,K;
int a[MAXN];

inline void Read(void){
	n=read(),K=read();
	for(reg int i=1;i<=n;++i)
		a[i]=read();
	return;
}

ll sum[MAXN];
ll f[MAXN],g[MAXN];
int fa[MAXK][MAXN];

inline double slope(reg int a,reg int b){
	reg ll x1=-sum[a],x2=-sum[b];
	reg ll y1=g[a]-sum[a]*sum[a];
	reg ll y2=g[b]-sum[b]*sum[b];
	if(x1==x2)
		return -INF;
	else
		return (double)(y1-y2)/(x1-x2);
}

int Q[MAXN];

inline void Work(void){
	for(reg int i=1;i<=n;++i)
		sum[i]=sum[i-1]+a[i];
	for(reg int T=1;T<=K;++T){
		for(reg int i=1;i<=n;++i)
			g[i]=f[i];
		reg int head=0,tail=0;
		for(reg int i=1;i<=n;++i){
			while(tail-head>=2&&slope(Q[head],Q[head+1])<=sum[i])
				++head;
			f[i]=0;
			if(head<tail){
				fa[T][i]=Q[head];
				f[i]=g[Q[head]]+sum[Q[head]]*(sum[i]-sum[Q[head]]);
			}
			while(tail-head>=2&&slope(Q[tail-1],Q[tail-2])>=slope(i,Q[tail-1]))
				--tail;
			Q[tail++]=i;
		}
	}
	printf("%lld\n",f[n]);
	for(reg int x=fa[K][n];K;x=fa[--K][x])
		printf("%d%c",x,K==1?'\n':' ');
	return;
}
