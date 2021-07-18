#pragma GCC optimize("Ofast")
#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

bool st;

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

namespace SegmentTree{
	#define lson ( (k) << 1 )
	#define rson ( (k) << 1 | 1 )
	#define mid ( ( (l) + (r) ) >> 1 )
	struct Node{
		int cnt;
		int tag;
		#define cnt(x) unit[(x)].cnt
		#define tag(x) unit[(x)].tag
	};
	Node unit[MAXN<<2];
	inline void build(reg int k,reg int l,reg int r){
		tag(k)=cnt(k)=0;
		if(l==r)
			return;
		build(lson,l,mid),build(rson,mid+1,r);
		return;
	}
	inline void pushup(reg int k,reg int l,reg int r){
		if(tag(k))
			cnt(k)=r-l+1;
		else if(l!=r)
			cnt(k)=cnt(lson)+cnt(rson);
		else
			cnt(k)=0;
		return;
	}
	inline void update(reg int k,reg int l,reg int r,reg int L,reg int R,reg int val){
		if(L<=l&&r<=R){
			tag(k)+=val;
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
	#undef lson
	#undef rson
	#undef mid
}

struct Event{
	int x,l,r,val;
	inline Event(void){return;}
	inline Event(const int& x,const int& l,const int& r,const int& val):x(x),l(l),r(r),val(val){return;}
	inline bool operator<(const Event& a)const{return x<a.x;}
};

vector<Event> E[5][5];

inline ll solve(reg int _x,reg int _y){
	reg int X=(n+4-_x)/5,Y=(n+4-_y)/5;
	if(!X||!Y)
		return 0;
	reg ll res=0;
	SegmentTree::build(1,0,Y-1);
	sort(E[_x][_y].begin(),E[_x][_y].end());
	for(reg int i=0,ptr=0;i<=X;++i){
		while(ptr<(int)E[_x][_y].size()&&E[_x][_y][ptr].x<=i){
			SegmentTree::update(1,0,Y-1,E[_x][_y][ptr].l,E[_x][_y][ptr].r,E[_x][_y][ptr].val);
			++ptr;
		}
		res+=SegmentTree::unit[1].cnt;
	}
	return res;
}

bool ed;

int main(void){
	n=read(),q=read();
	for(reg int i=1;i<=q;++i){
		static int x1,y1,x2,y2;
		x1=read()-1,y1=read()-1,x2=read()-1,y2=read()-1;
		for(reg int i=x1;i<=min(x1+4,x2);++i)
			for(reg int j=y1;j<=min(y1+4,y2);++j)
				if(((j-y1)%5*(x2-x1+1)%5+(i-x1))%5==0){
					reg int idx=i%5,idy=j%5;
					int lefx=i/5,rigx=lefx+(x2-i)/5;
					int lefy=j/5,rigy=lefy+(y2-j)/5;
					if(lefx<=rigx&&lefy<=rigy){
						E[idx][idy].push_back(Event(lefx,lefy,rigy,1));
						E[idx][idy].push_back(Event(rigx+1,lefy,rigy,-1));
					}
				}
	}
	reg ll ans=0;
	for(reg int i=0;i<5;++i)
		for(reg int j=0;j<5;++j)
			ans+=solve(i,j);
	printf("%lld\n",ans);
	fprintf(stderr,"%.3lf s\n",1.0*clock()/CLOCKS_PER_SEC);
	fprintf(stderr,"%.3lf MiB\n",(&ed-&st)/1048576.0);
	return 0;
}