#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline ll read(void){
	reg bool f=false;
	reg char ch=getchar();
	reg ll res=0;
	while(ch<'0'||'9'<ch)f|=(ch=='-'),ch=getchar();
	while('0'<=ch&&ch<='9')res=10*res+ch-'0',ch=getchar();
	return f?-res:res;
}

const int MAXN=100000+5;
const int MAXM=100000+5;

struct SegmentTree{
	#define lson (k<<1)
	#define rson (k<<1|1)
	#define mid ((l+r)>>1)
	struct Node{
		ll sum,tag;
		inline Node(void){
			sum=tag=0;
			return;
		}
		inline Node(reg ll a,reg ll b){
			sum=a,tag=b;
			return;
		}
	};
	Node unit[MAXN<<2];
	inline void pushup(reg int k){
		unit[k].sum=unit[lson].sum+unit[rson].sum;
		return;
	}
	inline void Add(reg int k,reg int l,reg int r,reg ll val){
		unit[k].sum+=val*(r-l+1);
		unit[k].tag+=val;
		return;
	}
	inline void pushdown(reg int k,reg int l,reg int r){
		if(unit[k].tag){
			Add(lson,l,mid,unit[k].tag);
			Add(rson,mid+1,r,unit[k].tag);
			unit[k].tag=0;
		}
		return;
	}
	inline void Build(reg int k,reg int l,reg int r,reg ll a[]){
		if(l==r){
			unit[k]=Node(a[l],0);
			return;
		}
		Build(lson,l,mid,a);
		Build(rson,mid+1,r,a);
		pushup(k);
		return;
	}
	inline void Update(reg int k,reg int l,reg int r,reg int L,reg int R,reg ll val){
		if(L<=l&&r<=R){
			Add(k,l,r,val);
			return;
		}
		pushdown(k,l,r);
		if(L<=mid)
			Update(lson,l,mid,L,R,val);
		if(R>mid)
			Update(rson,mid+1,r,L,R,val);
		pushup(k);
		return;
	}
	inline ll Query(reg int k,reg int l,reg int r,reg int L,reg int R){
		if(L<=l&&r<=R)
			return unit[k].sum;
		reg ll res=0;
		pushdown(k,l,r);
		if(L<=mid)
			res+=Query(lson,l,mid,L,R);
		if(R>mid)
			res+=Query(rson,mid+1,r,L,R);
		return res;
		
	}
	#undef lson
	#undef rson
	#undef mid
};

int n,m;
ll a[MAXN];
SegmentTree T;

int main(void){
	n=read(),m=read();
	for(reg int i=1;i<=n;++i)
		a[i]=read();
	T.Build(1,1,n,a);
	for(reg int i=1;i<=m;++i){
		static char ch;
		static int l,r;
		static ll d;
		ch='\0';
		do
			ch=getchar();
		while(ch!='C'&&ch!='Q');
		if(ch=='C'){
			l=read(),r=read(),d=read();
			T.Update(1,1,n,l,r,d);
		}
		if(ch=='Q'){
			l=read(),r=read();
			printf("%lld\n",T.Query(1,1,n,l,r));
		}
	}
	return 0;
}
