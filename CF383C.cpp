#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

const int MAXN=2e5+5;

struct TreeArray{
	inline int lowbit(reg int x){
		return x&(-x);
	}
	int n,unit[MAXN];
	inline void Init(reg int s){
		n=s;
		memset(unit,0,sizeof(unit));
		return;
	}
	inline void update(reg int id,reg int val){
		for(reg int i=id;i<=n;i+=lowbit(i))
			unit[i]+=val;
		return;
	}
	inline int query(reg int id){
		reg int res=0;
		for(reg int i=id;i;i-=lowbit(i))
			res+=unit[i];
		return res;
	}
};

int n,m;
int a[MAXN];
int cnt,head[MAXN],to[MAXN<<1],Next[MAXN<<1];

inline void Add_Edge(reg int u,reg int v){
	Next[++cnt]=head[u];
	to[cnt]=v;
	head[u]=cnt;
	return;
}

int dep[MAXN];
int dfn[MAXN],end[MAXN];

inline void dfs(reg int u,reg int father){
	dfn[u]=++tim;
	dep[u]=dep[father]+1;
	for(reg int i=head[u];i;i=Next[i]){
		reg int v=to[i];
		if(v!=father)
			dfs(v,u);
	}
	end[u]=tim;
	return;
}

int main(void){
	scanf("%d%d",&n,&m);
	for(reg int i=1;i<=n;++i)
		scanf("%d",&a[i]);
	for(reg int i=1;i<n;++i){
		static int u,v;
		scanf("%d%d",&u,&v);
		Add_Edge(u,v);
		Add_Edge(v,u);
	}
	
	return 0;
}