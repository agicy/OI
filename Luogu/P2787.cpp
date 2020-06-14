#include<bits/stdc++.h>
using namespace std;
#define reg register
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(ch<'0'||'9'<ch)ch=getchar();
	while('0'<=ch&&ch<='9')res=10*res+ch-'0',ch=getchar();
	return res;
}

const int MAXN=50000+5;

int n,m;
char str[MAXN];

namespace SegmentTree{
	#define lson ( (k) << 1 )
	#define rson ( (k) << 1 | 1 )
	#define mid ( ( (l) + (r) ) >> 1 )
	int sum[26][MAXN<<3],tag[26][MAXN<<3];
	inline void pushup(reg int id,reg int k){
		sum[id][k]=sum[id][lson]+sum[id][rson];
		return;
	}
	inline void Set0(reg int id,reg int k){
		sum[id][k]=0;
		tag[id][k]=-1;
		return;
	}
	inline void Set1(reg int id,reg int k,reg int l,reg int r){
		sum[id][k]=r-l+1;
		tag[id][k]=1;
		return;
	}
	inline void pushdown(reg int id,reg int k,reg int l,reg int r){
		if(tag[id][k]){
			if(tag[id][k]==-1){
				Set0(id,lson);
				Set0(id,rson);
			}
			else if(tag[id][k]==1){
				Set1(id,lson,l,mid);
				Set1(id,rson,mid+1,r);
			}
			tag[id][k]=0;
		}
		return;
	}
	inline void Build(reg int id,reg int k,reg int l,reg int r){
		if(l==r){
			sum[id][k]=((str[l]-'a')==id);
			return;
		}
		Build(id,lson,l,mid);
		Build(id,rson,mid+1,r);
		pushup(id,k);
		return;
	}
	inline void Update0(reg int id,reg int k,reg int l,reg int r,reg int L,reg int R){
		if(tag[id][k]==-1)
			return;
		if(R<l||r<L)
			return;
		if(L<=l&&r<=R){
			Set0(id,k);
			return;
		}
		pushdown(id,k,l,r);
		if(L<=mid)
			Update0(id,lson,l,mid,L,R);
		if(R>mid)
			Update0(id,rson,mid+1,r,L,R);
		pushup(id,k);
		return;
	}
	inline void Update1(reg int id,reg int k,reg int l,reg int r,reg int L,reg int R){
		if(tag[id][k]==1)
			return;
		if(R<l||r<L)
			return;
		if(L<=l&&r<=R){
			Set1(id,k,l,r);
			return;
		}
		pushdown(id,k,l,r);
		if(L<=mid)
			Update1(id,lson,l,mid,L,R);
		if(R>mid)
			Update1(id,rson,mid+1,r,L,R);
		pushup(id,k);
		return;
	}
	inline int Query(reg int id,reg int k,reg int l,reg int r,reg int L,reg int R){
		if(!sum[id][k])
			return 0;
		if(R<l||r<L)
			return 0;
		if(L<=l&&r<=R)
			return sum[id][k];
		pushdown(id,k,l,r);
		reg int res=0;
		if(L<=mid)
			res+=Query(id,lson,l,mid,L,R);
		if(R>mid)
			res+=Query(id,rson,mid+1,r,L,R);
		return res;
	}
	#undef lson
	#undef rson
	#undef mid
}

using namespace SegmentTree;

int main(void){
	n=read(),m=read();
	scanf("%s",str+1);
	for(reg int i=1;i<=n;++i)
		str[i]|=32;
	for(reg int i=0;i<26;++i)
		Build(i,1,1,n);
	while(m--){
		static char k[4];
		static int opt,x,y;
		opt=read(),x=read(),y=read();
		if(opt!=3)
			scanf("%s",k),k[0]|=32;
		switch(opt){
			case 1:{
				printf("%d\n",Query(k[0]-'a',1,1,n,x,y));
				break;
			}
			case 2:{
				for(reg int i=0;i<26;++i)
					Update0(i,1,1,n,x,y);
				Update1(k[0]-'a',1,1,n,x,y);
				break;
			}
			case 3:{
				static int T[26];
				for(reg int i=0;i<26;++i){
					T[i]=Query(i,1,1,n,x,y);
					Update0(i,1,1,n,x,y);
				}
				reg int lptr=x;
				for(reg int i=0;i<26;++i){
					if(T[i])
						Update1(i,1,1,n,lptr,lptr+T[i]-1);
					lptr+=T[i];
				}
				break;
			}
			default:break;
		}
	}
	return 0;
}