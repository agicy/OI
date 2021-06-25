#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
static char buf[1<<21],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return res;
}

const int MAXN=200+5;
const int MAXM=5e3+5;
const int MAXV=MAXN;
const int MAXE=(MAXM)*2;
const ll inf=0x3f3f3f3f3f3f3f3f;

int n,m,s,t;
int cnt=1,head[MAXV],to[MAXE],w[MAXE],Next[MAXE];

inline void Add_Edge(reg int u,reg int v,reg int len){
	Next[++cnt]=head[u];
	to[cnt]=v,w[cnt]=len;
	head[u]=cnt;
	return;
}

inline void Add_Tube(reg int u,reg int v,reg int len){
	Add_Edge(u,v,len);
	Add_Edge(v,u,0);
	return;
}

int dep[MAXV];
int Q[MAXV];

inline bool bfs(reg int s,reg int t){
	reg int _head=0,_tail=0;
	memset(dep,-1,sizeof(dep));
	dep[s]=1,Q[_tail++]=s;
	while(_head<_tail){
		reg int u=Q[_head++];
		for(reg int i=head[u];i;i=Next[i]){
			reg int v=to[i];
			if(dep[v]==-1&&w[i]){
				dep[v]=dep[u]+1;
				Q[_tail++]=v;
			}
		}
	}
	return dep[t]!=-1;
}

int cur[MAXV];

inline ll dfs(reg int u,reg int t,reg ll lim){
	if(u==t)
		return lim;
	reg ll flow=0;
	for(reg int &i=cur[u];i;i=Next[i]){
		reg int v=to[i];
		if(dep[v]==dep[u]+1&&w[i]){
			reg ll f=dfs(v,t,min(lim-flow,0ll+w[i]));
			if(f){
				flow+=f;
				w[i]-=f,w[i^1]+=f;
				if(flow==lim)
					break;
			}
		}
	}
	return flow;
}

inline ll dinic(reg int s,reg int t){
	reg ll res=0;
	while(bfs(s,t)){
		memcpy(cur,head,sizeof(head));
		res+=dfs(s,t,inf);
	}
	return res;
}

int main(void){
	n=read(),m=read(),s=read(),t=read();
	for(reg int i=1;i<=m;++i){
		static int u,v,c;
		u=read(),v=read(),c=read();
		Add_Tube(u,v,c);
	}
	printf("%lld\n",dinic(s,t));
	return 0;
}