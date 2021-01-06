#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return res;
}

const int MAXN=1e5+5;
const int MAXM=2e5+5;
const int MAXK=1e5+5;

struct Edge{
	int u,v;
};

int n,m,k;
Edge E[MAXM];
vector<int> V[MAXM];

namespace SegmentTree{
	#define lson ( (k) << 1 )
	#define rson ( (k) << 1 | 1 )
	#define mid ( ( (l) + (r) ) >> 1 )
	struct Node{
		vector<int> V;
		#define V(x) unit[(x)].V
	};
	Node unit[MAXK<<2];
	inline void update(reg int k,reg int l,reg int r,reg int L,reg int R,const int& id){
		if(L<=l&&r<=R){
			V(k).push_back(id);
			return;
		}
		if(L<=mid&&mid<R)
			update(lson,l,mid,L,R,id),update(rson,mid+1,r,L,R,id);
		else if(L<=mid)
			update(lson,l,mid,L,R,id);
		else
			update(rson,mid+1,r,L,R,id);
		return;
	}
	namespace UnionFind{
		int fa[MAXN],siz[MAXN],dep[MAXN];
		inline void Init(reg int n){
			for(reg int i=1;i<=n;++i)
				fa[i]=i,siz[i]=dep[i]=1;
			return;
		}
		inline int find(reg int x){
			while(x!=fa[x])
				x=fa[x];
			return x;
		}
	}
	struct Chunk{
		int rb,f,siz;
		inline Chunk(reg int rb=0,reg int f=0,reg int siz=0):rb(rb),f(f),siz(siz){
			return;
		}
	};
	int top;
	Chunk S[MAXM];
	inline void Do(reg int id,reg bool& flag){
		using namespace UnionFind;
		int ra=find(E[id].u),rb=find(E[id].v);
		if(ra==rb)
			return;
		if(dep[ra]<dep[rb])
			swap(ra,rb);
		S[++top]=Chunk(rb,dep[ra]==dep[rb],siz[rb]);
		fa[rb]=ra,dep[ra]+=(dep[ra]==dep[rb]),siz[ra]+=siz[rb];
		if(siz[ra]==n)
			flag=true;
		return;
	}
	inline void unDo(const Chunk& x){
		using namespace UnionFind;
		reg int &rb=fa[x.rb];
		dep[rb]-=x.f,siz[rb]-=x.siz,rb=x.rb;
		return;
	}
	inline void print(reg int k,reg int l,reg int r,bool flag){
		reg int tmp=top;
		for(vector<int>::iterator it=V(k).begin();it!=V(k).end();++it)
			Do(*it,flag);
		if(l==r)
			puts(flag?"Connected":"Disconnected");
		else
			print(lson,l,mid,flag),print(rson,mid+1,r,flag);
		while(top!=tmp)
			unDo(S[top--]);
		return;
	}
	inline void Solve(void){
		UnionFind::Init(n);
		print(1,1,k,false);
		return;
	}
	#undef lson
	#undef rson
	#undef mid
}

int main(void){
	n=read(),m=read();
	for(reg int i=1;i<=m;++i)
		E[i].u=read(),E[i].v=read();
	k=read();
	for(reg int i=1;i<=m;++i)
		V[i].push_back(0);
	for(int i=1;i<=k;++i)
		for(reg int c=read();c;--c)
			V[read()].push_back(i);
	for(reg int i=1;i<=m;++i)
		V[i].push_back(k+1);
	for(int i=1;i<=m;++i)
		for(reg int j=1,siz=V[i].size();j<siz;++j)
			if(V[i][j-1]+1<=V[i][j]-1)
				SegmentTree::update(1,1,k,V[i][j-1]+1,V[i][j]-1,i);
	SegmentTree::Solve();
	return 0;
}