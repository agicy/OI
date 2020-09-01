#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int MAXN=200+5;

int n,m;
int id[MAXN][MAXN];

namespace UnionFind{
	int fa[MAXN*MAXN];
	inline void Init(int n){
		for(int i=1;i<=n;++i)
			fa[i]=i;
		return;
	}
	inline int find(int x){
		if(x==fa[x])
			return x;
		else
			return fa[x]=find(fa[x]);
	}
	inline void merge(int a,int b){
		int ra=find(a),rb=find(b);
		fa[rb]=ra;
		return;
	}
	inline bool search(int a,int b){
		return find(a)==find(b);
	}
}

int main(void){
	scanf("%d%d",&n,&m);
	int tot=0;
	for(int i=1;i<=n;++i)
		for(int j=1;j<=n;++j)
			id[i][j]=++tot;
	UnionFind::Init(n*n);
	for(int i=1;i<=m;++i){
		static int x,y;
		scanf("%d%d",&x,&y);
		int a=id[x][y];
		static char opt;
		cin>>opt;
		int b=a+(opt=='D'?n:1);
		if(UnionFind::search(a,b)){
			printf("%d\n",i);
			return 0;
		}
		UnionFind::merge(a,b);
	}
	puts("draw");
	return 0;
}