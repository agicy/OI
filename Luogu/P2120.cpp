#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
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

const int MAXN=1000000+5;

int n;
int x[MAXN],p[MAXN],c[MAXN];
int Q[MAXN];
ll sum[MAXN],sump[MAXN],dp[MAXN];

inline double X(int i){
	return sump[i];
}

inline double Y(reg int i){
	return dp[i]+sum[i];
}

inline double slope(reg int i,reg int j){
	return (Y(i)-Y(j))/(X(i)-X(j));
}

int main(void){
	n=read();
	for(reg int i=1;i<=n;++i){
		x[i]=read(),p[i]=read(),c[i]=read();
		sump[i]=sump[i-1]+p[i];
		sum[i]=sum[i-1]+(ll)x[i]*p[i];
	}
	reg int head=0,tail=0;
	for(reg int i=1;i<=n;++i){
		while(head<tail&&slope(Q[head+1],Q[head])<x[i])
			++head;
		dp[i]=dp[Q[head]]+(ll)x[i]*(sump[i]-sump[Q[head]])-sum[i]+sum[Q[head]]+c[i];
		while(head<tail&&slope(Q[tail-1],Q[tail])>slope(i,Q[tail]))
			--tail;
		Q[++tail]=i;
	}
	printf("%lld\n",dp[n]);
	return 0;
}
