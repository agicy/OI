#include<bits/stdc++.h>
using namespace std;
#define reg register
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(ch<'0'||'9'<ch)ch=getchar();
	while('0'<=ch&&ch<='9')res=10*res+ch-'0',ch=getchar();
	return res;
}

const int MAXN=100000+5;

int n,m;
char str[MAXN];

namespace SegmentTree{
	#define lson ( (k) << 1 )
	#define rson ( (k) << 1 | 1 )
	#define mid ( ( (l) + (r) ) >> 1 )
	int val[26][MAXN<<3];
	int tag[26][MAXN<<3];
	inline void pushup(reg int id,reg int k){
		val[id][k]=val[id][lson]+val[id][rson];
		return;
	}
	inline void Set0(reg int id,reg int k){
		val[id][k]=0;
		tag[id][k]=-1;
		return;
	}
	inline void Set1(reg int id,reg int k,reg int l,reg int r){
		val[id][k]=r-l+1;
		tag[id][k]=1;
		return;
	}
	inline void pushdown(reg int id,reg int k,reg int l,reg int r){
		if(tag[id][k]){
			if(tag[id][k]==1){
				Set1(id,lson,l,mid);
				Set1(id,rson,mid+1,r);
			}
			if(tag[id][k]==-1){
				Set0(id,lson);
				Set0(id,rson);
			}
			tag[id][k]=0;
		}
		return;
	}
	inline void Build(reg int id,reg int k,reg int l,reg int r){
		if(l==r){
			val[id][k]=((str[l]-'a')==id);
			return;
		}
		Build(id,lson,l,mid);
		Build(id,rson,mid+1,r);
		pushup(id,k);
		return;
	}
	inline void Update0(reg int id,reg int k,reg int l,reg int r,reg int L,reg int R){
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
		if(L<=l&&r<=R)
			return val[id][k];
		pushdown(id,k,l,r);
		reg int res=0;
		if(L<=mid)
			res+=Query(id,lson,l,mid,L,R);
		if(R>mid)
			res+=Query(id,rson,mid+1,r,L,R);
		return res;
	}
	inline void Print(reg int k,reg int l,reg int r){
		if(l==r){
			for(reg int i=0;i<26;++i)
				if(val[i][k]){
					putchar(i+'a');
					break;
				}
			return;
		}
		for(reg int i=0;i<26;++i)
			pushdown(i,k,l,r);
		Print(lson,l,mid);
		Print(rson,mid+1,r);
		return;
	}
	#undef lson
	#undef rson
	#undef mid
}

using namespace SegmentTree;

int main(void){
	scanf("%d%d%s",&n,&m,str+1);
	for(reg int i=0;i<26;++i)
		Build(i,1,1,n);
	while(m--){
		static int l,r,k,a[26];
		scanf("%d%d%d",&l,&r,&k);
		memset(a,0,sizeof(a));
		for(reg int i=0;i<26;++i){
			a[i]=Query(i,1,1,n,l,r);
			Update0(i,1,1,n,l,r);
		}
		switch(k){
			case 0:{
				reg int rptr=r;
				for(reg int i=0;i<26;++i){
					if(a[i])
						Update1(i,1,1,n,rptr-a[i]+1,rptr);
					rptr-=a[i];
				}
				break;
			}
			case 1:{
				reg int lptr=l;
				for(reg int i=0;i<26;++i){
					if(a[i])
						Update1(i,1,1,n,lptr,lptr+a[i]-1);
					lptr+=a[i];
				}
				break;
			}
		}
	}
	Print(1,1,n);
	putchar('\n');
	return 0;
}