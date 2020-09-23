#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

const int MAXN=44+5;
const int MAXM=1995+5;

struct Edge{
	int x,y,id;
	inline Edge(reg int x=0,reg int y=0,reg int id=0):x(x),y(y),id(id){
		return;
	}
	inline bool operator<(const Edge& a)const{
		return id>a.id;
	}
};

int n,m;
int deg[MAXN];
int cnt,head[MAXN],to[MAXM<<1],w[MAXM<<1],Next[MAXM<<1];
bool vis[MAXM];
Edge E[MAXM];
int top,S[MAXM];

inline void Add_Edge(reg int u,reg int v,reg int len){
	Next[++cnt]=head[u];
	to[cnt]=v;
	w[cnt]=len;
	head[u]=cnt;
	return;
}

inline void dfs(reg int u,reg int id){
	for(reg int i=head[u];i;i=head[u]){
		reg int v=to[i];
		head[u]=Next[i];
		if(vis[i>>1])
			continue;
		vis[i>>1]=true;
		dfs(v,w[i]);
	}
	S[++top]=id;
	return;
}

int main(void){
	while(true){
		memset(deg,0,sizeof(deg));
		cnt=1,memset(head,0,sizeof(head));
		top=0,memset(vis,false,sizeof(vis));
		int n=0;
		int st;
		for(m=1;;++m){
			static int x,y,z;
			scanf("%d%d",&x,&y);
			if(!x&&!y)
				break;
			if(m==1)
				st=min(x,y);
			n=max(n,max(x,y));
			scanf("%d",&z);
			E[m]=Edge(x,y,z);
			++deg[x],++deg[y];
		}
		--m;
		if(!m)
			break;
		reg bool flag=true;
		for(reg int i=1;i<=n;++i)
			if(deg[i]&1){
				flag=false;
				break;
			}
		if(!flag){
			puts("Round trip does not exist.");
			continue;
		}
		sort(E+1,E+m+1);
		for(reg int i=1;i<=m;++i){
			Add_Edge(E[i].x,E[i].y,E[i].id);
			Add_Edge(E[i].y,E[i].x,E[i].id);
		}
		dfs(st,0);
		for(reg int i=top-1;i>=1;--i)
			printf("%d%c",S[i],i==1?'\n':' ');
	}
	return 0;
}