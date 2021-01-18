#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cctype>
using namespace std;
#define reg register
typedef long long ll;

inline int max(reg int a,reg int b){
	return a>b?a:b;
}

const int MAXN=2e5+5;
const int MAXLOG2A=16;

int n,m;
int a[MAXN];
int cnt,head[MAXN],to[MAXN<<1],Next[MAXN<<1];

inline void Add_Edge(reg int u,reg int v){
	Next[++cnt]=head[u];
	to[cnt]=v;
	head[u]=cnt;
	return;
}

int fa[MAXN],dep[MAXN];
int siz[MAXN],son[MAXN];

inline void dfs1(reg int u,reg int father){
	son[u]=0;
	siz[u]=1;
	fa[u]=father;
	dep[u]=dep[father]+1;
	for(reg int i=head[u];i;i=Next[i]){
		reg int v=to[i];
		if(v!=father){
			dfs1(v,u);
			siz[u]+=siz[v];
			if(siz[son[u]]<siz[v])
				son[u]=v;
		}
	}
	return;
}

namespace Trie{
	const int MAXSIZE=60*MAXN;
	struct Node{
		int ch[2];
		int siz;
		#define ch(x) unit[(x)].ch
		#define siz(x) unit[(x)].siz
	};
	int tot;
	Node unit[MAXSIZE];
	inline void Init(void){
		tot=0;
		ch(0)[0]=ch(0)[1]=0,siz(0)=0;
		return;
	}
	inline int New(void){
		reg int p=++tot;
		ch(p)[0]=ch(p)[1]=0,siz(p)=0;
		return p;
	}
	inline void pushup(reg int p){
		siz(p)=siz(ch(p)[0])+siz(ch(p)[1]);
		return;
	}
	inline int insert(reg int pre,reg int dep,reg int val){
		reg int p=New();
		unit[p]=unit[pre];
		++siz(p);
		if(dep!=-1){
			reg int c=(val>>dep)&1;
			ch(p)[c]=insert(ch(pre)[c],dep-1,val);
		}
		return p;
	}
	inline int query(reg int p,reg int q,reg int pre,reg int dep,reg int val){
		if(dep==-1)
			return 0;
		reg int c=(val>>dep)&1;
		if(siz(ch(p)[c^1])+siz(ch(q)[c^1])-2*siz(ch(pre)[c^1])>0)
			return (1<<dep)|query(ch(p)[c^1],ch(q)[c^1],ch(pre)[c^1],dep-1,val);
		else
			return query(ch(p)[c],ch(q)[c],ch(pre)[c],dep-1,val);
	}
}

int top[MAXN];
int rt[MAXN];

inline void dfs2(reg int u,reg int father,reg int topf){
	top[u]=topf;
	rt[u]=Trie::insert(rt[fa[u]],MAXLOG2A-1,a[u]);
	if(!son[u])
		return;
	dfs2(son[u],u,topf);
	for(reg int i=head[u];i;i=Next[i]){
		reg int v=to[i];
		if(v!=father&&v!=son[u])
			dfs2(v,u,v);
	}
	return;
}

inline int LCA(int x,int y){
	while(top[x]!=top[y]){
		if(dep[top[x]]>dep[top[y]])
			swap(x,y);
		y=fa[top[y]];
	}
	return dep[x]<dep[y]?x:y;
}

int main(void){
	while(scanf("%d%d",&n,&m)!=EOF){
		cnt=0,memset(head,0,sizeof(head));
		Trie::Init();
		for(reg int i=1;i<=n;++i)
			scanf("%d",&a[i]);
		for(reg int i=1;i<n;++i){
			static int u,v;
			scanf("%d%d",&u,&v);
			Add_Edge(u,v),Add_Edge(v,u);
		}
		dfs1(1,0);
		dfs2(1,0,1);
		while(m--){
			static int x,y,z;
			scanf("%d%d%d",&x,&y,&z);
			reg int lca=LCA(x,y);
			printf("%d\n",max(Trie::query(rt[x],rt[y],rt[LCA(x,y)],MAXLOG2A-1,z),a[lca]^z));
		}
	}
	return 0;
}