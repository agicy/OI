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

const int MAXN=3e5+5;
const int p=998244353;
const int inv2_p=499122177;
const int inv6_p=166374059;

inline int max(reg int a,reg int b){
	return a>b?a:b;
}

inline int min(reg int a,reg int b){
	return a<b?a:b;
}

inline int add(reg int a,reg int b){
	a+=b;
	return a>=p?a-p:a;
}

inline int mul(reg int a,reg int b){
	return 1ll*a*b%p;
}

inline int sigma1(reg int i){
	return mul(mul(i,i+1),inv2_p);
}

inline int sigma2(reg int i){
	return mul(mul(i,i+1),mul((i<<1|1),inv6_p));
}

int n,m;
int a[MAXN];

namespace SegmentTree{
	#define lson ( ( k ) << 1 )
	#define rson ( ( k ) << 1 | 1 )
	#define mid ( ( (l) + (r) ) >> 1 )
	struct Node{
		int Max,Min;
		int sum,sum2;
		#define Max(x) unit[(x)].Max
		#define Min(x) unit[(x)].Min
		#define sum(x) unit[(x)].sum
		#define sum2(x) unit[(x)].sum2
	};
	inline Node operator+(const Node& a,const Node& b){
		Node res;
		res.Max=max(a.Max,b.Max);
		res.Min=min(a.Min,b.Min);
		res.sum=add(a.sum,b.sum);
		res.sum2=add(a.sum2,b.sum2);
		return res;
	}
	Node unit[MAXN<<2];
	inline void pushup(reg int k){
		unit[k]=unit[lson]+unit[rson];
		return;
	}
	inline void build(reg int k,reg int l,reg int r,reg int a[]){
		if(l==r){
			Max(k)=Min(k)=sum(k)=a[l]%p;
			sum2(k)=mul(a[l]%p,a[l]%p);
			return;
		}
		build(lson,l,mid,a),build(rson,mid+1,r,a);
		pushup(k);
		return;
	}
	inline void update(reg int k,reg int l,reg int r,reg int pos,reg int val){
		if(l==r){
			Max(k)=Min(k)=sum(k)=val%p;
			sum2(k)=mul(val%p,val%p);
			return;
		}
		if(pos<=mid)
			update(lson,l,mid,pos,val);
		else
			update(rson,mid+1,r,pos,val);
		pushup(k);
		return;
	}
	inline Node query(reg int k,reg int l,reg int r,reg int L,reg int R){
		if(L<=l&&r<=R)
			return unit[k];
		if(L<=mid&&mid<R)
			return query(lson,l,mid,L,R)+query(rson,mid+1,r,L,R);
		else if(L<=mid)
			return query(lson,l,mid,L,R);
		else
			return query(rson,mid+1,r,L,R);
	}
	inline bool queryAns(reg int L,reg int R,reg int D){
		if(L>R)
			return false;
		Node info=query(1,1,n,L,R);
		reg int len=R-L+1;
		if(add(info.Max,p-(info.Min)%p)!=mul(abs(D),(len-1)))
			return false;
		reg int sum_real=mul(add(info.Max%p,info.Min%p),mul(len,inv2_p));
		if(sum_real!=info.sum)
			return false;
		reg int a_0=((info.Min-D)%p+p)%p;
		reg int part1=mul(len,mul(a_0,a_0));
		reg int part2=mul(add(a_0,a_0),mul(D,sigma1(len)));
		reg int part3=mul(mul(D,D),sigma2(len));
		reg int sum2_real=add(add(part1,part2),part3);
		if(sum2_real!=info.sum2)
			return false;
		return true;
	}
	#undef lson
	#undef rson
	#undef mid
}

int main(void){
	n=read(),m=read();
	for(reg int i=1;i<=n;++i)
		a[i]=read();
	reg int cnt_yes=0;
	SegmentTree::build(1,1,n,a);
	while(m--){
		static int op,x,y,l,r,k;
		op=read();
		switch(op){
			case 1:{
				x=read()^cnt_yes,y=read()^cnt_yes;
				SegmentTree::update(1,1,n,x,y);
				break;
			}
			case 2:{
				l=read()^cnt_yes,r=read()^cnt_yes,k=read()^cnt_yes;
				reg bool ans=SegmentTree::queryAns(l,r,k);
				if(ans)
					++cnt_yes;
				puts(ans?"Yes":"No");
				break;
			}
		}
	}
	return 0;
}