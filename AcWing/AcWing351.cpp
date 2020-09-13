#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar()(p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(ch<'0'||'9'<ch)ch=getchar();
	while('0'<=ch&&ch<='9')res=10*res+ch-'0',ch=getchar();
	return res;
}

const int MAXN=5e5+5;
const int inf=0x3f3f3f3f;

int n,s;
int cnt,head[MAXN],to[MAXN<<1],w[MAXN<<1],Next[MAXN<<1];

inline void Add_Edge(reg int u,reg int v,reg int len){
	Next[++cnt]=head[u];
	to[cnt]=v;
	w[cnt]=len;
	head[u]=cnt;
	return;
}

bool vis[MAXN];
int pre[MAXN];
int dis[MAXN];

inline void bfs(int s,reg bool flag){
	memset(dis,0x3f,sizeof(dis));
	queue<int> Q;
	dis[s]=0,Q.push(s);
	while(!Q.empty()){
		reg int u=Q.front();
		Q.pop();
		for(reg int i=head[u];i;i=Next[i]){
			int v=to[i];
			if(dis[v]==inf){
				dis[v]=dis[u]+w[i];
				if(flag)
					pre[v]=u;
				Q.push(v);
			}
		}
	}
	return;
}

int tot,d[MAXN];

inline void diameter(void){
	bfs(1,false);
	reg int s=1;
	for(reg int i=2;i<=n;++i)
		if(dis[i]>dis[s])
			s=i;
	bfs(s,true);
	int e=s;
	for(reg int i=1;i<=n;++i)
		if(dis[i]>dis[e])
			e=i;
	reg int p=e;
	while(p){
		d[++tot]=p;
		p=pre[p];
	}
	return;
}

int lst[MAXN];

inline void dfs(reg int u){
	for(reg int i=head[u];i;i=Next[i]){
		reg int v=to[i];
		if(!vis[v]){
			vis[v]=true;
			dfs(v);
			lst[u]=max(lst[u],lst[v]+w[i]);
		}
	}
	return;
}

inline int farthest(void){
	for(reg int i=1;i<=tot;++i)
		vis[d[i]]=true;
	for(reg int i=1;i<=tot;++i)
		dfs(d[i]);
	int res=-inf;
	for(reg int i=1;i<=tot;++i)
		res=max(res,lst[d[i]]);
	return res;
}

int main(void){
	n=read(),s=read();
	for(reg int i=1;i<n;++i){
		static int u,v,w;
		u=read(),v=read(),w=read();
		Add_Edge(u,v,w);
		Add_Edge(v,u,w);
	}
	diameter();
	int Max=farthest();
	int ans=inf;
	for(reg int head=1,tail=1;tail<=tot;++head)
		while(tail<=tot&&abs(dis[d[head]]-dis[d[tail]])<=s){
			ans=min(ans,max(Max,max(abs(dis[d[1]]-dis[d[head]]),abs(dis[d[tot]]-dis[d[tail]]))));
			++tail;
		}
	printf("%d\n",ans);
	return 0;
}