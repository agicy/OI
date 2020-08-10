#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(ch<'0'||'9'<ch)ch=getchar();
	while('0'<=ch&&ch<='9')res=10*res+ch-'0',ch=getchar();
	return res;
}

const int MAXN=2e5+5;

int n,m;
int a[MAXN];

namespace SegmentTree{
	const int MAXSIZE=40*MAXN;
	#define mid ( ( (l) + (r) ) >> 1 )
	struct Node{
		int lson,rson;
		ll cnt;
		#define lson(x) unit[(x)].lson
		#define rson(x) unit[(x)].rson
		#define cnt(x) unit[(x)].cnt
	};
	int tot;
	int root[MAXSIZE];
	Node unit[MAXSIZE];
	int top,S[MAXSIZE];
	inline int New(void){
		if(top)
			return S[top--];
		else
			return ++tot;
	}
	inline void update(reg int &k,reg int l,reg int r,reg int pos,reg ll val){
		if(!k)
			k=New();
		cnt(k)+=val;
		if(l==r)
			return;
		if(pos<=mid)
			update(lson(k),l,mid,pos,val);
		else
			update(rson(k),mid+1,r,pos,val);
		return;
	}
	inline int kth(reg int k,reg int l,reg int r,reg ll val){
		if(l==r)
			return l;
		if(val<=cnt(lson(k)))
			return kth(lson(k),l,mid,val);
		else
			return kth(rson(k),mid+1,r,val-cnt(lson(k)));
	}
	inline ll query(reg int k,reg int l,reg int r,reg int L,reg int R){
		if(L<=l&&r<=R)
			return cnt(k);
		reg ll res=0;
		if(lson(k)&&L<=mid)
			res+=query(lson(k),l,mid,L,R);
		if(rson(k)&&R>mid)
			res+=query(rson(k),mid+1,r,L,R);
		return res;
	}
	inline void del(reg int k){
		S[++top]=k;
		lson(k)=rson(k)=cnt(k)=0;
		return;
	}
	inline int merge(reg int x,reg int y){
		if(!x||!y)
			return x+y;
		cnt(x)+=cnt(y);
		lson(x)=merge(lson(x),lson(y));
		rson(x)=merge(rson(x),rson(y));
		del(y);
		return x;
	}
	inline void split(reg int x,reg int &y,reg ll k){
		if(x==0)
			return;
		y=New();
		if(k>cnt(lson(x)))
			split(rson(x),rson(y),k-cnt(lson(x)));
		else
			swap(rson(x),rson(y));
		if(k<cnt(lson(x)))
			split(lson(x),lson(y),k);
		cnt(y)=cnt(x)-k;
		cnt(x)=k;
		return;
	}
	#undef mid
}

using namespace SegmentTree;

int main(void){
	n=read(),m=read();
	for(reg int i=1;i<=n;++i){
		static int x;
		x=read();
		update(root[1],1,n,i,x);
	}
	reg int tot=1;
	while(m--){
		static ll opt,p,q,x,y,k,t;
		opt=read();
		switch(opt){
			case 0:{
				p=read(),x=read(),y=read();
				reg ll k1=query(root[p],1,n,1,y);
				reg ll k2=query(root[p],1,n,x,y);
				split(root[p],root[++tot],k1-k2);
				int tmp=0;
				split(root[tot],tmp,k2);
				root[p]=merge(root[p],tmp);
				break;
			}
			case 1:{
				p=read(),t=read();
				root[p]=merge(root[p],root[t]);
				break;
			}
			case 2:{
				p=read(),x=read(),q=read();
				update(root[p],1,n,q,x);
				break;
			}
			case 3:{
				p=read(),x=read(),y=read();
				printf("%lld\n",query(root[p],1,n,x,y));
				break;
			}
			case 4:{
				p=read(),k=read();
				if(cnt(root[p])<k)
					puts("-1");
				else
					printf("%d\n",kth(root[p],1,n,k));
				break;
			}
		}
	}
	return 0;
}