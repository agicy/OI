#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar()(p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
#define flush() (fwrite(wbuf,1,wp1,stdout),wp1=0)
#define putchar(c) (wp1==wp2&&(flush(),0),wbuf[wp1++]=c)
static char wbuf[1<<21];int wp1;const int wp2=1<<21;
inline int read(void){
	reg bool f=false;
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))f|=(ch=='-'),ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return f?-res:res;
}

inline void writeln(reg ll x){
	static char buf[32];
	reg int p=-1;
	if(x==0) putchar('0');
	else while(x) buf[++p]=(x%10)^'0',x/=10;
	while(~p) putchar(buf[p--]);
	putchar('\n');
	return;
}

const int MAXN=1e5+5;
const int MAXLOG2A=20;

int n,m;
int a[MAXN];

namespace SegmentTree{
	#define lson ( (k) << 1 )
	#define rson ( (k) << 1 | 1 )
	#define mid ( ( (l) + (r) ) >> 1 )
	struct Node{
		int cnt;
		bool tag;
		#define cnt(x,y) unit[(y)][(x)].cnt
		#define tag(x,y) unit[(y)][(x)].tag
	};
	Node unit[MAXN<<2][MAXLOG2A];
	inline void pushup(reg int id,reg int k){
		cnt(id,k)=cnt(id,lson)+cnt(id,rson);
		return;
	}
	inline void build(reg int k,reg int l,reg int r,reg int a[]){
		if(l==r){
			for(reg int i=0;i<MAXLOG2A;++i)
				cnt(i,k)=(a[l]>>i)&1;
			return;
		}
		build(lson,l,mid,a),build(rson,mid+1,r,a);
		for(reg int i=0;i<MAXLOG2A;++i)
			pushup(i,k);
		return;
	}
	inline void rev(reg int id,reg int k,reg int l,reg int r){
		cnt(id,k)=r-l+1-cnt(id,k);
		tag(id,k)=!tag(id,k);
		return;
	}
	inline void pushdown(reg int id,reg int k,reg int l,reg int r){
		if(tag(id,k)){
			rev(id,lson,l,mid),rev(id,rson,mid+1,r);
			tag(id,k)=false;
		}
		return;
	}
	inline void update(reg int id,reg int k,reg int l,reg int r,reg int L,reg int R){
		if(L<=l&&r<=R){
			rev(id,k,l,r);
			return;
		}
		pushdown(id,k,l,r);
		if(L<=mid)
			update(id,lson,l,mid,L,R);
		if(R>mid)
			update(id,rson,mid+1,r,L,R);
		pushup(id,k);
		return;
	}
	inline int query(reg int id,reg int k,reg int l,reg int r,reg int L,reg int R){
		if(L<=l&&r<=R)
			return cnt(id,k);
		pushdown(id,k,l,r);
		if(L<=mid&&mid<R)
			return query(id,lson,l,mid,L,R)+query(id,rson,mid+1,r,L,R);
		else if(L<=mid)
			return query(id,lson,l,mid,L,R);
		else
			return query(id,rson,mid+1,r,L,R);
	}
	#undef lson
	#undef rson
	#undef mid
}

inline int lowbit(reg int x){
	return x&(-x);
}

map<int,int> lg;

int main(void){
	for(reg int i=0;i<MAXLOG2A;++i)
		lg[1<<i]=i;
	n=read();
	for(reg int i=1;i<=n;++i)
		a[i]=read();
	SegmentTree::build(1,1,n,a);
	m=read();
	while(m--){
		static int opt,l,r,x;
		opt=read(),l=read(),r=read();
		switch(opt){
			case 1:{
				reg ll sum=0;
				for(reg int i=0;i<MAXLOG2A;++i)
					sum+=(1ll*SegmentTree::query(i,1,1,n,l,r))<<i;
				writeln(sum);
				break;
			}
			case 2:{
				x=read();
				for(reg int i=x;i;i^=lowbit(i))
					SegmentTree::update(lg[lowbit(i)],1,1,n,l,r);
				break;
			}
		}
	}
	flush();
	return 0;
}