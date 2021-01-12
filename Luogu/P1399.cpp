#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define int ll
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return res;
}

const int MAXN=1e5+5;

int n;
int cnt,head[MAXN],to[MAXN<<1],w[MAXN<<1],Next[MAXN<<1];

inline void Add_Edge(reg int u,reg int v,reg int len){
	Next[++cnt]=head[u];
	to[cnt]=v,w[cnt]=len;
	head[u]=cnt;
	return;
}

bool vis[MAXN];
int top;
pair<int,int> S[MAXN];
int tot,cir[MAXN<<1],dis[MAXN<<1];
bool tag[MAXN];
int sum[MAXN<<1];

inline bool dfs1(reg int u,reg int father,reg int len){
	vis[u]=true;
	S[++top]=make_pair(u,len);
	for(reg int i=head[u];i;i=Next[i]){
		reg int v=to[i];
		if(v!=father){
			if(vis[v]){
				dis[tot+1]=len;
				while(S[top].first!=v){
					tag[cir[++tot]=S[top].first]=true;
					dis[tot+1]=S[top--].second;
				}
				tag[cir[++tot]=v]=true;
				return true;
			}
			else if(dfs1(v,u,w[i]))
				return true;
		}
	}
	vis[u]=false;
	--top;
	return false;
}

int ans;
int f[MAXN];

inline void dfs2(reg int u,reg int father){
	int cMax=0;
	for(reg int i=head[u];i;i=Next[i]){
		reg int v=to[i];
		if(v!=father&&!tag[v]){
			dfs2(v,u);
			if(f[u]<f[v]+w[i]){
				cMax=f[u];
				f[u]=f[v]+w[i];
			}
			else if(f[u]==f[v]+w[i]&&cMax<f[v]+w[i])
				cMax=f[v]+w[i];
		}
	}
	ans=max(ans,f[u]+cMax);
	return;
}

int g[MAXN<<1];

signed main(void){
	n=read();
	for(reg int i=1;i<=n;++i){
		static int a,b,l;
		a=read(),b=read(),l=read();
		Add_Edge(a,b,l);
		Add_Edge(b,a,l);
	}
	dfs1(1,0,0);
	for(reg int i=1;i<=tot;++i){
		dfs2(cir[i],0);
		g[i]=f[cir[i]];
	}
	for(reg int i=1;i<=tot;++i)
		cir[i+tot]=cir[i],dis[i+tot]=dis[i],g[i+tot]=g[i];
	for(reg int i=1;i<=(tot<<1);++i){
		sum[i]=sum[i-1]+dis[i];
	}
	reg int S=sum[tot];

	for(reg int i=1;i<=tot;++i){
		for(reg int j=i+1;j<=tot;++j){
			ans=max(ans,g[i]+g[j]+min(sum[j]-sum[i],S-(sum[j]-sum[i])));
		}
	}
	printf("%.1lf\n",0.5*ans);
	/*
	deque<int> Q;
	Q.push_back(1);
	for(reg int i=2;i<=tot*2;++i){
		while(!Q.empty()&&i-Q.front()>tot)
			Q.pop_front();
		if(!Q.empty())
			ans=max(ans,g[i]+g[Q.front()]+min(sum[i]-sum[Q.front()],S-(sum[i]-sum[Q.front()])));
		while(!Q.empty()&&g[Q.back()]-sum[Q.back()]<=g[i]-sum[i])
			Q.pop_back();
		Q.push_back(i);
	}
	printf("%.1lf\n",0.5*ans);*/
	return 0;
}