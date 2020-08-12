#include<bits/stdc++.h>
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

const int MAXN=4e5+5;
const int MAXM=2e5+5;
const int MAXK=1e5+5;

int n,m,k;
int top;
pair<int,int> S[MAXN];
int fa[MAXN<<1],siz[MAXN<<1];
bitset<MAXK> ans;

namespace SegmentTree{
	#define lson ( (k) << 1 )
	#define rson ( (k) << 1 | 1 )
	#define mid ( ( (l) + (r) ) >> 1 )
	struct Node{
		vector<pair<int,int>/**/> V;
		#define V(x) unit[(x)].V
	};
	Node unit[MAXK<<2];
	inline void update(reg int k,reg int l,reg int r,reg int L,reg int R,reg int u,reg int v){
		if(L<=l&&r<=R){
			V(k).push_back(make_pair(u,v));
			return;
		}
		if(L<=mid)
			update(lson,l,mid,L,R,u,v);
		if(R>mid)
			update(rson,mid+1,r,L,R,u,v);
		return;
	}
	inline int find(reg int x){
		while(x!=fa[x])
			x=fa[x];
		return x;
	}
	inline void merge(int x,int y){
		if(siz[x]<siz[y])
			swap(x,y);
		++top;
		S[top]=make_pair(y,siz[y]);
		fa[y]=x;
		siz[x]+=siz[y];
		return;
	}
	inline void solve(reg int k,reg int l,reg int r){
		reg bool flag=true;
		reg int last=top;
		for(reg int i=0,size=V(k).size();i<size;++i){
			reg int p=find(V(k)[i].first),q=find(V(k)[i].second);
			if(p==q){
				flag=false;
				break;
			}
			reg int s=find(V(k)[i].second+n),t=find(V(k)[i].first+n);
			merge(p,s),merge(q,t);
		}
		if(flag){
			if(l==r)
				ans[l]=true;
			else
				solve(lson,l,mid),solve(rson,mid+1,r);
		}
		while(top>last){
			reg int p=S[top].first;
			siz[fa[p]]-=S[top].second;
			fa[p]=p;
			--top;
		}
		return;
	}
}

int main(void){
	n=read(),m=read(),k=read();
	for(reg int i=1;i<=2*n;++i)
		fa[i]=i,siz[i]=1;
	for(reg int i=1;i<=m;++i){
		static int u,v,l,r;
		u=read(),v=read(),l=read(),r=read();
		if(l!=r)
			SegmentTree::update(1,1,k,l+1,r,u,v);
	}
	SegmentTree::solve(1,1,k);
	for(reg int i=1;i<=k;++i)
		puts(ans[i]?"Yes":"No");
	return 0;
}