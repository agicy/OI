#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
#define flush() (fwrite(wbuf,1,wp1,stdout),wp1=0)
#define putchar(c) (wp1==wp2&&(flush(),0),wbuf[wp1++]=c)
static char wbuf[1<<21];int wp1;const int wp2=1<<21;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return res;
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

namespace SegmentTree{
	#define lson ( (k) << 1 )
	#define rson ( (k) << 1 | 1 )
	#define mid ( ( (l) + (r) ) >> 1 )
	struct Node{
		ll sum;
		bool flag;
		inline Node(reg ll a=0){
			sum=a,flag=(a==0||a==1);
			return;
		}
		#define sum(x) unit[(x)].sum
		#define flag(x) unit[(x)].flag
	};
	Node unit[MAXN<<2];
	inline void pushup(reg int k){
		sum(k)=sum(lson)+sum(rson);
		flag(k)=flag(lson)&&flag(rson);
		return;
	}
	inline void build(reg int k,reg int l,reg int r,reg ll a[]){
		if(l==r){
			unit[k]=Node(a[l]);
			return;
		}
		build(lson,l,mid,a),build(rson,mid+1,r,a);
		pushup(k);
		return;
	}
	inline void update(reg int k,reg int l,reg int r,reg int L,reg int R){
		if(unit[k].flag)
			return;
		if(l==r){
			unit[k]=Node((ll)floor(sqrt(unit[k].sum)));
			return;
		}
		if(L<=mid)
			update(lson,l,mid,L,R);
		if(R>mid)
			update(rson,mid+1,r,L,R);
		pushup(k);
		return;
	}
	inline ll query(reg int k,reg int l,reg int r,reg int L,reg int R){
		if(L<=l&&r<=R)
			return sum(k);
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
};

int n,m;
ll a[MAXN];

int main(void){
	n=read();
	for(reg int i=1;i<=n;++i)
		a[i]=read();
	SegmentTree::build(1,1,n,a);
	for(reg int i=1;i<=n;++i){
		static int opt,l,r;
		opt=read(),l=read(),r=read(),read();
		if(!opt)
			SegmentTree::update(1,1,n,l,r);
		else
			writeln(SegmentTree::query(1,1,n,l,r));
	}
	flush();
	return 0;
}