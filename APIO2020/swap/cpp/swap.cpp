#include "swap.h"
#include <vector>

#include<bits/stdc++.h>
using namespace std;
#define reg register

const int MAXN=1e5+5;
const int MAXM=2e5+5;

namespace UnionFind{
	int fa[MAXN],dep[MAXN];
	bool tag[MAXN];
	inline void Init(reg int n){
		for(reg int i=1;i<=n;++i)
			fa[i]=i,dep[i]=1,tag[i]=false;
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
		if(dep[ra]<dep[rb])
			swap(ra,rb);
		fa[rb]=ra;
		tag[ra]|=tag[rb];
		if(dep[ra]==dep[rb])
			++dep[ra];
		return;
	}
	inline bool search(reg int a,reg int b){
		return find(a)==find(b);
	}
	inline void Set(reg int a){
		reg int r=find(a);
		tag[r]=true;
		return;
	}
}

struct Edge{
	int u,v,w;
	inline Edge(reg int u=0,reg int v=0,reg int w=0):u(u),v(v),w(w){
		return;
	}
	inline bool operator<(const Edge& a)const{
		return w<a.w;
	}
};

int n,m;
Edge E[MAXM];
bool task1=false;
bool task2=false;
int deg[MAXN],dis[MAXN],val[MAXN];

void init(int N, int M,std::vector<int> u, std::vector<int> v, std::vector<int> w) {
	n=N,m=M;
	reg bool ueq0=true;
	int Max=0;
	for(reg int i=0;i<m;++i){
		++deg[u[i]],++deg[v[i]];
		if(u[i]!=0)
			ueq0=false;
		Max=max(Max,max(deg[u[i]],deg[v[i]]));
	}
	if(Max<=2)
		task1=true;
	if(ueq0&&M==N-1){
		task2=true;
		reg int len=0;
		for(reg int i=0;i<M;++i){
			val[v[i]]=w[i];
			dis[++len]=w[i];
		}
		sort(dis+1,dis+len+1);
	}
	for(reg int i=0;i<M;++i)
		E[i+1]=Edge(u[i]+1,v[i]+1,w[i]);
	sort(E+1,E+m+1);
	return;
}

int L,R;

inline bool check(reg int mid){
	memset(deg,0,sizeof(deg));
	UnionFind::Init(n);
	for(reg int i=1;i<=m;++i){
		if(E[i].w>mid)
			break;
		reg int u=E[i].u,v=E[i].v;
		if(UnionFind::search(u,v))
			UnionFind::Set(u);
		++deg[u],++deg[v];
		if(deg[u]>=3||deg[v]>=3)
			UnionFind::Set(u),UnionFind::Set(v);
		UnionFind::merge(u,v);
	}
	return UnionFind::search(L,R)&&(UnionFind::tag[UnionFind::find(L)]);
}

inline int find(reg int l,reg int r){
	if(l==r)
		return l;
	reg int mid=(l+r)>>1;
	reg int tmp1=check(mid);
	reg int tmp2=check(mid+1);
	if(tmp1)
		return find(l,mid);
	else if(!tmp1&&tmp2)
		return mid+1;
	else
		return find(mid+1,r);
}

int getMinimumFuelCapacity(int x,int y){
	if(task1){
		if(n==m){
			return E[m].w;
		}
		else
			return -1;
	}
	if(task2){
		int ans=max(dis[1],max(dis[2],dis[3]));
		ans=max(ans,max(val[x],val[y]));
		return ans;
	}
	L=x+1,R=y+1;
	reg int A=1e9+1;
	reg int tmp=find(0,1e9+1);
	if(tmp==A)
		return -1;
	return tmp;
}