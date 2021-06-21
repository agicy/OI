#pragma GCC optimize("Ofast")
#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
static char buf[1<<21],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch)) ch=getchar();
	while(isdigit(ch)) res=10*res+(ch^'0'),ch=getchar();
	return res;
}

const int mod=1e9+9;

struct modInt{
	int x;
	inline modInt(reg int x=0):x(x){
		//assert(0<=x&&x<mod);
		return;
	}
	inline modInt operator+(const modInt& a)const{
		reg int sum=x+a.x;
		return sum>=mod?sum-mod:sum;
	}
	inline modInt operator-(const modInt& a)const{
		reg int sum=x-a.x;
		return sum<0?sum+mod:sum;
	}
	inline modInt operator-(void){
		return modInt(0)-*this;
	}
	inline modInt operator*(const modInt& a)const{
		return 1ll*x*a.x%mod;
	}
	inline void operator+=(const modInt& a){
		x+=a.x;
		if(x>=mod) x-=mod;
		return;
	}
	inline void operator-=(const modInt& a){
		x-=a.x;
		if(x<0) x+=mod;
		return;
	}
	inline void operator*=(const modInt& a){
		x=1ll*x*a.x%mod;
		return;
	}
};

const int MAXN=5e5+5;
const int inf=0x3f3f3f3f;

struct Interval{
	int l,r;
	inline bool operator<(const Interval& a)const{
		return r<a.r;
	}
};

int n,m;
int x[MAXN];
Interval Inv[MAXN];

namespace SegmentTree{
	#define lson ( (k) << 1 )
	#define rson ( (k) << 1 | 1 )
	#define mid ( ( (l) + (r) ) >> 1 )
	struct Node{
		modInt sum,tMul;
		#define sum(x) unit[(x)].sum
		#define tMul(x) unit[(x)].tMul
	};
	Node unit[MAXN<<2];
	inline void pushup(reg int k){
		sum(k)=sum(lson)+sum(rson);
		return;
	}
	inline void build(reg int k,reg int l,reg int r){
		tMul(k)=1;
		if(l==r)
			return;
		build(lson,l,mid),build(rson,mid+1,r);
		return;
	}
	inline void mul(reg int k,modInt v){
		sum(k)*=v,tMul(k)*=v;
		return;
	}
	inline void pushdown(reg int k){
		if(tMul(k).x!=1){
			mul(lson,tMul(k)),mul(rson,tMul(k));
			tMul(k)=1;
		}
		return;
	}
	inline void update(reg int k,reg int l,reg int r,reg int pos,modInt val){
		if(l==r){
			sum(k)+=val;
			return;
		}
		pushdown(k);
		if(pos<=mid)
			update(lson,l,mid,pos,val);
		else
			update(rson,mid+1,r,pos,val);
		pushup(k);
		return;
	}
	inline void update(reg int k,reg int l,reg int r,reg int L,reg int R,modInt val){
		if(L<=l&&r<=R){
			mul(k,val);
			return;
		}
		pushdown(k);
		if(L<=mid)
			update(lson,l,mid,L,R,val);
		if(R>mid)
			update(rson,mid+1,r,L,R,val);
		pushup(k);
		return;
	}
	inline modInt query(reg int k,reg int l,reg int r,reg int L,reg int R){
		if(L<=l&&r<=R)
			return sum(k);
		pushdown(k);
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
	#undef sum
	#undef tMul
}

int main(void){
	n=read(),m=read();
	for(reg int i=1;i<=n;++i)
		Inv[i].l=read(),Inv[i].r=read();
	for(reg int i=1;i<=m;++i)
		x[i]=read();
	sort(x+1,x+m+1);
	sort(Inv+1,Inv+n+1);
	if(x[m]>Inv[n].r)
		puts("0");
	else{
		x[m+1]=inf;
		SegmentTree::build(1,1,m+1);
		SegmentTree::update(1,1,m+1,m+1,1);
		for(reg int i=1;i<=n;++i){
			reg int lef=lower_bound(x+1,x+m+1,Inv[i].l)-x;
			reg int rig=upper_bound(x+1,x+m+1,Inv[i-1].r)-x;
			modInt v=SegmentTree::query(1,1,m+1,m+1,m+1);
			modInt tmp1=SegmentTree::query(1,1,m+1,lef,m),tmp2=0;
			if(Inv[i].l<=x[rig])
				tmp1+=v;
			else
				tmp2+=v;
			if(Inv[i].r<x[rig])
				tmp1+=v;
			else
				tmp2+=v;
			if(lef>1) SegmentTree::update(1,1,m+1,1,lef-1,2);
			SegmentTree::update(1,1,m+1,m+1,m+1,0);
			SegmentTree::update(1,1,m+1,m+1,tmp1);
			SegmentTree::update(1,1,m+1,rig,tmp2);
		}
		printf("%d\n",SegmentTree::query(1,1,m+1,m+1,m+1).x);
	}
	return 0;
}