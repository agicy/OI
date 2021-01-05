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

const int MAXN=1e3+5;
const int MAXM=1e3+5;
const int MAXV=2*MAXM+MAXN;
const int MAXE=2*(2*MAXN+2*MAXM+2*MAXN*MAXM);
const ll inf=0x3f3f3f3f3f3f3f3f;

int n,m;
int a[MAXN],b[MAXN];
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
queue<int> Q;

inline bool bfs(int s,reg int t){
	memset(dep,-1,sizeof(dep));
	dep[s]=1,Q.push(s);
	while(!Q.empty()){
		reg int u=Q.front();
		Q.pop();
		for(reg int i=head[u];i;i=Next[i]){
			int v=to[i];
			if(dep[v]==-1&&w[i]){
				dep[v]=dep[u]+1;
				Q.push(v);
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
			reg int f=dfs(v,t,min(lim-flow,w[i]));
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
	n=read();
	reg ll sum=0;
	for(reg int i=1;i<=n;++i)
		a[i]=read(),sum+=a[i];
	for(reg int i=1;i<=n;++i)
		b[i]=read(),sum+=b[i];
	m=read();
	reg int s=0,t=n+2*m+1;
	for(reg int i=1;i<=n;++i)
		Add_Tube(s,i,a[i]),Add_Tube(i,t,b[i]);
	for(reg int i=1;i<=m;++i){
		static int k,c1,c2;
		k=read(),c1=read(),c2=read();
		sum+=c1+c2;
		Add_Tube(s,i+n,c1);
		Add_Tube(i+n+m,t,c2);
		for(reg int j=0;j<k;++j){
			static int x;
			x=read();
			Add_Tube(i+n,x,inf);
			Add_Tube(x,i+n+m,inf);
		}
	}
	printf("%lld\n",sum-dinic(s,t));
	return 0;
}