#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
typedef unsigned long long ull;
#define INF 0X3F3F3F3F3F3F3F3Fll
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

const int MAXN=100000+5;
const int MAXQ=100000+5;

inline void Read(void);
inline void Work(void);

int main(void){
	Read();
	Work();
	return 0;
}

int n,Q;
ll a[MAXN];

inline void Read(void){
	n=read(),Q=read();
	for(reg int i=1;i<=n;++i)
		a[i]=read();
	return;
}

inline ll Div(reg ll a,reg ll b){
	if(a<0&&a%b!=0)
		return a/b-1;
	else
		return a/b;
}

struct SegmentTree{
	#define lson ( (k) << 1 )
	#define rson ( (k) << 1 | 1)
	#define mid ( ( (l) + (r) ) >> 1 )
	struct Node{
		ll sum,Max,Min,tag_Add;
		inline Node(reg ll sum=0,reg ll Max=0,reg ll Min=0,reg ll tag_Add=0):sum(sum),Max(Max),Min(Min),tag_Add(tag_Add){
			return;
		}
	};
	Node unit[MAXN<<3];
	inline void pushup(reg int k){
		unit[k]=Node(unit[lson].sum+unit[rson].sum,max(unit[lson].Max,unit[rson].Max),min(unit[lson].Min,unit[rson].Min),0);
		return;
	}
	inline void Add(reg int k,reg int l,reg int r,reg ll val){
		unit[k].sum+=(r-l+1)*val;
		unit[k].Max+=val;
		unit[k].Min+=val;
		unit[k].tag_Add+=val;
		return;
	}
	inline void pushdown(reg int k,reg int l,reg int r){
		if(unit[k].tag_Add){
			Add(lson,l,mid,unit[k].tag_Add);
			Add(rson,mid+1,r,unit[k].tag_Add);
			unit[k].tag_Add=0;
		}
		return;
	}
	inline void Build(reg int k,reg int l,reg int r,reg ll a[]){
		if(l==r){
			unit[k]=Node(a[l],a[l],a[l],0);
			return;
		}
		Build(lson,l,mid,a);
		Build(rson,mid+1,r,a);
		pushup(k);
		return;
	}
	inline void Update_Add(reg int k,reg int l,reg int r,reg int L,reg int R,reg ll val){
		if(L<=l&&r<=R){
			Add(k,l,r,val);
			return;
		}
		pushdown(k,l,r);
		if(L<=mid)
			Update_Add(lson,l,mid,L,R,val);
		if(R>mid)
			Update_Add(rson,mid+1,r,L,R,val);
		pushup(k);
		return;
	}
	inline void Update_Div(reg int k,reg int l,reg int r,reg int L,reg int R,reg ll val){
		if(L<=l&&r<=R){
			reg ll v1=Div(unit[k].Max,val);
			reg ll v2=Div(unit[k].Min,val);
			if(unit[k].Max-v1==unit[k].Min-v2){
				reg ll temp=unit[k].Min-v2;
				Add(k,l,r,-temp);
				return;
			}
		}
		pushdown(k,l,r);
		if(L<=mid)
			Update_Div(lson,l,mid,L,R,val);
		if(R>mid)
			Update_Div(rson,mid+1,r,L,R,val);
		pushup(k);
		return;
	}
	inline ll QueryMin(reg int k,reg int l,reg int r,reg int L,reg int R){
		if(L<=l&&r<=R)
			return unit[k].Min;
		pushdown(k,l,r);
		ll res=INF;
		if(L<=mid)
			res=min(res,QueryMin(lson,l,mid,L,R));
		if(R>mid)
			res=min(res,QueryMin(rson,mid+1,r,L,R));
		return res;
	}
	inline ll QuerySum(reg int k,reg int l,reg int r,reg int L,reg int R){
		if(L<=l&&r<=R)
			return unit[k].sum;
		pushdown(k,l,r);
		reg ll res=0;
		if(L<=mid)
			res+=QuerySum(lson,l,mid,L,R);
		if(R>mid)
			res+=QuerySum(rson,mid+1,r,L,R);
		return res;
	}
	#undef lson
	#undef rson
	#undef mid
};

SegmentTree T;

inline void Work(void){
	T.Build(1,1,n,a);
	while(Q--){
		static int opt,l,r,val;
		opt=read(),l=read()+1,r=read()+1;
		switch(opt){
			case 1:val=read(),T.Update_Add(1,1,n,l,r,val);break;
			case 2:val=read(),T.Update_Div(1,1,n,l,r,val);break;
			case 3:printf("%lld\n",T.QueryMin(1,1,n,l,r));break;
			case 4:printf("%lld\n",T.QuerySum(1,1,n,l,r));break;
			default:break;
		}
	}
	return;
}
