#include<bits/stdc++.h>
using namespace std;
#define reg register
#define INF 0X3F3F3F3F
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(ch<'0'||'9'<ch)ch=getchar();
	while('0'<=ch&&ch<='9')res=10*res+ch-'0',ch=getchar();
	return res;
}

const int MAXN=5000+5;

inline void Read(void);
inline void Work(void);

int main(void){
	Read();
	Work();
	return 0;
}

int cnt,head[MAXN],to[MAXN<<1],w[MAXN<<1],Next[MAXN<<1];

inline void Add_Edge(reg int u,reg int v,reg int len){
	Next[++cnt]=head[u];
	to[cnt]=v;
	w[cnt]=len;
	head[u]=cnt;
	return;
}

int n;
int u[MAXN],v[MAXN],d[MAXN];

inline void Read(void){
	n=read();
	for(reg int i=1;i<n;++i){
		u[i]=read(),v[i]=read(),d[i]=read();
		Add_Edge(u[i],v[i],d[i]);
		Add_Edge(v[i],u[i],d[i]);
	}
	return;
}

bool vis[MAXN];
int son[MAXN];
int dp[2][MAXN];

inline void GetD(reg int ID,reg int &d){
	vis[ID]=true;
	for(reg int i=head[ID];i;i=Next[i])
		if(!vis[to[i]]){
			GetD(to[i],d);
			if(dp[0][to[i]]+w[i]>dp[0][ID]){
				dp[1][ID]=dp[0][ID];
				dp[0][ID]=dp[0][to[i]]+w[i];
				son[ID]=to[i];
			}
			else if(dp[0][to[i]]+w[i]>dp[1][ID])
				dp[1][ID]=dp[0][to[i]]+w[i];
		}
	d=max(d,dp[0][ID]+dp[1][ID]);
	return;
}

inline void GetR(reg int ID,int last,reg int &r){
	vis[ID]=false;
	r=min(r,max(last,dp[0][ID]));
	for(reg int i=head[ID];i;i=Next[i])
		if(vis[to[i]]){
			if(to[i]==son[ID])
				GetR(to[i],max(dp[1][ID]+w[i],last+w[i]),r);
			else
				GetR(to[i],max(dp[0][ID]+w[i],last+w[i]),r);
		}
	return;
}

inline void clear(void){
	memset(dp,0,sizeof(dp));
	memset(son,0,sizeof(son));
	memset(vis,false,sizeof(vis));
	return;
}

inline void Work(void){
	int ans=INF;
	for(reg int i=1;i<n;++i){
		clear();
		vis[v[i]]=true;
		int d1=0,d2=0;
		GetD(u[i],d1),GetD(v[i],d2);
		vis[v[i]]=false;
		int r1=INF,r2=INF;
		GetR(u[i],0,r1),GetR(v[i],0,r2);
		ans=min(ans,max(max(d1,d2),r1+r2+d[i]));
	}
	printf("%d\n",ans);
	return;
}