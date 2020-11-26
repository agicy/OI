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
	while(!isdigit(ch))f|=(ch=='-'),ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return f?-res:res;
}

const int MAXN=1e3+5;
const int MAXB=20+5;
const int MAXV=MAXN+MAXB;
const int MAXE=(MAXN*MAXB+MAXN+MAXB)*2;
const int inf=0x3f3f3f3f;

int n,b;
int l[MAXN][MAXB];
int v[MAXB];
int cnt=1,head[MAXV],to[MAXE],w[MAXE],Next[MAXE];

inline void Add_Edge(reg int u,reg int v,reg int len){
	Next[++cnt]=head[u];
	to[cnt]=v;
	w[cnt]=len;
	head[u]=cnt;
	return;
}

inline void Add_Tube(reg int u,reg int v,reg int len){
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

inline int dfs(reg int u,reg int t,reg int lim){
	if(u==t)
		return lim;
	reg int flow=0;
	for(reg int &i=cur[u];i;i=Next[i]){
		reg int v=to[i];
		if(dep[v]==dep[u]+1&&w[i]){
			reg int f=dfs(v,t,min(lim-flow,w[i]));
			if(f){
				flow+=f;
				w[i]-=f;
				w[i^1]+=f;
				if(flow==lim)
					break;
			}
		}
	}
	return flow;
}

inline int dinic(reg int s,reg int t){
	reg int res=0;
	while(bfs(s,t)){
		memcpy(cur,head,sizeof(head));
		res+=dfs(s,t,inf);
	}
	return res;
}

int back_cnt,back_head[MAXV],back_w[MAXE];

inline bool check(reg int L,reg int R,reg int s,reg int t){
	back_cnt=cnt;
	for(reg int i=0;i<=n+b+1;++i)
		back_head[i]=head[i];
	for(reg int i=0;i<=cnt;++i)
		back_w[i]=w[i];
	for(reg int i=1;i<=n;++i)
		for(reg int j=L;j<=R;++j)
			Add_Tube(i,n+l[i][j],1);
	reg int flow=dinic(s,t);
	cnt=back_cnt;
	for(reg int i=0;i<=n+b+1;++i)
		head[i]=back_head[i];
	for(reg int i=0;i<=cnt;++i)
		w[i]=back_w[i];
	return flow==n;
}

int main(void){
	n=read(),b=read();
	for(reg int i=1;i<=n;++i)
		for(reg int j=1;j<=b;++j)
			l[i][j]=read();
	for(reg int i=1;i<=b;++i)
		v[i]=read();
	reg int s=0,t=n+b+1;
	for(reg int i=1;i<=n;++i)
		Add_Tube(s,i,1);
	for(reg int i=1;i<=b;++i)
		Add_Tube(n+i,t,v[i]);
	int ans=inf;
	for(reg int l=1,r=0;l<=b;++l){
		while(r<=b&&!check(l,r,s,t))
			++r;
		if(r==b+1)
			break;
		ans=min(ans,r-l+1);
	}
	printf("%d\n",ans);
	return 0;
}