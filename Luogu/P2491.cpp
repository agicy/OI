#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(ch<'0'||'9'<ch)ch=getchar();
	while('0'<=ch&&ch<='9')res=10*res+ch-'0',ch=getchar();
	return res;
}

const int MAXN=3e5+5;

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
int dis[MAXN];
queue<int> Q;

inline int bfs(int s){
	memset(vis,false,sizeof(vis));
	memset(dis,0,sizeof(dis));
	while(!Q.empty())Q.pop();
	vis[s]=true,dis[s]=0,Q.push(s);
	while(!Q.empty()){
		reg int u=Q.front();
		Q.pop();
		for(reg int i=head[u];i;i=Next[i]){
			int v=to[i];
			if(!vis[v]){
				vis[v]=true;
				dis[v]=dis[u]+w[i];
				Q.push(v);
			}
		}
	}
	reg int Max=0,pos=s;
	for(reg int i=1;i<=n;++i)
		if(Max<dis[i])
			pos=i,Max=dis[i];
	return pos;
}

int l,r;
int b[MAXN];

inline void dfs1(reg int u,int dis,reg int s1,reg int s2){
	l=max(l,dis);
	for(reg int i=head[u];i;i=Next[i]){
		reg int v=to[i];
		if(v!=s1&&v!=s2)
			dfs1(v,dis+w[i],u,u);
	}
	return;
}

inline void dfs2(reg int father,int u,reg int y,reg int cnt,reg int dis){
	if(u==y){
		b[0]=cnt,b[cnt]=dis;
		r=dis;
		return;
	}
	for(reg int i=head[u];i;i=Next[i]){
		reg int v=to[i];
		if(v!=father){
			dfs2(u,v,y,cnt+1,dis+w[i]);
			if(b[0]){
				b[cnt]=dis;
				dfs1(u,0,father,v);
				return;
			}
		}
	}
	return;
}

inline bool check(reg int mid,reg int s){
	reg int i,j;
	for(i=1;i<=b[0];++i)
		if(b[i]>mid)
			break;
	--i;
	for(j=i;j<=b[0];++j)
		if(b[j]-b[i]>s)
			break;
	--j;
	return b[b[0]]-b[j]<=mid;
}

int main(void){
	n=read(),s=read();
	for(reg int i=1;i<n;++i){
		static int u,v,w;
		u=read(),v=read(),w=read();
		Add_Edge(u,v,w);
		Add_Edge(v,u,w);
	}
	reg int L=bfs(1);
	reg int R=bfs(L);
	dfs2(0,L,R,1,0);
	while(l<r){
		reg int mid=(l+r)>>1;
		if(check(mid,s))
			r=mid;
		else
			l=mid+1;
	}
	printf("%d\n",l);
	return 0;
}