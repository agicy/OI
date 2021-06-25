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

inline void writeln(reg ll x){
	static char buf[32];
	reg int p=-1;
	if(!x) putchar('0');
	else while(x) buf[++p]=(x%10)^'0',x/=10;
	while(~p) putchar(buf[p--]);
	putchar('\n');
	return;
}

const int MAXQ=3e5+5;
const int MAXT=1e6+5;
const int T=1e6;

int q;
int a[MAXQ],b[MAXQ];

namespace SegmentTree{
	#define lson ( (k) << 1 )
	#define rson ( (k) << 1 | 1 )
	#define mid ( ( (l) + (r) ) >> 1 )
	struct Node{
		ll sum,val;
		#define sum(x) unit[(x)].sum
		#define val(x) unit[(x)].val
	};
	Node unit[MAXT<<2];
	inline void pushup(reg int k){
		sum(k)=sum(lson)+sum(rson);
		val(k)=max(val(lson)+sum(rson),val(rson));
		return;
	}
	inline void build(reg int k,reg int l,reg int r){
		if(l==r){
			val(k)=l;
			return;
		}
		build(lson,l,mid),build(rson,mid+1,r);
		pushup(k);
		return;
	}
	inline void update(reg int k,reg int l,reg int r,reg int pos,reg int Val){
		if(l==r){
			sum(k)+=Val,val(k)+=Val;
			return;
		}
		if(pos<=mid)
			update(lson,l,mid,pos,Val);
		else
			update(rson,mid+1,r,pos,Val);
		pushup(k);
		return;
	}
	ll ans=0;
	inline void query(reg int k,reg int l,reg int r,reg int pos){
		if(r<=pos){
			ans=max(ans+sum(k),val(k));
			return;
		}
		query(lson,l,mid,pos);
		if(mid<pos)
			query(rson,mid+1,r,pos);
		return;
	}
	#undef lson
	#undef rson
	#undef mid
}

int main(void){
	q=read();
	SegmentTree::build(1,1,T);
	for(reg int i=1;i<=q;++i){
		static char opt;
		do
			opt=getchar();
		while(opt!='+'&&opt!='-'&&opt!='?');
		a[i]=read();
		switch(opt){
			case '+':{
				b[i]=read();
				SegmentTree::update(1,1,T,a[i],b[i]);
				break;
			}
			case '-':{
				SegmentTree::update(1,1,T,a[a[i]],-b[a[i]]);
				break;
			}
			case '?':{
				SegmentTree::ans=0;
				SegmentTree::query(1,1,T,a[i]);
				writeln(SegmentTree::ans-a[i]);
				break;
			}
		}
	}
	flush();
	return 0;
}