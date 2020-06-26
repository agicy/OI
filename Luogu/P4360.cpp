#include<bits/stdc++.h>
using namespace std;
#define reg register
#define INF (2e9+1)
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

const int MAXN=20000+5;

inline void Read(void);
inline void Work(void);

int main(void){
	Read();
	Work();
	return 0;
}

int n;
int w[MAXN],d[MAXN];

inline void Read(void){
	n=read();
	for(reg int i=1;i<=n;++i)
		w[i]=read(),d[i]=read();
	return;
}

int sum;
int s[MAXN];

inline double slope(reg int i,reg int j){
	return 1.0*(1.0*d[i]*s[i]-d[j]*s[j])/(s[i]-s[j]);
}

inline int Calc(reg int i,reg int j){
	return sum-d[j]*s[j]-d[i]*(s[i]-s[j]);
}

int Q[MAXN];

inline void Work(void){
	for(reg int i=n;i>=1;--i)
		d[i]+=d[i+1];
	for(reg int i=1;i<=n;++i){
		s[i]=s[i-1]+w[i];
		sum+=d[i]*w[i];
	}
	reg int head=0,tail=0;
	int ans=INF;
	for(reg int i=1;i<=n;++i){
		while(head<tail&&slope(Q[head],Q[head+1])>d[i])
			++head;
		ans=min(ans,Calc(i,Q[head]));
		while(head<tail&&slope(Q[tail-1],Q[tail])<slope(Q[tail],i))
			--tail;
		Q[++tail]=i;
	}
	printf("%d\n",ans);
	return;
}
