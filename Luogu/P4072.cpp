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

const int MAXN=3000+5;

inline void Read(void);
inline void Work(void);

int main(void){
	Read();
	Work();
	return 0;
}

int n,m;
int d[MAXN];

inline void Read(void){
	n=read(),m=read();
	for(reg int i=1;i<=n;++i)
		d[i]=read();
	return;
}

ll f[MAXN],g[MAXN];
ll sum[MAXN];
int Q[MAXN];

inline double X(reg int i){
	return sum[i];
}

inline double Y(reg int i){
	return g[i]+sum[i]*sum[i];
}

inline double slope(reg int i,reg int j){
	return (Y(i)-Y(j))/(X(i)-X(j));
}

inline void Work(void){
	for(reg int i=1;i<=n;++i)
		sum[i]=sum[i-1]+d[i];
	for(reg int i=1;i<=n;++i)
		g[i]=sum[i]*sum[i];
	for(reg int i=1;i<m;++i){
		reg int head=1,tail=1;
		Q[1]=i;
		for(reg int j=i+1;j<=n;++j){
			while(head<tail&&slope(Q[head],Q[head+1])<2*sum[j])
				++head;
			f[j]=g[Q[head]]+(sum[j]-sum[Q[head]])*(sum[j]-sum[Q[head]]);
			while(head<tail&&slope(Q[tail-1],Q[tail])>slope(Q[tail],j))
				--tail;
			Q[++tail]=j;
		}
		for(reg int j=1;j<=n;++j)
			g[j]=f[j];
	}
	printf("%lld\n",-sum[n]*sum[n]+m*f[n]);
	return;
}
