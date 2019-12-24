#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
typedef unsigned long long ull;

const int MAXN=10000+5;
const int MAXD=10000+5;

struct Node{
	int w,t;
	void Read(void){
		scanf("%d%d",&w,&t);
		return;
	}
	bool operator<(const Node &a)const{
		return w!=a.w?w>a.w:t<a.t;
	}
};

struct UnionFind{
	int ID[MAXD];
	inline void Init(reg int n){
		for(reg int i=1;i<=n;++i)
			ID[i]=i;
		return;
	}
	inline int find(reg int x){
		return (x==ID[x])?x:ID[x]=find(ID[x]);
	}
};

int n;
Node E[MAXN];
UnionFind S;

inline void Work(void);

int main(void){
	while(scanf("%d",&n)!=EOF){
		for(reg int i=1;i<=n;++i)
			E[i].Read();
		Work();
	}
	return 0;
}

inline void Work(void){
	reg int ans=0;
	sort(E+1,E+n+1);
	S.Init(E[1].w);
	for(reg int i=1;i<=n;++i)
		if(S.find(E[i].t)!=0){
			ans+=E[i].w;
			S.ID[S.find(E[i].t)]=S.ID[S.find(E[i].t)]-1;
		}
	printf("%d\n",ans);
	return;
}
