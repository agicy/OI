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

const int MAXN=2e5+5;

int n;
int M[MAXN];
int cnt,head[MAXN],to[MAXN],Next[MAXN];

inline void Add_Edge(reg int u,reg int v){
	Next[++cnt]=head[u];
	to[cnt]=v;
	head[u]=cnt;
	return;
}

int tim,id[MAXN];
priority_queue<int> Q[MAXN];
int tmp[MAXN];

inline void dfs(reg int u){
	id[u]=++tim;
	for(reg int i=head[u];i;i=Next[i]){
		reg int v=to[i];
		dfs(v);
		if(Q[id[u]].size()<Q[id[v]].size())
			swap(id[u],id[v]);
		reg int siz=Q[id[v]].size();
		for(reg int i=0;i<siz;++i){
			tmp[i]=max(Q[id[u]].top(),Q[id[v]].top());
			Q[id[u]].pop(),Q[id[v]].pop();
		}
		for(reg int i=0;i<siz;++i)
			Q[id[u]].push(tmp[i]);
	}
	Q[id[u]].push(M[u]);
	return;
}

int main(void){
	n=read();
	for(reg int i=1;i<=n;++i)
		M[i]=read();
	for(reg int i=2;i<=n;++i){
		static int fa;
		fa=read();
		Add_Edge(fa,i);
	}
	dfs(1);
	reg ll ans=0;
	while(!Q[id[1]].empty()){
		ans+=Q[id[1]].top();
		Q[id[1]].pop();
	}
	printf("%lld\n",ans);
	return 0;
}