#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int MAXN=1e5+5;

int n,m;

namespace UnionFind{
	int fa[MAXN],siz[MAXN];
	inline void Init(int n){
		for(int i=1;i<=n;++i)
			fa[i]=i,siz[i]=1;
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
		if(ra!=rb){
			fa[rb]=ra;
			siz[ra]+=siz[rb];
		}
		return;
	}
	inline bool search(int a,int b){
		return find(a)==find(b);
	}
}

int main(void){
	scanf("%d%d",&n,&m);
	UnionFind::Init(n);
	while(m--){
		static string s;
		static int a,b;
		cin>>s>>a;
		if(s=="C"){
			cin>>b;
			UnionFind::merge(a,b);
		}
		else if(s=="Q1"){
			cin>>b;
			puts(UnionFind::search(a,b)?"Yes":"No");
		}
		else if(s=="Q2")
			printf("%d\n",UnionFind::siz[UnionFind::find(a)]);
	}
	return 0;
}