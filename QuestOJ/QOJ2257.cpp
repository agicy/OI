#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
inline int read(void){
	reg bool f=false;
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))f|=(ch=='-'),ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return f?-res:res;
}

const int MAXN=2e5+5;
const int MAXL=2e5+5;
const int p=1e9+7;

inline int add(reg int a,reg int b){
	reg int sum=a+b;
	return sum>=p?sum-p:sum;
}

inline int mul(reg int a,reg int b){
	return 1ll*a*b%p;
}

int base2[MAXN];

namespace SegmentTree{
	#define lson ( (k) << 1 )
	#define rson ( (k) << 1 | 1 )
	#define mid ( ( (l) + (r) ) >> 1 )
	struct Node{
		int sum;
		int hash;
		int tag;
		#define sum(x) unit[(x)].sum
		#define hash(x) unit[(x)].hash
		#define tag(x) unit[(x)].tag
	};
	Node unit[MAXL<<2];
	inline void pushup(reg int k,reg int l,reg int r){
		sum(k)=sum(lson)+sum(rson);
		hash(k)=add(mul(hash(lson),base2[r-mid]),hash(rson));
		return;
	}
	inline void build(reg int k,reg int l,reg int r,reg char a[]){
		tag(k)=-1;
		if(l==r){
			if(a[l]=='1')
				sum(k)=hash(k)=1;
			else
				sum(k)=hash(k)=0;
			return;
		}
		build(lson,l,mid,a),build(rson,mid+1,r,a);
		pushup(k,l,r);
		return;
	}
	inline void set0(reg int k,reg int l,reg int r){
		sum(k)=0;
		hash(k)=0;
		tag(k)=0;
		return;
	}
	inline void set1(reg int k,reg int l,reg int r){
		sum(k)=r-l+1;
		hash(k)=add(base2[r-l+1],p-1);
		tag(k)=1;
		return;
	}
	inline void pushdown(reg int k,reg int l,reg int r){
		if(tag(k)==0){
			set0(lson,l,mid);
			set0(rson,mid+1,r);
		}
		if(tag(k)==1){
			set1(lson,l,mid);
			set1(rson,mid+1,r);
		}
		tag(k)=-1;
	}
	inline void update0(reg int k,reg int l,reg int r,reg int L,reg int R){
		if(L<=l&&r<=R){
			set0(k,l,r);
			return;
		}
		pushdown(k,l,r);
		if(L<=mid)
			update0(lson,l,mid,L,R);
		if(R>mid)
			update0(rson,mid+1,r,L,R);
		pushup(k,l,r);
		return;
	}
	inline void update1(reg int k,reg int l,reg int r,reg int L,reg int R){
		if(L<=l&&r<=R){
			set1(k,l,r);
			return;
		}
		pushdown(k,l,r);
		if(L<=mid)
			update1(lson,l,mid,L,R);
		if(R>mid)
			update1(rson,mid+1,r,L,R);
		pushup(k,l,r);
		return;
	}
	inline int querySum(reg int k,reg int l,reg int r,reg int L,reg int R){
		if(L<=l&&r<=R)
			return sum(k);
		pushdown(k,l,r);
		if(L<=mid&&mid<R){
			reg int lef=querySum(lson,l,mid,L,R),rig=querySum(rson,mid+1,r,L,R);
			return lef+rig;
		}
		else if(L<=mid)
			return querySum(lson,l,mid,L,R);
		else
			return querySum(rson,mid+1,r,L,R);
	}
	inline int queryHash(reg int k,reg int l,reg int r,reg int L,reg int R){
		if(L<=l&&r<=R)
			return hash(k);
		pushdown(k,l,r);
		if(L<=mid&&mid<R){
			reg int lef=queryHash(lson,l,mid,L,mid),rig=queryHash(rson,mid+1,r,mid+1,R);
			return add(mul(lef,base2[R-mid]),rig);
		}
		else if(L<=mid)
			return queryHash(lson,l,mid,L,R);
		else
			return queryHash(rson,mid+1,r,L,R);
	}
	inline void print(reg int k,reg int l,reg int r){
		if(l==r){
			putchar(sum(k)+'0');
			return;
		}
		pushdown(k,l,r);
		print(lson,l,mid),print(rson,mid+1,r);
		return;
	}
	#undef lson
	#undef rson
	#undef mid
}

int n;
char str[MAXL];

int main(void){
	scanf("%s",str+1);
	reg int len=strlen(str+1);
	base2[0]=1;
	for(reg int i=1;i<=len;++i)
		base2[i]=add(base2[i-1],base2[i-1]);
	n=read();
	SegmentTree::build(1,1,len,str);
	while(n--){
		static int opt,l,r;
		opt=read(),l=read(),r=read();
		switch(opt){
			case 1:{
				reg int cnt1=SegmentTree::querySum(1,1,len,l,r);
				if(cnt1!=0&&cnt1!=r-l+1){
					SegmentTree::update1(1,1,len,l,l+cnt1-1);
					SegmentTree::update0(1,1,len,l+cnt1,r);
				}
				break;
			}
			case 2:{
				reg int cnt1=SegmentTree::querySum(1,1,len,l,r);
				if(cnt1!=0&&cnt1!=r-l+1){
					SegmentTree::update0(1,1,len,l,r-cnt1);
					SegmentTree::update1(1,1,len,r-cnt1+1,r);
				}
				break;
			}
			case 3:{
				printf("%d\n",SegmentTree::queryHash(1,1,len,l,r));
				break;
			}
		}
	}
	return 0;
}