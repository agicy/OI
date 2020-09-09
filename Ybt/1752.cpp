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

const int MAXN=1e6+5;

struct Node{
	int l,r;
	inline Node(reg int l=0,reg int r=0):l(l),r(r){
		return;
	}
};

namespace SegmentTree{
	#define lson ( (k) << 1 )
	#define rson ( (k) << 1 | 1 )
	#define mid ( ( (l) + (r) ) >> 1 )
	struct Node{
		int len;
		int lMax,rMax,Max;
		int tag;
		#define len(x) unit[(x)].len
		#define lMax(x) unit[(x)].lMax
		#define rMax(x) unit[(x)].rMax
		#define Max(x) unit[(x)].Max
		#define tag(x) unit[(x)].tag
	};
	Node unit[MAXN<<2];
	inline void build(reg int k,reg int l,reg int r){
		len(k)=lMax(k)=rMax(k)=Max(k)=r-l+1;
		if(l==r)
			return;
		build(lson,l,mid),build(rson,mid+1,r);
		return;
	}
	inline void update(reg int k){
		if(tag(k))
			lMax(k)=rMax(k)=Max(k)=0;
		else if(len(k)==1)
			lMax(k)=rMax(k)=Max(k)=1;
		else{
			lMax(k)=(lMax(lson)==len(lson))?len(lson)+lMax(rson):lMax(lson);
			rMax(k)=(rMax(rson)==len(rson))?len(rson)+rMax(lson):rMax(rson);
			Max(k)=max(rMax(lson)+lMax(rson),max(Max(lson),Max(rson)));
		}
		return;
	}
	inline void update(reg int k,reg int l,reg int r,reg int L,reg int R,reg int val){
		if(L<=l&&r<=R){
			tag(k)+=val;
			update(k);
			return;
		}
		if(L<=mid)
			update(lson,l,mid,L,R,val);
		if(R>mid)
			update(rson,mid+1,r,L,R,val);
		update(k);
		return;
	}
	#undef lson
	#undef rson
	#undef mid
}

int n,m,p;
vector<Node> add[MAXN],del[MAXN];

int main(void){
	n=read(),m=read(),p=read();
	for(reg int i=1;i<=p;++i){
		static int x1,y1,x2,y2;
		x1=read(),y1=read(),x2=read(),y2=read();
		add[x1].push_back(Node(y1,y2));
		del[x2].push_back(Node(y1,y2));
	}
	int ans=0;
	SegmentTree::build(1,1,m);
	for(reg int r=1,l=1;r<=n;++r){
		for(reg int i=0,siz=add[r].size();i<siz;++i)
			SegmentTree::update(1,1,m,add[r][i].l,add[r][i].r,1);
		ans=max(ans,min(SegmentTree::unit[1].Max,r-l+1));
		while(r-l+1>SegmentTree::unit[1].Max){
			for(reg int i=0,siz=del[l].size();i<siz;++i)
				SegmentTree::update(1,1,m,del[l][i].l,del[l][i].r,-1);
			++l;
		}
	}
	printf("%d\n",ans);
	return 0;
}