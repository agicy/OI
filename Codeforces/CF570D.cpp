#include<bits/stdc++.h>
using namespace std;
#define reg register

const int MAXN=500000+5;

struct Querys{
	int id,dep;
	inline Querys(reg int id=0,reg int dep=0):id(id),dep(dep){
		return;
	}
};

int n,m;
int cnt,head[MAXN],to[MAXN],Next[MAXN];

inline void Add_Edge(reg int u,reg int v){
	Next[++cnt]=head[u];
	to[cnt]=v;
	head[u]=cnt;
	return;
}

vector<int> temp[MAXN];
vector<Querys> Q[MAXN];

int tot[MAXN],ans[MAXN];
char str[MAXN];

inline void DFS(reg int ID,reg int dep){
	tot[dep]^=(1<<(str[ID]-'a'));
	for(reg int i=0,size=Q[ID].size();i<size;++i)
		temp[ID].push_back(tot[Q[ID][i].dep]);
	for(reg int i=head[ID];i;i=Next[i])
		DFS(to[i],dep+1);
	for(reg int i=0,size=Q[ID].size();i<size;++i)
		ans[Q[ID][i].id]=(temp[ID][i]^tot[Q[ID][i].dep]);
	return;
}

inline int lowbit(reg int x){
	return x&(-x);
}

int main(void){
	scanf("%d%d",&n,&m);
	for(reg int i=2;i<=n;++i){
		static int fa;
		scanf("%d",&fa);
		Add_Edge(fa,i);
	}
	scanf("%s",str+1);
	for(reg int i=1;i<=m;++i){
		static int v,h;
		scanf("%d%d",&v,&h);
		Q[v].push_back(Querys(i,h));
	}
	DFS(1,1);
	for(reg int i=1;i<=m;++i)
		puts(ans[i]==lowbit(ans[i])?"Yes":"No");
	return 0;
}