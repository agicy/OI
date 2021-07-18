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

const int MAXN=1e5+5;

int n;
int cnt,head[MAXN],to[MAXN<<1],nxt[MAXN<<1];

inline void Add_Edge(reg int u,reg int v){
	nxt[++cnt]=head[u];
	to[cnt]=v;
	head[u]=cnt;
	return;
}

int siz[MAXN];
int f[MAXN][2],g[MAXN][3];
int Max;

inline void dfs1(reg int u,reg int father){
	siz[u]=1;
	f[u][1]=1,g[u][0]=1;
	for(reg int i=head[u];i;i=nxt[i]){
		reg int v=to[i];
		if(v!=father){
			dfs1(v,u);
			siz[u]+=siz[v];
			f[u][1]+=f[v][0],g[u][1]+=g[v][0];
			if(f[v][0]<f[v][1])
				f[u][0]+=f[v][1],g[u][0]+=g[v][1],g[u][2]+=g[v][2];
			else if(f[v][0]==f[v][1])
				f[u][0]+=f[v][0],g[u][0]+=g[v][0]+g[v][1]-g[v][2],g[u][2]+=g[v][0];
			else
				f[u][0]+=f[v][0],g[u][0]+=g[v][0],g[u][2]+=g[v][0];
		}
	}
	return;
}

ll ans;

inline void dfs2(reg int u,reg int father){
	int __f[2],__g[3];
	memcpy(__f,f[u],sizeof(f[u]));
	memcpy(__g,g[u],sizeof(g[u]));
	if(father){
		f[u][1]+=f[father][0],g[u][1]+=g[father][0];
		if(f[father][0]<f[father][1])
			f[u][0]+=f[father][1],g[u][0]+=g[father][1],g[u][2]+=g[father][2];
		else if(f[father][0]==f[father][1])
			f[u][0]+=f[father][0],g[u][0]+=g[father][0]+g[father][1]-g[father][2],g[u][2]+=g[father][0];
		else
			f[u][0]+=f[father][0],g[u][0]+=g[father][0],g[u][2]+=g[father][0];
	}
	for(reg int i=head[u];i;i=nxt[i]){
		reg int v=to[i];
		if(v!=father){
			f[u][1]-=f[v][0],g[u][1]-=g[v][0];
			if(f[v][0]<f[v][1])
				f[u][0]-=f[v][1],g[u][0]-=g[v][1],g[u][2]-=g[v][2];
			else if(f[v][0]==f[v][1])
				f[u][0]-=f[v][0],g[u][0]-=g[v][0]+g[v][1]-g[v][2],g[u][2]-=g[v][0];
			else
				f[u][0]-=f[v][0],g[u][0]-=g[v][0],g[u][2]-=g[v][0];
			if(f[u][1]+f[v][1]>Max)
				ans+=1ll*siz[v]*(n-siz[v])-1ll*(siz[v]-g[v][1])*(n-siz[v]-g[u][1]);
			dfs2(v,u);
			f[u][1]+=f[v][0],g[u][1]+=g[v][0];
			if(f[v][0]<f[v][1])
				f[u][0]+=f[v][1],g[u][0]+=g[v][1],g[u][2]+=g[v][2];
			else if(f[v][0]==f[v][1])
				f[u][0]+=f[v][0],g[u][0]+=g[v][0]+g[v][1]-g[v][2],g[u][2]+=g[v][0];
			else
				f[u][0]+=f[v][0],g[u][0]+=g[v][0],g[u][2]+=g[v][0];
		}
	}
	memcpy(f[u],__f,sizeof(__f));
	memcpy(g[u],__g,sizeof(__g));
	return;
}

int main(void){
	n=read();
	for(reg int i=1;i<n;++i){
		static int u,v;
		u=read(),v=read();
		Add_Edge(u,v),Add_Edge(v,u);
	}
	dfs1(1,0),Max=max(f[1][0],f[1][1]),dfs2(1,0);
	printf("%lld\n",ans);
	return 0;
}