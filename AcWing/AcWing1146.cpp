#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int MAXN=300+5;

struct Edge{
	int u,v,w;
	inline Edge(int u=0,int v=0,int w=0):u(u),v(v),w(w){
		return;
	}
	inline bool operator<(const Edge& a)const{
		return w<a.w;
	}
};

int n;
Edge E[MAXN*MAXN+MAXN];
int fa[MAXN];

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
	scanf("%d",&n);
	int s=n+1,tot=0;
	for(int i=1;i<=n;++i){
		static int v;
		scanf("%d",&v);
		E[++tot]=Edge(i,s,v);
	}
	for(int i=1;i<=n;++i)
		for(int j=1;j<=n;++j){
			static int p;
			scanf("%d",&p);
			if(i<j)
				E[++tot]=Edge(i,j,p);
		}
	sort(E+1,E+tot+1);
	for(int i=1;i<=s;++i)
		fa[i]=i;
	int ans=0;
	for(int i=1;i<=tot;++i)
		if(!search(E[i].u,E[i].v)){
			ans+=E[i].w;
			merge(E[i].u,E[i].v);
		}
	printf("%d\n",ans);
	return 0;
}