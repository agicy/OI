#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
typedef unsigned long long ull;
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

inline void Read(void);
inline void Work(void);

int main(void){
	Read();
	Work();
	return 0;
}

int n,m;

inline void Read(void){
	n=read(),m=read();
	return;
}

struct SegmentTree{
	#define lson ( (k) << 1 )
	#define rson ( (k) << 1 | 1 )
	#define mid ( ( (l) + (r) ) >> 1 )
	struct Node{
		int sum;
		bool tag;
		inline Node(reg int sum=0,reg bool tag=false):sum(sum),tag(tag){
			return;
		}
	};
	Node unit[MAXN<<2];
	inline void pushup(reg int k){
		unit[k]=Node(unit[lson].sum+unit[rson].sum,false);
		return;
	}
	inline void Change(reg int k,reg int l,reg int r){
		unit[k]=Node((r-l+1)-unit[k].sum,!unit[k].tag);
		return;
	}
	inline void pushdown(reg int k,reg int l,reg int r){
		if(unit[k].tag){
			Change(lson,l,mid);
			Change(rson,mid+1,r);
			unit[k].tag=false;
		}
		return;
	}
	inline void Update(reg int k,reg int l,reg int r,reg int L,reg int R){
		if(L<=l&&r<=R){
			Change(k,l,r);
			return;
		}
		pushdown(k,l,r);
		if(L<=mid)
			Update(lson,l,mid,L,R);
		if(R>mid)
			Update(rson,mid+1,r,L,R);
		pushup(k);
		return;
	}
	inline int Query(reg int k,reg int l,reg int r,reg int L,reg int R){
		if(L<=l&&r<=R)
			return unit[k].sum;
		pushdown(k,l,r);
		reg int res=0;
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

SegmentTree T;

inline void Work(void){
	while(m--){
		static int opt,a,b;
		opt=read(),a=read(),b=read();
		switch(opt){
			case 0:T.Update(1,1,n,a,b);break;
            case 1:printf("%d\n",T.Query(1,1,n,a,b));break;
            default:break;
		}
	}
	return;
}
