#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(ch<'0'||'9'<ch)ch=getchar();
	while('0'<=ch&&ch<='9')res=10*res+ch-'0',ch=getchar();
	return res;
}

const int MAXN=1e5+5;

int n,m;
char str[MAXN];

namespace SegmentTree{
	#define lson ( (k) << 1 )
	#define rson ( (k) << 1 | 1 )
	#define mid ( ( (l) + (r) ) >> 1 )
	struct Node{
		int T[26];
		int tag;
		#define T(x) unit[(x)].T
		#define tag(x) unit[(x)].tag
	};
	Node unit[MAXN<<2];
	inline void pushup(reg int k){
		for(reg int i=0;i<26;++i)
			T(k)[i]=T(lson)[i]+T(rson)[i];
		return;
	}
	inline void build(reg int k,reg int l,reg int r,reg char str[]){
		tag(k)=-1;
		if(l==r){
			++T(k)[str[l]-'a'];
			return;
		}
		build(lson,l,mid,str),build(rson,mid+1,r,str);
		pushup(k);
		return;
	}
	inline void set(reg int k,reg int l,reg int r,reg int val){
		for(reg int i=0;i<26;++i)
			T(k)[i]=0;
		T(k)[val]=r-l+1;
		tag(k)=val;
		return;
	}
	inline void pushdown(reg int k,reg int l,reg int r){
		if(tag(k)!=-1){
			set(lson,l,mid,tag(k));
			set(rson,mid+1,r,tag(k));
			tag(k)=-1;
		}
		return;
	}
	inline void update(reg int k,reg int l,reg int r,reg int L,reg int R,reg int val){
		if(L<=l&&r<=R){
			set(k,l,r,val);
			return;
		}
		pushdown(k,l,r);
		if(L<=mid)
			update(lson,l,mid,L,R,val);
		if(R>mid)
			update(rson,mid+1,r,L,R,val);
		pushup(k);
		return;
	}
	inline Node query(reg int k,reg int l,reg int r,reg int L,reg int R){
		if(L<=l&&r<=R)
			return unit[k];
		pushdown(k,l,r);
		if(L<=mid&&mid<R){
			Node le=query(lson,l,mid,L,R),ri=query(rson,mid+1,r,L,R);
			for(reg int i=0;i<26;++i)
				le.T[i]+=ri.T[i];
			return le;
		}
		else if(L<=mid)
			return query(lson,l,mid,L,R);
		else
			return query(rson,mid+1,r,L,R);
	}
	inline void print(reg int k,reg int l,reg int r){
		if(l==r){
			for(reg int i=0;i<26;++i)
				if(T(k)[i]){
					putchar('a'+i);
					break;
				}
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

using namespace SegmentTree;

int main(void){
	n=read(),m=read();
	scanf("%s",str+1);
	build(1,1,n,str);
	while(m--){
		static int l,r,x;
		static Node tmp;
		l=read(),r=read(),x=read();
		if(x==1){
			tmp=query(1,1,n,l,r);
			reg int lptr=l;
			for(reg int i=0;i<26;++i)
				if(tmp.T[i]){
					update(1,1,n,lptr,lptr+tmp.T[i]-1,i);
					lptr+=tmp.T[i];
				}
		}
		else{
			tmp=query(1,1,n,l,r);
			reg int rptr=r;
			for(reg int i=0;i<26;++i)
				if(tmp.T[i]){
					update(1,1,n,rptr-tmp.T[i]+1,rptr,i);
					rptr-=tmp.T[i];
				}
		}
	}
	print(1,1,n);
	putchar('\n');
	return 0;
}