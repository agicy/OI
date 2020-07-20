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

const int MAXN=400000+5;

int n,m,K,x;
int cnt,head[MAXN],to[MAXN<<1],Next[MAXN<<1];

inline void Add_Edge(reg int u,reg int v){
	Next[++cnt]=head[u];
	to[cnt]=v;
	head[u]=cnt;
	return;
}

bool key[MAXN];
int ans=INF;
int f[2][MAXN],g[MAXN];

inline void DFS1(reg int u,reg int father){
	f[0][u]=f[1][u]=-INF;
	if(key[u])
		f[0][u]=0;
	for(reg int i=head[u];i;i=Next[i]){
		reg int v=to[i];
		if(v!=father){
			DFS1(v,u);
			if(f[0][v]+1>f[0][u]){
				f[1][u]=f[0][u];
				f[0][u]=f[0][v]+1;
			}
			else if(f[0][v]+1>f[1][u])
				f[1][u]=f[0][v]+1;
		}
	}
	return;
}

inline void DFS2(reg int u,reg int father){
	for(reg int i=head[u];i;i=Next[i]){
		reg int v=to[i];
		if(v!=father){
			DFS2(v,u);
			g[v]=(f[0][v]+1==f[0][u])?f[1][u]:f[0][u];
		}
	}
	return;
}

inline void DFS3(reg int u,reg int father,int Max,reg int dep){
	ans=min(ans,dep+max(0,max(Max,f[0][u]-dep)-K));
	for(reg int i=head[u];i;i=Next[i]){
		reg int v=to[i];
		if(v!=father)
			DFS3(v,u,max(g[v]-dep,Max),dep+1);
	}
	return;
}

int main(void){
	n=read();
	for(reg int i=1;i<n;++i){
		static int u,v;
		u=read(),v=read();
		Add_Edge(u,v);
		Add_Edge(v,u);
	}
	m=read();
	for(reg int i=1;i<=m;++i)
		key[read()]=true;
	K=read(),x=read();
	DFS1(x,0);
	DFS2(x,0);
	DFS3(x,0,-INF,0);
	printf("%d\n",max(0,ans)+1);
	return 0;
}