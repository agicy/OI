#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define int ll
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(ch<'0'||'9'<ch)ch=getchar();
	while('0'<=ch&&ch<='9')res=10*res+ch-'0',ch=getchar();
	return res;
}

const int MAXN=1e5+5;

int n;
vector<int> V;
int val[MAXN<<1];
int Max=1<<31;

namespace SegmentTree{
	#define lson ( (k) << 1 )
	#define rson ( (k) << 1 | 1 )
	#define mid ( ( (l) + (r) ) >> 1 )
	struct Node{
		int cnt,len;
		#define cnt(x) unit[(x)].cnt
		#define len(x) unit[(x)].len
	};
	Node unit[MAXN<<4];
	inline void pushup(reg int k,reg int l,reg int r){
		if(l==Max&&r==Max)
			return;
		if(cnt(k))
			len(k)=val[r+1]-val[l];
		else
			len(k)=len(lson)+len(rson);
		return;
	}
	inline void update(reg int k,reg int l,reg int r,reg int L,reg int R,reg int val){
		if(L<=l&&r<=R){
			cnt(k)+=val;
			pushup(k,l,r);
			return;
		}
		if(L<=mid)
			update(lson,l,mid,L,R,val);
		if(R>mid)
			update(rson,mid+1,r,L,R,val);
		pushup(k,l,r);
		return;
	}
}

struct Line{
	int x,y1,y2,val;
	inline Line(reg int x=0,reg int y1=0,reg int y2=0,reg int val=0):x(x),y1(y1),y2(y2),val(val){
		return;
	}
	inline bool operator<(const Line& a)const{
		if(x!=a.x)
			return x<a.x;
		else
			return val>a.val;
	}
};

Line L[MAXN<<1];

signed main(void){
	n=read();
	reg ll ans=0;
	for(reg int i=1;i<=n;++i){
		static ll x1,y1,x2,y2;
		x1=read(),y1=read(),x2=read(),y2=read();
		L[2*i-1]=Line(x1,y1,y2,1);
		L[2*i]=Line(x2,y1,y2,-1);
		V.push_back(y1),V.push_back(y2);
	}
	sort(V.begin(),V.end());
	V.erase(unique(V.begin(),V.end()),V.end());
	for(reg int i=1;i<=2*n;++i){
		L[i].y1=lower_bound(V.begin(),V.end(),L[i].y1)-V.begin()+1;
		L[i].y2=lower_bound(V.begin(),V.end(),L[i].y2)-V.begin()+1;
		val[L[i].y1]=V[L[i].y1-1];
		val[L[i].y2]=V[L[i].y2-1];
		Max=max(Max,max(L[i].y1,L[i].y2));
	}
	sort(L+1,L+2*n+1);
	for(reg int i=1;i<n<<1;++i){
		SegmentTree::update(1,1,n<<1,L[i].y1,L[i].y2-1,L[i].val);
		ans+=SegmentTree::unit[1].len*(L[i+1].x-L[i].x);
	}
	printf("%lld\n",ans);
	return 0;
}