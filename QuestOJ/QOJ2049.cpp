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
	while(!isdigit(ch))f|=(ch=='-'),ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return f?-res:res;
}

const int MAXN=1e5+5;
const int inf=2e9;

int n,q;
int a[MAXN],b[MAXN];
int x[MAXN],y[MAXN];
int rtx[MAXN],rty[MAXN];

namespace SegmentTree{
	const int MAXSIZE=MAXN*90;
	#define mid ( ( 0ll + (l) + (r) ) >> 1 )
	struct Node{
		int lson,rson;
		int cnt;
		ll sum;
		#define lson(x) unit[(x)].lson
		#define rson(x) unit[(x)].rson
		#define cnt(x) unit[(x)].cnt
		#define sum(x) unit[(x)].sum
	};
	int tot;
	Node unit[MAXSIZE];
	inline int update(reg int pre,reg int l,reg int r,reg int pos){
		reg int p=++tot;
		unit[p]=unit[pre],++cnt(p),sum(p)+=pos;
		if(l!=r){
			if(pos<=mid)
				lson(p)=update(lson(pre),l,mid,pos);
			else
				rson(p)=update(rson(pre),mid+1,r,pos);
		}
		return p;
	}
	ll ans;
	inline int query(reg int pre,reg int p,reg int l,reg int r,reg int k){
		if(l==r)
			return l;
		reg int res=0,Sum=cnt(lson(p))-cnt(lson(pre));
		if(Sum>=k){
			ans+=sum(rson(p))-sum(rson(pre));
			res=query(lson(pre),lson(p),l,mid,k);
			ans-=1ll*res*(cnt(rson(p))-cnt(rson(pre)));
		}
		else{
			ans-=sum(lson(p))-sum(lson(pre));
			res=query(rson(pre),rson(p),mid+1,r,k-Sum);
			ans+=1ll*res*(cnt(lson(p))-cnt(lson(pre)));
		}
		return res;
	}
}

int main(void){
	n=read(),q=read();
	for(reg int i=1;i<=n;++i)
		a[i]=read();
	for(reg int i=1;i<=n;++i)
		b[i]=read();
	for(reg int i=1;i<=n;++i){
		rtx[i]=SegmentTree::update(rtx[i-1],-inf,inf,a[i]+b[i]);
		rty[i]=SegmentTree::update(rty[i-1],-inf,inf,a[i]-b[i]);
	}
	while(q--){
		static int l,r;
		l=read(),r=read();
		SegmentTree::ans=0;
		SegmentTree::query(rtx[l-1],rtx[r],-inf,inf,(r-l+2)>>1);
		SegmentTree::query(rty[l-1],rty[r],-inf,inf,(r-l+2)>>1);
		printf("%.2lf\n",0.5*SegmentTree::ans);
	}
	return 0;
}