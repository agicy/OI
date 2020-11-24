#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg bool f=false;
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))f|=(ch=='-'),ch=getchar();
	while(isdigit(ch))res=10*res+ch-'0',ch=getchar();
	return f?-res:res;
}

inline void cMax(reg int &a,reg int b){
	if(a<b)
		a=b;
	return;
}

const int MAXN=1e4+5;

struct Node{
	int x,y1,y2,val;
	inline Node(reg int x=0,reg int y1=0,reg int y2=0,reg int val=0):x(x),y1(y1),y2(y2),val(val){
		return;
	}
	inline bool operator<(const Node& a)const{
		return x==a.x?val<a.val:x<a.x;
	}
};

namespace SegmentTree{
	#define lson ( (k) << 1 )
	#define rson ( (k) << 1 | 1 )
	#define mid ( ( (l) + (r) ) >> 1 )
	struct Node{
		int val,tag;
		#define val(x) unit[(x)].val
		#define tag(x) unit[(x)].tag
	};
	Node unit[MAXN<<4];
	inline void pushup(reg int k){
		val(k)=max(val(lson),val(rson));
		return;
	}
	inline void add(reg int k,reg int v){
		val(k)+=v,tag(k)+=v;
		return;
	}
	inline void pushdown(reg int k){
		if(tag(k)){
			add(lson,tag(k));
			add(rson,tag(k));
			tag(k)=0;
		}
		return;
	}
	inline void update(reg int k,reg int l,reg int r,reg int L,reg int R,reg int v){
		if(L<=l&&r<=R){
			add(k,v);
			return;
		}
		pushdown(k);
		if(L<=mid)
			update(lson,l,mid,L,R,v);
		if(R>mid)
			update(rson,mid+1,r,L,R,v);
		pushup(k);
		return;
	}
	inline int query(reg int k,reg int l,reg int r,reg int L,reg int R){
		if(L<=l&&r<=R)
			return val(k);
		pushdown(k);
		if(L<=mid&&mid<R)
			return max(query(lson,l,mid,L,R),query(rson,mid+1,r,L,R));
		else if(L<=mid)
			return query(lson,l,mid,L,R);
		else
			return query(rson,mid+1,r,L,R);
	}
	#undef lson
	#undef rson
	#undef mid
};

int n,W,H;
int x[MAXN],y[MAXN],a[MAXN];
int tot;
Node l[MAXN<<1];
vector<int> Vx,Vy;

int main(void){
	n=read(),W=read(),H=read();
	for(reg int i=1;i<=n;++i)
		x[i]=read(),y[i]=read(),a[i]=read();
	reg int tot=0;
	Vx.clear(),Vy.clear();
	for(reg int i=1;i<=n;++i){
		Vx.push_back(x[i]),Vx.push_back(x[i]-W+1);
		Vy.push_back(y[i]),Vy.push_back(y[i]-H+1);
	}
	sort(Vx.begin(),Vx.end());
	sort(Vy.begin(),Vy.end());
	Vx.erase(unique(Vx.begin(),Vx.end()),Vx.end());
	Vy.erase(unique(Vy.begin(),Vy.end()),Vy.end());
	reg int size=Vy.size()+1;
	for(reg int i=1;i<=n;++i){
		reg int tx1=lower_bound(Vx.begin(),Vx.end(),x[i]-W+1)-Vx.begin()+1;
		reg int tx2=lower_bound(Vx.begin(),Vx.end(),x[i])-Vx.begin()+1;
		reg int ty1=lower_bound(Vy.begin(),Vy.end(),y[i]-H+1)-Vy.begin()+1;
		reg int ty2=lower_bound(Vy.begin(),Vy.end(),y[i])-Vy.begin()+1;
		l[++tot]=Node(tx1,ty1,ty2,a[i]),l[++tot]=Node(tx2+1,ty1,ty2,-a[i]);
	}
	int ans=0;
	sort(l+1,l+tot+1);
	for(reg int i=1;i<=tot;++i){
		SegmentTree::update(1,1,size,l[i].y1,l[i].y2,l[i].val);
		cMax(ans,SegmentTree::query(1,1,size,1,size));
	}
	printf("%d\n",ans);
	return 0;
}