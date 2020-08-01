#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
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

const int MAXN=5e4+5;

struct querys{
	int l,r,opt,id;
	ll c;
	inline void Read(void){
		opt=read(),l=read(),r=read(),c=read();
		return;
	}
};

int n,m;
ll ans[MAXN];
querys q[MAXN],q1[MAXN],q2[MAXN];

namespace SegmentTree{
	#define lson ( (k) << 1 )
	#define rson ( (k) << 1 | 1 )
	#define mid ( ( (l) + (r) ) >> 1 )
	struct Node{
		ll val,tag;
		#define val(x) unit[(x)].val
		#define tag(x) unit[(x)].tag
	};
	Node unit[MAXN<<2];
	inline void pushup(reg int k){
		val(k)=val(lson)+val(rson);
		return;
	}
	inline void add(reg int k,reg int l,reg int r,reg ll V){
		val(k)+=(r-l+1)*V;
		tag(k)+=V;
		return;
	}
	inline void pushdown(reg int k,reg int l,reg int r){
		if(tag(k)){
			add(lson,l,mid,tag(k));
			add(rson,mid+1,r,tag(k));
			tag(k)=0;
		}
		return;
	}
	inline void update(reg int k,reg int l,reg int r,reg int L,reg int R,reg ll V){
		if(L<=l&&r<=R){
			add(k,l,r,V);
			return;
		}
		pushdown(k,l,r);
		if(L<=mid)
			update(lson,l,mid,L,R,V);
		if(R>mid)
			update(rson,mid+1,r,L,R,V);
		pushup(k);
		return;
	}
	inline ll query(reg int k,reg int l,reg int r,reg int L,reg int R){
		if(L<=l&&r<=R)
			return val(k);
		pushdown(k,l,r);
		reg ll res=0;
		if(L<=mid)
			res+=query(lson,l,mid,L,R);
		if(R>mid)
			res+=query(rson,mid+1,r,L,R);
		return res;
	}
	#undef lson
	#undef rson
	#undef mid
}

ll tmp[MAXN];

inline void Solve(reg int l,reg int r,reg ll L,reg ll R){
	if(l>r)
		return;
	if(L==R){
		for(reg int i=l;i<=r;++i)
			if(q[i].opt==2)
				ans[q[i].id]=L;
		return;
	}
	reg ll mid=(L+R)>>1;
	for(reg int i=l;i<=r;++i)
		switch(q[i].opt){
			case 1:{
				if(q[i].c>mid)
					SegmentTree::update(1,1,n,q[i].l,q[i].r,1);
				break;
			}
			case 2:{
				tmp[i]=SegmentTree::query(1,1,n,q[i].l,q[i].r);
				break;
			}
		}
	for(reg int i=l;i<=r;++i)
		if(q[i].opt==1&&q[i].c>mid)
			SegmentTree::update(1,1,n,q[i].l,q[i].r,-1);
	reg int cnt1=0,cnt2=0;
	for(reg int i=l;i<=r;++i)
		switch(q[i].opt){
			case 1:{
				if(q[i].c<=mid)
					q1[cnt1++]=q[i];
				else
					q2[cnt2++]=q[i];
				break;
			}
			case 2:{
				if(tmp[i]>=q[i].c)
					q2[cnt2++]=q[i];
				else{
					q[i].c-=tmp[i];
					q1[cnt1++]=q[i];
				}
				break;
			}
		}
	for(reg int i=0;i<cnt1;++i)
		q[l+i]=q1[i];
	for(reg int i=0;i<cnt2;++i)
		q[l+cnt1+i]=q2[i];
	Solve(l,l+cnt1-1,L,mid),Solve(l+cnt1,r,mid+1,R);
	return;
}
int main(){
	n=read(),m=read();
	reg int tot=0;
	for(reg int i=1;i<=m;++i){
		q[i].Read();
		if(q[i].opt==2)
			q[i].id=tot++;
	}
	Solve(1,m,0,n);
	for(reg int i=0;i<tot;++i)
		printf("%lld\n",ans[i]);
	return 0;
}