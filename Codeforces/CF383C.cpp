#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int MAXN=2e5+5;

namespace TreeArray{
	inline int lowbit(int x){
		return x&(-x);
	}
	int n,unit[MAXN];
	inline void Init(int s){
		n=s;
		memset(unit,0,sizeof(unit));
		return;
	}
	inline void update(int id,int val){
		for(int i=id;i<=n;i+=lowbit(i))
			unit[i]+=val;
		return;
	}
	inline int query(int id){
		int res=0;
		for(int i=id;i;i-=lowbit(i))
			res+=unit[i];
		return res;
	}
};

int n,m;
int a[MAXN];
int cnt,head[MAXN],to[MAXN<<1],Next[MAXN<<1];

inline void Add_Edge(int u,int v){
	Next[++cnt]=head[u];
	to[cnt]=v;
	head[u]=cnt;
	return;
}

int dep[MAXN];
int tim,dfn[MAXN],edf[MAXN];

inline void dfs(int u,int father){
	dfn[u]=++tim;
	dep[u]=dep[father]+1;
	for(int i=head[u];i;i=Next[i]){
		int v=to[i];
		if(v!=father)
			dfs(v,u);
	}
	edf[u]=tim;
	return;
}

int main(void){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;++i)
		scanf("%d",&a[i]);
	for(int i=1;i<n;++i){
		static int u,v;
		scanf("%d%d",&u,&v);
		Add_Edge(u,v);
		Add_Edge(v,u);
	}
	dep[0]=-1;
	dfs(1,0);
	TreeArray::Init(n);
	while(m--){
		static int opt,u,val;
		scanf("%d",&opt);
		switch(opt){
			case 1:{
				scanf("%d%d",&u,&val);
				if(dep[u]&1)
					TreeArray::update(dfn[u],val),TreeArray::update(edf[u]+1,-val);
				else
					TreeArray::update(dfn[u],-val),TreeArray::update(edf[u]+1,val);
				break;
			}
			case 2:{
				scanf("%d",&u);
				int tmp=TreeArray::query(dfn[u]);
				printf("%d\n",a[u]+((dep[u]&1)?tmp:-tmp));
				break;
			}
		}
	}
	return 0;
}