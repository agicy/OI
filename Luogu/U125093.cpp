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
	while(ch<'0'||'9'<ch)f|=(ch=='-'),ch=getchar();
	while('0'<=ch&&ch<='9')res=10*res+ch-'0',ch=getchar();
	return f?-res:res;
}

const int MAXN=5e4+5;

namespace SegmentTree{
	#define lson ( (k) << 1 )
	#define rson ( (k) << 1 | 1 )
	#define mid ( ( (l) + (r) ) >> 1 )
	const int MAXSIZE=4*MAXN;
	struct Node{
		ll sum;
		#define sum(x) unit[(x)].sum
	};
	Node unit[MAXSIZE];
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
	inline void update(reg int k,reg int l,reg int r,reg int pos,reg int val){
		if(l==r){
			sum(k)+=val;
			return;
		}
		if(pos<=mid)
			update(lson,l,mid,pos,val);
		else
			update(rson,mid+1,r,pos,val);
		pushup(k);
		return;
	}
	inline ll query(reg int k,reg int l,reg int r,reg int L,reg int R){
		if(L<=l&&r<=R)
			return sum(k);
		reg ll res=0;
		if(L<=mid)
			res+=query(lson,l,mid,L,R);
		if(R>mid)
			res+=query(rson,mid+1,r,L,R);
		return res;
	}
	#undef lson
	#undef rson
	#undef mid
}

int n;
int a[MAXN];


int main(void){
	reg int T=read();
	for(reg int C=1;C<=T;++C){
		printf("Case %d:\n",C);
		n=read();
		for(reg int i=1;i<=n;++i)
			a[i]=read();
		using namespace SegmentTree;
		build(1,1,n,a);
		reg bool flag=true;
		while(flag){
			static char ch;
			static int i,j;
			do
				ch=getchar();
			while(ch!='A'&&ch!='S'&&ch!='Q'&&ch!='E');
			switch(ch){
				case 'A':{
					i=read(),j=read();
					update(1,1,n,i,j);
					break;
				}
				case 'S':{
					i=read(),j=read();
					update(1,1,n,i,-j);
					break;
				}
				case 'Q':{
					i=read(),j=read();
					reg ll res=query(1,1,n,i,j);
					printf("%lld\n",res);
					break;
				}
				case 'E':{
					flag=false;
					break;
				}
			}
		}
	}
	return 0;
}