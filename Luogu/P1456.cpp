#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
typedef unsigned long long ull;

const int MAXN=100000+5;

inline void Read(void);
inline void Work(void);

int main(void){
	while(true)
		Read(),Work();
	return 0;
}

int n,m;
int a[MAXN];

inline void Read(void){
	if(scanf("%d",&n)==EOF)
		exit(0);
	for(reg int i=1;i<=n;++i)
		scanf("%d",&a[i]);
	return;
}

struct LeftistTree{
	int dist[MAXN];
	int val[MAXN],root[MAXN];
	int lson[MAXN],rson[MAXN];
	inline void Init(reg int size,reg int a[]){
		dist[0]=-1;
		for(reg int i=1;i<=size;++i){
			val[i]=a[i];
			root[i]=i;
			lson[i]=rson[i]=dist[i]=0;
		}
		return;
	}
	inline int merge(int x,int y){
		if(!x||!y)
			return x|y;
		if(val[x]<val[y])
			swap(x,y);
		rson[x]=merge(rson[x],y);
		if(dist[lson[x]]<dist[rson[x]])
			swap(lson[x],rson[x]);
		root[lson[x]]=root[rson[x]]=root[x]=x;
		dist[x]=dist[rson[x]]+1;
		return x;
	}
	inline int find(reg int x){
		if(x==root[x])
			return x;
		else
			return root[x]=find(root[x]);
	}
};

LeftistTree T;

inline void Work(void){
	T.Init(n,a);
	scanf("%d",&m);
	while(m--){
		static int x,y;
		scanf("%d%d",&x,&y);
		if(T.find(x)==T.find(y))
			puts("-1");
		else{
			reg int rx=T.find(x),ry=T.find(y);
			reg int root_x=T.merge(T.lson[rx],T.rson[rx]),root_y=T.merge(T.lson[ry],T.rson[ry]);
			T.lson[rx]=T.rson[rx]=0,T.lson[ry]=T.rson[ry]=0;
			T.val[rx]>>=1,T.val[ry]>>=1;
			root_x=T.merge(root_x,rx),root_y=T.merge(root_y,ry);
			T.root[root_x]=T.root[root_y]=T.merge(root_x,root_y);
			printf("%d\n",T.val[T.find(T.root[root_x])]);
		}
	}
	return;
}
