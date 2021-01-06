#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return res;
}

const int MAXN=200+5;
const int MAXM=10200+5;
const int MAXV=MAXN;
const int MAXE=2*(MAXM+MAXN);
const int inf=0x3f3f3f3f;

int cnt=1,head[MAXV],to[MAXE],Next[MAXE];
ll w[MAXE];

inline void Add_Edge(reg int u,reg int v,reg ll len){
	Next[++cnt]=head[u];
	to[cnt]=v;
	w[cnt]=len;
	head[u]=cnt;
	return;
}

inline void Add_Tube(reg int u,reg int v,reg ll len){
	Add_Edge(u,v,len);
	Add_Edge(v,u,0);
	return;
}

int dep[MAXV];
int Q[MAXV];

inline bool bfs(reg int s,reg int t){
	memset(dep,-1,sizeof(dep));
	reg int h=0,ta=0;
	dep[s]=1,Q[ta++]=s;
	while(h<ta){
		reg int u=Q[h++];
		for(reg int i=head[u];i;i=Next[i]){
			reg int v=to[i];
			if(dep[v]==-1&&w[i]){
				dep[v]=dep[u]+1;
				Q[ta++]=v;
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
			reg ll f=dfs(v,t,min(lim-flow,w[i]));
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
	reg int res=0;
	while(bfs(s,t)){
		memcpy(cur,head,sizeof(head));
		res+=dfs(s,t,inf);
	}
	return res;
}

int n,m;
ll l[MAXM];
ll d[MAXN];

int main(void){
	n=read(),m=read();
	for(reg int i=1;i<=m;++i){
		static int s,t;
		static ll r;
		s=read(),t=read(),l[i]=read(),r=read();
		d[t]+=l[i],d[s]-=l[i];
		Add_Tube(s,t,r-l[i]);
	}
	reg int s=0,t=n+1;
	reg ll sum=0;
	for(reg int i=1;i<=n;++i){
		if(d[i]>0){
			Add_Tube(s,i,d[i]);
			sum+=d[i];
		}
		if(d[i]<0)
			Add_Tube(i,t,-d[i]);
	}
	reg ll flow=dinic(s,t);
	if(flow==sum){
		puts("YES");
		for(reg int i=1,j=3;i<=m;++i,j+=2)
			printf("%lld\n",w[j]+l[i]);
	}
	else
		puts("NO");
	return 0;
}