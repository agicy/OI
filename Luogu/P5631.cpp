#include<bits/stdc++.h>
#pragma GCC optimize(2)
#pragma GCC optimize(3)
#pragma GCC optimize("Ofast")
#pragma GCC optimize("inline")
#pragma GCC optimize("-fgcse")
#pragma GCC optimize("-fgcse-lm")
#pragma GCC optimize("-fipa-sra")
#pragma GCC optimize("-ftree-pre")
#pragma GCC optimize("-ftree-vrp")
#pragma GCC optimize("-fpeephole2")
#pragma GCC optimize("-ffast-math")
#pragma GCC optimize("-fsched-spec")
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("-falign-jumps")
#pragma GCC optimize("-falign-loops")
#pragma GCC optimize("-falign-labels")
#pragma GCC optimize("-fdevirtualize")
#pragma GCC optimize("-fcaller-saves")
#pragma GCC optimize("-fcrossjumping")
#pragma GCC optimize("-fthread-jumps")
#pragma GCC optimize("-funroll-loops")
#pragma GCC optimize("-fwhole-program")
#pragma GCC optimize("-freorder-blocks")
#pragma GCC optimize("-fschedule-insns")
#pragma GCC optimize("inline-functions")
#pragma GCC optimize("-ftree-tail-merge")
#pragma GCC optimize("-fschedule-insns2")
#pragma GCC optimize("-fstrict-aliasing")
#pragma GCC optimize("-fstrict-overflow")
#pragma GCC optimize("-falign-functions")
#pragma GCC optimize("-fcse-skip-blocks")
#pragma GCC optimize("-fcse-follow-jumps")
#pragma GCC optimize("-fsched-interblock")
#pragma GCC optimize("-fpartial-inlining")
#pragma GCC optimize("no-stack-protector")
#pragma GCC optimize("-freorder-functions")
#pragma GCC optimize("-findirect-inlining")
#pragma GCC optimize("-frerun-cse-after-loop")
#pragma GCC optimize("inline-small-functions")
#pragma GCC optimize("-finline-small-functions")
#pragma GCC optimize("-ftree-switch-conversion")
#pragma GCC optimize("-foptimize-sibling-calls")
#pragma GCC optimize("-fexpensive-optimizations")
#pragma GCC optimize("-funsafe-loop-optimizations")
#pragma GCC optimize("inline-functions-called-once")
#pragma GCC optimize("-fdelete-null-pointer-checks")
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(ch<'0'||'9'<ch)ch=getchar();
	while('0'<=ch&&ch<='9')res=10*res+ch-'0',ch=getchar();
	return res;
}

const int MAXN=1000000+5;
const int MAXM=2000000+5;
const int MAXW=100000+5;

int n,m;
int u[MAXM],v[MAXM],w[MAXM];

namespace SegmentTree{
	namespace UnionFind{
		int cnt;
		int fa[MAXN],size[MAXN];
		inline void Init(reg int S){
			cnt=S;
			for(reg int i=1;i<=S;++i)
				fa[i]=i;
			return;
		}
		inline int find(reg int x){
			if(x==fa[x])
				return x;
			else
				return find(fa[x]);
		}
		stack<int> S;
		inline void merge(reg int a,reg int b){
			int ra=find(a),rb=find(b);
			if(ra!=rb){
				--cnt;
				if(size[rb]>size[ra])
					swap(ra,rb);
				S.push(rb);
				fa[rb]=ra;
				size[ra]+=size[rb];
			}
			return;
		}
		inline void del(reg int tag){
			while(tag<(int)S.size()){
				++cnt;
				reg int x=S.top();
				S.pop();
				size[fa[x]]-=size[x];
				fa[x]=x;
			}
			return;
		}
	}
	#define lson ( (k) << 1 )
	#define rson ( (k) << 1 | 1 )
	#define mid ( ( (l) + (r) ) >> 1 )
	vector<pair<int,int>/**/> V[MAXW<<2];
	inline void Update(reg int k,reg int l,reg int r,reg int L,reg int R,const pair<int,int> P){
		if(r<L||R<l)
			return;
		if(L<=l&&r<=R){
			V[k].push_back(P);
			return;
		}
		if(L<=mid)
			Update(lson,l,mid,L,R,P);
		if(R>mid)
			Update(rson,mid+1,r,L,R,P);
		return;
	}
	inline void Query(reg int k,reg int l,reg int r){
		reg int tag=UnionFind::S.size();
		for(reg int i=0,size=V[k].size();i<size;++i){
			reg int x=V[k][i].first,y=V[k][i].second;
			UnionFind::merge(x,y);
		}
		if(l==r){
			if(UnionFind::cnt==1){
				printf("%d\n",l);
				exit(0);
			}
			UnionFind::del(tag);
			return;
		}
		Query(lson,l,mid);
		Query(rson,mid+1,r);
		UnionFind::del(tag);
		return;
	}
	#undef lson
	#undef rson
	#undef mid
}

int main(void){
	n=read(),m=read();
	int Max=0;
	for(reg int i=1;i<=m;++i){
		u[i]=read(),v[i]=read(),w[i]=read();
		Max=max(Max,w[i]+1);
	}
	for(reg int i=1;i<=m;++i){
		SegmentTree::Update(1,0,Max,0,w[i]-1,make_pair(u[i],v[i]));
		SegmentTree::Update(1,0,Max,w[i]+1,Max,make_pair(u[i],v[i]));
	}
	SegmentTree::UnionFind::Init(n);
	SegmentTree::Query(1,0,Max);
	return 0;
}