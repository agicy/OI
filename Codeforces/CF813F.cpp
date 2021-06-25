#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
static char buf[1<<21],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch)) ch=getchar();
	while(isdigit(ch)) res=10*res+(ch^'0'),ch=getchar();
	return res;
}

const int MAXN=1e5+5;
const int MAXQ=1e5+5;

int n,q;
bool ans[MAXQ];
unordered_map<int,int> M[MAXN];

namespace UnionFind{
	int fa[MAXN<<1],siz[MAXN<<1];
	inline void Init(reg int n){
		for(reg int i=1;i<=n;++i)
			fa[i]=i,siz[i]=1;
		return;
	}
	inline int find(reg int x){
		while(x!=fa[x])
			x=fa[x];
		return x;
	}
	inline pair<int,int> merge(int x,int y){
		x=find(x),y=find(y);
		if(siz[x]>siz[y])
			swap(x,y);
		if(x==y)
			return make_pair(-1,-1);
		else{
			fa[x]=y;
			siz[y]+=siz[x];
			return make_pair(x,y);
		}
	}
}

namespace SegmentTree{
	#define lson ( (k) << 1 )
	#define rson ( (k) << 1 | 1 )
	#define mid ( ( (l) + (r) ) >> 1 )
	struct Node{
		vector<pair<int,int>/**/> V;
		#define V(x) unit[(x)].V
	};
	Node unit[MAXQ<<2];
	inline void update(reg int k,reg int l,reg int r,reg int L,reg int R,const pair<int,int>& p){
		if(L<=l&&r<=R){
			V(k).push_back(p);
			return;
		}
		if(L<=mid)
			update(lson,l,mid,L,R,p);
		if(R>mid)
			update(rson,mid+1,r,L,R,p);
		return;
	}
	stack<pair<int,int>/**/> S;
	inline void print(reg int k,reg int l,reg int r){
		reg unsigned int tmp=S.size();
		reg bool flag=true;
		for(pair<int,int> x:V(k)){
			pair<int,int> res;
			res=UnionFind::merge(x.first,x.second+n);
			if(res.first!=-1)
				S.push(res);
			res=UnionFind::merge(x.first+n,x.second);
			if(res.first!=-1)
				S.push(res);
			if(UnionFind::find(x.first)==UnionFind::find(x.first+n)||UnionFind::find(x.second)==UnionFind::find(x.second+n)){
				flag=false;
				break;
			}
		}
		if(l==r)
			ans[l]=flag;
		else if(flag)
			print(lson,l,mid),print(rson,mid+1,r);
		while(S.size()!=tmp){
			reg int x=S.top().first,y=S.top().second;
			UnionFind::siz[y]-=UnionFind::siz[x];
			UnionFind::fa[x]=x;
			S.pop();
		}
		return;
	}
	#undef lson
	#undef rson
	#undef mid
}

int main(void){
	n=read(),q=read();
	UnionFind::Init(n<<1);
	for(reg int i=1;i<=q;++i){
		static int x,y;
		x=read(),y=read();
		if(M[x][y])
			SegmentTree::update(1,1,q,M[x][y],i-1,make_pair(x,y)),M[x][y]=0;
		else
			M[x][y]=i;
	}
	for(int i=1;i<=n;++i)
		for(auto x:M[i])
			if(x.second)
				SegmentTree::update(1,1,q,x.second,q,make_pair(i,x.first));
	SegmentTree::print(1,1,q);
	for(reg int i=1;i<=q;++i)
		puts(ans[i]?"YES":"NO");
	return 0;
}