#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

const int MAXN=1e5+5;
const int MAXM=1e5+5;

int n,m;

namespace UnionFind{
	int fa[MAXN];
	inline void Init(reg int n){
		for(reg int i=1;i<=n;++i)
			fa[i]=i;
		return;
	}
	inline int find(reg int x){
		if(x==fa[x])
			return x;
		else
			return fa[x]=find(fa[x]);
	}
	inline void merge(reg int a,reg int b){
		reg int ra=find(a),rb=find(b);
		if(ra!=rb)
			fa[rb]=ra;
		return;
	}
	inline bool search(reg int a,reg int b){
		return find(a)==find(b);
	}
}

int main(void){
	scanf("%d%d",&n,&m);
	UnionFind::Init(n);
	while(m--){
		static char ch;
		static int a,b;
		cin>>ch>>a>>b;
		if(ch=='M')
			UnionFind::merge(a,b);
		else if(ch=='Q')
			puts(UnionFind::search(a,b)?"Yes":"No");
	}
	return 0;
}