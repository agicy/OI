#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef unsigned int uint;
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

const int MAXN=1e5+5;
const int MAXK=6+1;
const uint inf=0x7fffffffu;

struct Data{
	uint d,v;
	inline Data(reg uint d=0,reg uint v=0):d(d),v(v){
		return;
	}
	inline bool operator<(const Data& a)const{
		return d<a.d;
	}
};

int n,q;
Data a[MAXN];

namespace SegmentTree{
	#define lson ( (k) << 1 )
	#define rson ( (k) << 1 | 1 )
	#define mid ( ( (l) + (r) ) >> 1 )
	struct Node{
		int pos;
		uint f[MAXK];
		inline Node(void){
			pos=0,memset(f,0,sizeof(f));
			f[0]=1;
			return;
		}
		inline Node operator+(const Node& x){
			Node res;
			res.f[0]=0;
			if(a[pos].v<a[x.pos].v)
				res.pos=pos;
			else
				res.pos=x.pos;
			for(reg int i=0;i<MAXK;++i)
				for(reg int j=0;j<=i;++j)
					res.f[i]+=f[j]*x.f[i-j];
			return res;
		}
		#define f(x) unit[(x)].f
		#define pos(x) unit[(x)].pos
	};
	Node unit[MAXN<<2];
	inline void pushup(reg int k){
		unit[k]=unit[lson]+unit[rson];
		return;
	}
	inline void build(reg int k,reg int l,reg int r,reg Data a[]){
		if(l==r){
			f(k)[1]=a[l].v;
			pos(k)=l;
			return;
		}
		build(lson,l,mid,a),build(rson,mid+1,r,a);
		pushup(k);
		return;
	}
	inline Node query(reg int k,reg int l,reg int r,reg int L,reg int R){
		if(L<=l&&r<=R)
			return unit[k];
		Node res;
		if(L<=mid)
			res=res+query(lson,l,mid,L,R);
		if(R>mid)
			res=res+query(rson,mid+1,r,L,R);
		return res;
	}
	#undef lson
	#undef rson
	#undef mid
}

uint fac[MAXN];

using namespace SegmentTree;

int main(void){
	n=read(),q=read();
	a[0].v=inf;
	for(reg int i=1;i<=n;++i)
		a[i].d=read(),a[i].v=read();
	fac[0]=1;
	for(reg int i=1;i<=n;++i)
		fac[i]=fac[i-1]*i;
	sort(a+1,a+n+1);
	build(1,1,n,a);
	while(q--){
		static int L,R,k;
		L=read(),R=read(),k=read();
		reg int l=lower_bound(a+1,a+n+1,Data(L,0))-a;
		reg int r=upper_bound(a+1,a+n+1,Data(R,0))-(a+1);
		if(l>r||l>n)
			puts("0");
		else{
			reg int pos=query(1,1,n,l,r).pos;
			Node tmp;
			if(l<=pos-1)
				tmp=tmp+query(1,1,n,l,pos-1);
			if(r>=pos+1)
				tmp=tmp+query(1,1,n,pos+1,r);
			printf("%u\n",tmp.f[k]*fac[k]);
		}
	}
	return 0;
}