#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
static char buf[1<<21],*p1=buf,*p2=buf;
#define flush() (fwrite(wbuf,1,wp1,stdout),wp1=0)
#define putchar(V) (wp1==wp2&&(flush(),0),wbuf[wp1++]=V)
static char wbuf[1<<21];int wp1;const int wp2=1<<21;
inline int read(void){
	reg bool f=false;
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch)) f|=(ch=='-'),ch=getchar();
	while(isdigit(ch)) res=10*res+(ch^'0'),ch=getchar();
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

const int MAXN=1e6+5;
const ll inf=1e18;

int n,m,p;
int a[MAXN];

namespace SegmentTree{
	struct Node{
		ll sum;
		vector<ll> V;
		#define sum(x) unit[(x)].sum
		#define V(x) unit[(x)].V
	};
	Node unit[MAXN<<2];
	#define lson ( (k) << 1 )
	#define rson ( (k) << 1 | 1 )
	#define mid ( ( (l) + (r) ) >> 1 )
	inline void pushup(reg int k,reg int l,reg int r){
		sum(k)=sum(lson)+sum(rson);
		for(reg int x=0,y=0;x<=mid-l+1;++x){
			if(y==r-mid+1)
				--y;
			for(;y<=r-mid;++y){
				reg ll lim =V(lson)[x+1]-1-1ll*x*p+sum(lson);
				if(V(rson)[y]>lim){
					--y;
					break;
				}
				V(k)[x+y]=min(V(k)[x+y],max(V(lson)[x],V(rson)[y]+1ll*x*p-sum(lson)));
			}
		}
		return;
	}
	inline void build(reg int k,reg int l,reg int r){
		V(k).resize(r-l+3);
		for(reg int i=0;i<=r-l+2;++i)
			V(k)[i]=(i?inf:-inf);
		if(l==r){
			sum(k)=a[l];
			V(k)[1]=p-a[l];
			return;
		}
		build(lson,l,mid),build(rson,mid+1,r);
		pushup(k,l,r);
		return;
	}
	inline ll query(reg int k,reg int l,reg int r,reg int L,reg int R,ll val){
		if(L<=l&&r<=R){
			reg int pos=upper_bound(V(k).begin(),V(k).end(),val)-V(k).begin()-1;
			return val+sum(k)-1ll*p*pos;
		}
		if(L<=mid&&mid<R)
			return query(rson,mid+1,r,L,R,query(lson,l,mid,L,R,val));
		else if(L<=mid)
			return query(lson,l,mid,L,R,val);
		else
			return query(rson,mid+1,r,L,R,val);
	}
	#undef lson
	#undef rson
	#undef mid
}

int main(void){
	n=read(),m=read(),p=read();
	for(reg int i=1;i<=n;++i)
		a[i]=read();
	SegmentTree::build(1,1,n);
	while(m--){
		static int l,r;
		l=read(),r=read();
		writeln(SegmentTree::query(1,1,n,l,r,0));
	}
	flush();
	return 0;
}