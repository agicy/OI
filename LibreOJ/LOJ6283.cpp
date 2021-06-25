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
	while(isdigit(ch)) res=10*res+(ch^'0'),ch=getchar();
	return f?-res:res;
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

const int MAXN=1e5+5;
const int mod=1e4+7;

inline int add(reg int a,reg int b){
	a+=b;
	return a>=mod?a-mod:a;
}

inline int sub(reg int a,reg int b){
	a-=b;
	return a<0?a+mod:a;
}

namespace SegmentTree{
	#define lson ( (k) << 1 )
	#define rson ( (k) << 1 | 1 )
	#define mid ( ( (l) + (r) ) >> 1 )
	struct Node{
		int val;
		int tAdd;
		int tMul;
		#define val(x) unit[(x)].val
		#define tAdd(x) unit[(x)].tAdd
		#define tMul(x) unit[(x)].tMul
	};
	Node unit[MAXN<<2];
	inline void pushup(reg int k){
		val(k)=add(val(lson),val(rson));
		return;
	}
	inline void build(reg int k,reg int l,reg int r,reg int a[]){
		tMul(k)=1;
		tAdd(k)=0;
		if(l==r){
			val(k)=a[l];
			return;
		}
		build(lson,l,mid,a),build(rson,mid+1,r,a);
		pushup(k);
		return;
	}
	inline void Mul(reg int k,reg int Val){
		val(k)=1ll*val(k)*Val%mod,tAdd(k)=1ll*tAdd(k)*Val%mod,tMul(k)=1ll*tMul(k)*Val%mod;
		return;
	}
	inline void Add(reg int k,reg int l,reg int r,reg int Val){
		val(k)=add(val(k),1ll*Val*(r-l+1)%mod),tAdd(k)=add(tAdd(k),Val);
		return;
	}
	inline void pushdown(reg int k,reg int l,reg int r){
		if(tMul(k)!=1){
			Mul(lson,tMul(k)),Mul(rson,tMul(k));
			tMul(k)=1;
		}
		if(tAdd(k)){
			Add(lson,l,mid,tAdd(k)),Add(rson,mid+1,r,tAdd(k));
			tAdd(k)=0;
		}
		return;
	}
	inline void updateMul(reg int k,reg int l,reg int r,reg int L,reg int R,reg int Val){
		if(L<=l&&r<=R){
			Mul(k,Val);
			return;
		}
		pushdown(k,l,r);
		if(L<=mid)
			updateMul(lson,l,mid,L,R,Val);
		if(R>mid)
			updateMul(rson,mid+1,r,L,R,Val);
		pushup(k);
		return;
	}
	inline void updateAdd(reg int k,reg int l,reg int r,reg int L,reg int R,reg int Val){
		if(L<=l&&r<=R){
			Add(k,l,r,Val);
			return;
		}
		pushdown(k,l,r);
		if(L<=mid)
			updateAdd(lson,l,mid,L,R,Val);
		if(R>mid)
			updateAdd(rson,mid+1,r,L,R,Val);
		pushup(k);
		return;
	}
	inline int query(reg int k,reg int l,reg int r,reg int pos){
		if(l==r)
			return val(k);
		pushdown(k,l,r);
		if(pos<=mid)
			return query(lson,l,mid,pos);
		else
			return query(rson,mid+1,r,pos);
	}
	#undef lson
	#undef rson
	#undef mid
	#undef val
	#undef tAdd
	#undef tMul
};

int n,m;
int a[MAXN];

int main(void){
	n=read();
	for(reg int i=1;i<=n;++i)
		a[i]=(read()%mod+mod)%mod;
	SegmentTree::build(1,1,n,a);
	for(reg int i=1;i<=n;++i){
		static int opt,l,r,c;
		opt=read(),l=read(),r=read(),c=(read()%mod+mod)%mod;
		switch(opt){
			case 0:{
				SegmentTree::updateAdd(1,1,n,l,r,c);
				break;
			}
			case 1:{
				SegmentTree::updateMul(1,1,n,l,r,c);
				break;
			}
			case 2:{
				writeln(SegmentTree::query(1,1,n,r));
				break;
			}
		}
	}
	flush();
	return 0;
}