#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

inline void cMin(reg int &a,reg int b){
	if(a>b)
		a=b;
	return;
}

const int MAXN=100+5;
const int MAXE=MAXN*(MAXN-1);

int n;
int cnt,head[MAXN],to[MAXE],Next[MAXE];

inline void Add_Edge(reg int u,reg int v){
	Next[++cnt]=head[u];
	to[cnt]=v;
	head[u]=cnt;
	return;
}

bool vis[MAXN];
int tim,dfn[MAXN],low[MAXN];
int top,S[MAXN];
int tarjan_cnt,col[MAXN];

inline void tarjan(reg int u){
	vis[u]=true;
	dfn[u]=low[u]=++tim;
	S[++top]=u;
	for(reg int i=head[u];i;i=Next[i]){
		reg int v=to[i];
		if(!dfn[v]){
			tarjan(v);
			cMin(low[u],low[v]);
		}
		else if(vis[v])
			cMin(low[u],dfn[v]);
	}
	if(dfn[u]==low[u]){
		reg int v;
		++tarjan_cnt;
		do{
			v=S[top--];
			vis[v]=false;
			col[v]=tarjan_cnt;
		}while(u!=v);
	}
	return;
}

int inDeg[MAXN],outDeg[MAXN];

int main(void){
	scanf("%d",&n);
	for(reg int i=1;i<=n;++i){
		static int x;
		while(scanf("%d",&x)!=EOF&&x!=0)
			Add_Edge(i,x);
	}
	for(reg int i=1;i<=n;++i)
		if(!dfn[i])
			tarjan(i);
	for(reg int i=1;i<=n;++i)
		for(reg int j=head[i];j;j=Next[j]){
			reg int u=to[j];
			if(col[i]!=col[u])
				++inDeg[col[u]],++outDeg[col[i]];
		}
	int ans1=0,ans2=0;
	for(reg int i=1;i<=tarjan_cnt;++i){
		if(!inDeg[i])
			++ans1;
		if(!outDeg[i])
			++ans2;
	}
	printf("%d\n%d\n",ans1,(tarjan_cnt==1)?0:max(ans1,ans2));
	return 0;
}