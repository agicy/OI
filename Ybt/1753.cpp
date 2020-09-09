#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

inline int read(void){
	static int tmp;
	scanf("%d",&tmp);
	return tmp;
}

const int MAXN=2e5+5;

struct Node{
	int opt,l,r;
	inline Node(reg int opt=0,reg int l=0,reg int r=0):opt(opt),l(l),r(r){
		return;
	}
};

int n;
Node a[MAXN];
vector<int> V;

int fa[MAXN];
int le[MAXN],ri[MAXN];

inline int find(reg int x){
	if(x==fa[x])
		return x;
	else
		return fa[x]=find(fa[x]);
}

namespace SegmentTree{
	#define lson ( (k) << 1 )
	#define rson ( (k) << 1 | 1 )
	#define mid ( ( (l) + (r) ) >> 1 )
	struct Node{
		vector<int> V;
		#define V(x) unit[(x)].V
	};
	Node unit[MAXN<<2];
	inline void merge(reg int k,reg int l,reg int r,reg int pos,reg int id){
		for(reg int i=0,siz=V(k).size();i<siz;++i){
			reg int rx=find(V(k)[i]),ry=find(id);
			fa[rx]=ry;
			le[ry]=min(le[ry],le[rx]);
			ri[ry]=max(ri[ry],ri[rx]);
		}
		V(k).clear();
		if(l==r)
			return;
		if(pos<=mid)
			merge(lson,l,mid,pos,id);
		else
			merge(rson,mid+1,r,pos,id);
		return;
	}
	inline void update(reg int k,reg int l,reg int r,reg int L,reg int R,int id){
		if(L==l&&r==R){
			V(k).push_back(id);
			return;
		}
		if(R<=mid)
			update(lson,l,mid,L,R,id);
		else if(mid<L)
			update(rson,mid+1,r,L,R,id);
		else
			update(lson,l,mid,L,mid,id),update(rson,mid+1,r,mid+1,R,id);
		return;
	}
	#undef lson
	#undef rson
	#undef mid
}

int main(void){
	n=read();
	for(reg int i=1;i<=n;++i){
		static int opt,l,r;
		opt=read(),l=read(),r=read();
		a[i]=Node(opt,l,r);
		if(opt==1)
			V.push_back(l),V.push_back(r);
	}
	sort(V.begin(),V.end());
	V.erase(unique(V.begin(),V.end()),V.end());
	for(reg int i=1;i<=n;++i)
		if(a[i].opt==1){
			a[i].l=lower_bound(V.begin(),V.end(),a[i].l)-V.begin()+1;
			a[i].r=lower_bound(V.begin(),V.end(),a[i].r)-V.begin()+1;
		}
	reg int m=V.size();
	reg int tot=0;
	for(reg int i=1;i<=n;++i)
		if(a[i].opt==1){
			++tot;
			fa[tot]=tot;
			le[tot]=a[i].l,ri[tot]=a[i].r;
			SegmentTree::merge(1,1,m,a[i].l,tot);
			SegmentTree::merge(1,1,m,a[i].r,tot);
			reg int x=find(tot);
			if(le[x]+1<=ri[x]-1)
				SegmentTree::update(1,1,m,le[x]+1,ri[x]-1,tot);
		}
		else{
			reg int x=a[i].l,y=a[i].r;
			reg int rx=find(x),ry=find(y);
			if(rx==ry||(le[ry]<le[rx]&&le[rx]<ri[ry])||(le[ry]<ri[rx]&&ri[rx]<ri[ry]))
				puts("YES");
			else
				puts("NO");
		}
	return 0;
}