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
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch)) ch=getchar();
	while(isdigit(ch)) res=10*res+(ch^'0'),ch=getchar();
	return res;
}

inline void writeln(reg int x){
	static char buf[32];
	reg int p=-1;
	if(!x) putchar('0');
	else while(x) buf[++p]=(x%10)^'0',x/=10;
	while(~p) putchar(buf[p--]);
	putchar('\n');
	return;
}

const int MAXN=2e5+5;
const int MAXLOG2A=30;

struct Basis{
	int cnt,unit[MAXLOG2A];
	inline void insert(reg int x){
		for(reg int i=MAXLOG2A-1;i>=0;--i)
			if((x>>i)&1){
				if(!unit[i]){
					++cnt,unit[i]=x;
					break;
				}
				x^=unit[i];
			}
		return;
	}
	inline void clear(void){
		cnt=0,memset(unit,0,sizeof(unit));
		return;
	}
};

inline Basis operator+(const Basis& a,const Basis& b){
	Basis res=a;
	for(reg int i=0;i<MAXLOG2A;++i)
		if(b.unit[i])
			res.insert(b.unit[i]);
	return res;
}

int n,q;
int a[MAXN],b[MAXN];

namespace SegmentTree{
	#define lson ( (k) << 1 )
	#define rson ( (k) << 1 | 1 )
	#define mid ( ( (l) + (r) ) >> 1 )
	struct Node{
		Basis bas;
		#define val(x) unit[(x)].val
		#define bas(x) unit[(x)].bas
	};
	Node unit[MAXN<<2];
	inline void pushup(reg int k){
		bas(k)=bas(lson)+bas(rson);
		return;
	}
	inline void build(reg int k,reg int l,reg int r,reg int b[]){
		if(l==r){
			bas(k).insert(b[l]);
			return;
		}
		build(lson,l,mid,b),build(rson,mid+1,r,b);
		pushup(k);
		return;
	}
	inline void update(reg int k,reg int l,reg int r,reg int pos){
		if(l==r){
			bas(k).clear();
			bas(k).insert(b[l]);
			return;
		}
		if(pos<=mid)
			update(lson,l,mid,pos);
		else
			update(rson,mid+1,r,pos);
		pushup(k);
		return;
	}
	inline Basis query(reg int k,reg int l,reg int r,reg int L,reg int R){
		if(L<=l&&r<=R)
			return bas(k);
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
	#undef val
	#undef bas
}

namespace BIT{
	inline int lowbit(reg int x){
		return x&(-x);
	}
	int n,unit[MAXN];
	inline void Init(reg int s){
		n=s;
		return;
	}
	inline void update(reg int id,reg int val){
		for(reg int i=id;i<=n;i+=lowbit(i))
			unit[i]^=val;
		return;
	}
	inline int query(reg int id){
		reg int res=0;
		for(reg int i=id;i;i^=lowbit(i))
			res^=unit[i];
		return res;
	}
}

int main(void){
	n=read(),q=read();
	for(reg int i=1;i<=n;++i)
		a[i]=read(),b[i]=a[i]^a[i-1];
	BIT::Init(n);
	for(reg int i=1;i<=n;++i)
		BIT::update(i,a[i]),BIT::update(i+1,a[i]);
	SegmentTree::build(1,1,n,b);
	while(q--){
		static int opt,l,r,k;
		static Basis ans;
		opt=read(),l=read(),r=read();
		switch(opt){
			case 1:{
				k=read();
				b[l]^=k,b[r+1]^=k;
				BIT::update(l,k),BIT::update(r+1,k);
				SegmentTree::update(1,1,n,l);
				if(r<n)
					SegmentTree::update(1,1,n,r+1);
				break;
			}
			case 2:{
				ans.clear();
				if(l<r)
					ans=SegmentTree::query(1,1,n,l+1,r);
				ans.insert(BIT::query(l));
				writeln(1<<ans.cnt);
				break;
			}
		}
	}
	flush();
	return 0;
}