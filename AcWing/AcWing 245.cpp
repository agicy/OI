#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
typedef unsigned long long ull;
#define INF 0X3F3F3F3F
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

const int MAXN=500000+5;
const int MAXM=100000+5;

struct SegmentTree{
	#define lson (k<<1)
	#define rson (k<<1|1)
	#define mid ((l+r)>>1)
	struct Node{
		int sum,lsum,rsum,data;
		inline Node(void){
			sum=lsum=rsum=data=0;
			return;
		}
		inline Node(reg int a){
			sum=lsum=rsum=data=a;
			return;
		}
	};
	Node unit[MAXN<<2];
	inline void pushup(reg int k){
		unit[k].sum=unit[lson].sum+unit[rson].sum;
		unit[k].lsum=max(unit[lson].lsum,unit[lson].sum+unit[rson].lsum);
		unit[k].rsum=max(unit[rson].rsum,unit[rson].sum+unit[lson].rsum);
		unit[k].data=max(unit[lson].rsum+unit[rson].lsum,max(unit[lson].data,unit[rson].data));
		return;
	}
	inline void Build(reg int k,reg int l,reg int r,reg int a[]){
		if(l==r){
			unit[k]=Node(a[l]);
			return;
		}
		Build(lson,l,mid,a);
		Build(rson,mid+1,r,a);
		pushup(k);
		return;
	}
	inline void Update(reg int k,reg int l,reg int r,reg int pos,reg int val){
		if(l==r&&l==pos){
			unit[k]=Node(val);
			return;
		}
		if(pos<=mid)
			Update(lson,l,mid,pos,val);
		else
			Update(rson,mid+1,r,pos,val);
		pushup(k);
		return;
	}
	inline Node Query(reg int k,reg int l,reg int r,reg int L,reg int R){
		if(L<=l&&r<=R)
			return unit[k];
		Node a(-INF),b(-INF),c(0);
		if(L<=mid){
			a=Query(lson,l,mid,L,R);
			c.sum+=a.sum;
		}
		if(R>mid){
			b=Query(rson,mid+1,r,L,R);
			c.sum+=b.sum;
		}
		c.data=max(max(a.data,b.data),a.rsum+b.lsum);
		c.lsum=max(a.lsum,b.lsum+a.sum);
		if(L>mid)
			c.lsum=max(c.lsum,b.lsum);
		c.rsum=max(b.rsum,a.rsum+b.sum);
		if(R<=mid)
			c.rsum=max(c.rsum,a.rsum);
		return c;
	}
	#undef lson
	#undef rson
	#undef mid
};

int n,m;
int a[MAXN];
SegmentTree T;

int main(void){
	n=read(),m=read();
	for(reg int i=1;i<=n;++i)
		a[i]=read();
	T.Build(1,1,n,a);
	while(m--){
		static int k,x,y;
		k=read(),x=read(),y=read();
		if(k==1){
			if(x>y)
				swap(x,y);
			printf("%d\n",T.Query(1,1,n,x,y).data);
		}
		if(k==2)
			T.Update(1,1,n,x,y);
	}
	return 0;
}