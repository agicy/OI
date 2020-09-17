#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

inline void cMin(reg int &a,reg int b){
	if(a>b)
		a=b;
	return;
}

const int MAXN=1e5+5;
const int MAXM=2e5+5;

int n,m,Q;
int a[MAXM],b[MAXM];
int cnt,head[MAXN],to[MAXM<<1],Next[MAXM<<1];

inline void Add_Edge(reg int u,reg int v){
	Next[++cnt]=head[u];
	to[cnt]=v;
	head[u]=cnt;
	return;
}

int fa[MAXN];
bool val[MAXN];
int tim,dfn[MAXN],low[MAXN];
bool cut[MAXM<<1];

inline void tarjan(reg int u,reg int id){
	dfn[u]=low[u]=++tim;
	for(reg int i=head[u];i;i=Next[i]){
		if(i==id)
			continue;
		reg int v=to[i];
		if(!dfn[v]){
			tarjan(v,i^1);
			fa[v]=u;
			cMin(low[u],low[v]);
			if(low[v]>dfn[u]){
				val[v]=true;
				cut[i]=cut[i^1]=true;
			}
		}
		else
			cMin(low[u],dfn[v]);
	}
	return;
}

inline int lca(reg int u,reg int v){
    reg int res=0;
    while(dfn[u]>dfn[v]){
        if(val[u]){
            ++res;
			val[u]=false;
        }
		u=fa[u];
    }
    while(dfn[u]<dfn[v]){
        if(val[v]){
            ++res;
			val[v]=false;
        }
		v=fa[v];
    }
    while(u!=v){
        if(val[u]){
            val[u]=false;
            ++res;
        }
        if(val[v]){
            val[v]=false;
            ++res;
        }
        u=fa[u],v=fa[v];
    }
	return res;
}

int tarjan_cnt,col[MAXN];

inline void dfs(reg int u,reg int c){
	col[u]=c;
	for(reg int i=head[u];i;i=Next[i]){
		if(cut[i])
			continue;
		reg int v=to[i];
		if(!col[v])
			dfs(v,c);
	}
	return;
}

int main(void){
	reg int Case=0;
	while(scanf("%d%d",&n,&m)!=EOF&&n!=0&&m!=0){
		cnt=1,memset(head,0,sizeof(head));
		tim=0,memset(dfn,0,sizeof(dfn));
		memset(cut,false,sizeof(cut));
		memset(val,false,sizeof(val));
		tarjan_cnt=0,memset(col,0,sizeof(col));
		for(reg int i=1;i<=n;++i)
			fa[i]=i;

		printf("Case %d:\n",++Case);
		for(reg int i=1;i<=m;++i){
			scanf("%d%d",&a[i],&b[i]);
			Add_Edge(a[i],b[i]);
			Add_Edge(b[i],a[i]);
		}
		for(reg int i=1;i<=n;++i)
			if(!dfn[i])
				tarjan(i,0);
		for(reg int i=1;i<=n;++i)
			if(!col[i]){
				++tarjan_cnt;
				dfs(i,tarjan_cnt);
			}
		scanf("%d",&Q);
		reg int ans=tarjan_cnt-1;
		while(Q--){
			static int u,v;
			scanf("%d%d",&u,&v);
			if(col[u]!=col[v])
				ans-=lca(u,v);
			printf("%d\n",ans);
		}
		puts("");
	}
	return 0;
}