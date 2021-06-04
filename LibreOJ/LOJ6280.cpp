#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
static char buf[1<<21],*p1=buf,*p2=buf;
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
	if(x<0) x=-x,putchar('-');
	if(!x) putchar('0');
	else while(x) buf[++p]=(x%10)^'0',x/=10;
	while(~p) putchar(buf[p--]);
	putchar('\n');
	return;
}

const int MAXN=5e4+5;

int n;
int a[MAXN];

namespace SegmentTree{
	#define lson ( (k) << 1 )
	#define rson ( (k) << 1 | 1 )
	#define mid ( ( (l) + (r) ) >> 1 )
	struct Node{
		ll sum,tAdd;
		#define sum(x) unit[(x)].sum
		#define tAdd(x) unit[(x)].tAdd
	};
	Node unit[MAXN<<2];
	inline void pushup(reg int k){
		sum(k)=sum(lson)+sum(rson);
		return;
	}
	inline void build(reg int k,reg int l,reg int r,reg int a[]){
		if(l==r){
			sum(k)=a[l];
			return;
		}
		build(lson,l,mid,a),build(rson,mid+1,r,a);
		pushup(k);
		return;
	}
	inline void add(reg int k,reg int l,reg int r,reg int val){
		sum(k)+=1ll*(r-l+1)*val;
		tAdd(k)+=val;
		return;
	}
	inline void pushdown(reg int k,reg int l,reg int r){
		if(tAdd(k)){
			add(lson,l,mid,tAdd(k));
			add(rson,mid+1,r,tAdd(k));
			tAdd(k)=0;
		}
		return;
	}
	inline void update(reg int k,reg int l,reg int r,reg int L,reg int R,reg int val){
		if(L<=l&&r<=R){
			add(k,l,r,val);
			return;
		}
		pushdown(k,l,r);
		if(L<=mid)
			update(lson,l,mid,L,R,val);
		if(R>mid)
			update(rson,mid+1,r,L,R,val);
		pushup(k);
		return;
	}
	inline ll query(reg int k,reg int l,reg int r,reg int L,reg int R){
		if(L<=l&&r<=R)
			return sum(k);
		pushdown(k,l,r);
		if(L<=mid&&mid<R)
			return query(lson,l,mid,L,R)+query(rson,mid+1,r,L,R);
		else if(L<=mid)
			return query(lson,l,mid,L,R);
		else
			return query(rson,mid+1,r,L,R);
	}
	#undef lson
	#undef rson
	#undef mid
}

int main(void){
	n=read();
	for(reg int i=1;i<=n;++i)
		a[i]=read();
	SegmentTree::build(1,1,n,a);
	for(reg int i=1;i<=n;++i){
		static int opt,l,r;
		static ll c;
		opt=read(),l=read(),r=read(),c=read();
		switch(opt){
			case 0:{
				SegmentTree::update(1,1,n,l,r,c);
				break;
			}
			case 1:{
				writeln(SegmentTree::query(1,1,n,l,r)%(c+1));
				break;
			}
		}
	}
	flush();
	return 0;
}