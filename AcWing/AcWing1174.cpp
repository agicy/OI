#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

const int MAXN=1e4+5;
const int MAXM=5e4+5;

int n,m;
int a[MAXM],b[MAXM];
int cnt,head[MAXN],to[MAXM],Next[MAXM];

inline void Add_Edge(reg int u,reg int v){
	Next[++cnt]=head[u];
	to[cnt]=v;
	head[u]=cnt;
	return;
}

bool vis[MAXN];
int tim,dfn[MAXN],low[MAXN];
int top,S[MAXN];
int tarjan_cnt,col[MAXN],siz[MAXN];

inline void tarjan(reg int u){
	vis[u]=true;
	dfn[u]=low[u]=++tim;
	S[++top]=u;
	for(reg int i=head[u];i;i=Next[i]){
		reg int v=to[i];
		if(!dfn[v]){
			tarjan(v);
			low[u]=min(low[u],low[v]);
		}
		else if(vis[v]){
			low[u]=min(low[u],dfn[v]);
		}
	}
	if(dfn[u]==low[u]){
		reg int v;
		++tarjan_cnt;
		do{
			v=S[top--];
			vis[v]=false;
			++siz[tarjan_cnt];
			col[v]=tarjan_cnt;
		}while(v!=u);
	}
	return;
}

int outDeg[MAXN];

int main(void){
	scanf("%d%d",&n,&m);
	for(reg int i=1;i<=m;++i){
		scanf("%d%d",&a[i],&b[i]);
		Add_Edge(a[i],b[i]);
	}
	for(reg int i=1;i<=n;++i)
		if(!dfn[i])
			tarjan(i);
	for(reg int i=1;i<=m;++i)
		if(col[a[i]]!=col[b[i]])
			++outDeg[col[a[i]]];
	reg bool f=false;
	int ans=0;
	for(reg int i=1;i<=tarjan_cnt;++i)
		if(!f&&outDeg[i]==0){
			ans=siz[i];
			f=true;
		}
		else if(f&&outDeg[i]==0){
			puts("0");
			return 0;
		}
	printf("%d\n",ans);
	return 0;
}