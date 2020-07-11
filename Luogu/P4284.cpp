#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
typedef unsigned long long ull;
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

const int MAXN=500000+5;

inline void Read(void);
inline void Work(void);

int main(void){
	Read();
	Work();
	return 0;
}

int n;
int cnt,head[MAXN],to[MAXN<<1],Next[MAXN<<1];
double w[MAXN<<1];
double q[MAXN];

inline void Add_Edge(reg int u,reg int v,reg double len){
	Next[++cnt]=head[u];
	to[cnt]=v;
	w[cnt]=len;
	head[u]=cnt;
	return;
}

inline void Read(void){
	n=read();
	for(reg int i=1;i<n;++i){
		static int a,b,p;
		a=read(),b=read(),p=read();
		Add_Edge(a,b,p/100.0);
		Add_Edge(b,a,p/100.0);
	}
	for(reg int i=1;i<=n;++i)
		q[i]=read()/100.0;
	return;
}

double dp[2][MAXN];

inline void DFS(reg int ID,reg int father){
	dp[0][ID]=1-q[ID];
	for(reg int i=head[ID];i;i=Next[i])
		if(to[i]!=father){
			DFS(to[i],ID);
			dp[0][ID]*=(1-w[i]+w[i]*dp[0][to[i]]);
		}
	return;
}

inline void DP(reg int ID,reg int father,reg double f_w){
	reg double p=dp[1][father]/(1-f_w+f_w*dp[0][ID]);
	dp[1][ID]=dp[0][ID]*(1-f_w+f_w*p);
	for(reg int i=head[ID];i;i=Next[i])
		if(to[i]!=father)
			DP(to[i],ID,w[i]);
	return;
}

inline void Work(void){
	DFS(1,0);
	DP(1,0,0);
	reg double ans=0;
	for(reg int i=1;i<=n;++i)
		ans+=1-dp[1][i];
	printf("%.6lf\n",ans);
	return;
}
