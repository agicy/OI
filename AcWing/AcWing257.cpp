#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int MAXN=2e4+5;
const int MAXM=1e5+5;

struct Edge{
	int u,v,w;
	inline Edge(int u=0,int v=0,int w=0):u(u),v(v),w(w){
		return;
	}
	inline bool operator<(const Edge& a)const{
		return w>a.w;
	}
};

int n,m;
int fa[MAXN];
int e[MAXN];
Edge E[MAXM];

inline int find(int x){
	if(x==fa[x])
		return x;
	else
		return fa[x]=find(fa[x]);
}

inline void merge(int a,int b){
	int ra=find(a),rb=find(b);
	if(ra!=rb)
		fa[rb]=ra;
	return;
}

inline bool search(int a,int b){
	return find(a)==find(b);
}

int main(void){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;++i)
		fa[i]=i;
	for(int i=1;i<=m;++i){
		static int a,b,c;
		scanf("%d%d%d",&a,&b,&c);
		E[i]=Edge(a,b,c);
	}
	sort(E+1,E+m+1);
	for(int i=1;i<=m;++i){
		if(!search(E[i].u,E[i].v)){
			if(!e[E[i].u])
				e[E[i].u]=E[i].v;
			else
				merge(e[E[i].u],E[i].v);
			if(!e[E[i].v])
				e[E[i].v]=E[i].u;
			else
				merge(e[E[i].v],E[i].u);
		}
		else{
			printf("%d\n",E[i].w);
			return 0;
		}
	}
	puts("0");
	return 0;
}