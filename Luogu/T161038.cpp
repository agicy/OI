#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef unsigned int uint;
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return res;
}

const int MAXN=1e5+7;
const int inf=0x3f3f3f3f;

int n;

namespace SegmentTree{
	#define lson ( (k) << 1 )
	#define rson ( (k) << 1 | 1 )
	#define mid ( ( (l) + (r) ) >> 1 )
	struct Node{
		uint v[8];
		int a[3];
		#define v(x) unit[(x)].v
		#define a(x) unit[(x)].a
	};
	Node unit[MAXN<<2];
	inline void pushup(reg int k){
		v(k)[0]=v(lson)[0]+v(rson)[0],v(k)[1]=v(lson)[1]+v(rson)[1],v(k)[2]=v(lson)[2]+v(rson)[2],v(k)[3]=v(lson)[3]+v(rson)[3],v(k)[4]=v(lson)[4]+v(rson)[4],v(k)[5]=v(lson)[5]+v(rson)[5],v(k)[6]=v(lson)[6]+v(rson)[6],v(k)[7]=v(lson)[7]+v(rson)[7];
		return;
	}
	inline void build(reg int k,reg int l,reg int r){
		v(k)[0]=r-l+1;
		if(l==r)
			return;
		build(lson,l,mid),build(rson,mid+1,r);
		return;
	}
	inline void add(reg int k,const int& id,reg int x){
		switch(id){
			case 0:{
				a(k)[0]+=x;
				v(k)[1]+=v(k)[0]*x,v(k)[3]+=v(k)[2]*x,v(k)[5]+=v(k)[4]*x,v(k)[7]+=v(k)[6]*x;
				break;
			}
			case 1:{
				a(k)[1]+=x;
				v(k)[2]+=v(k)[0]*x,v(k)[3]+=v(k)[1]*x,v(k)[6]+=v(k)[4]*x,v(k)[7]+=v(k)[5]*x;
				break;
			}
			case 2:{
				a(k)[2]+=x;
				v(k)[4]+=v(k)[0]*x,v(k)[5]+=v(k)[1]*x,v(k)[6]+=v(k)[2]*x,v(k)[7]+=v(k)[3]*x;
				break;
			}
		}
		return;
	}
	inline void pushdown(reg int k){
		if(a(k)[0]){
			add(lson,0,a(k)[0]);
			add(rson,0,a(k)[0]);
			a(k)[0]=0;
		}
		if(a(k)[1]){
			add(lson,1,a(k)[1]);
			add(rson,1,a(k)[1]);
			a(k)[1]=0;
		}
		if(a(k)[2]){
			add(lson,2,a(k)[2]);
			add(rson,2,a(k)[2]);
			a(k)[2]=0;
		}
		return;
	}
	int L,R,id,val;
	inline void update(reg int k,reg int l,reg int r){
		if(L<=l&&r<=R){
			add(k,id,val);
			return;
		}
		pushdown(k);
		if(L<=mid)
			update(lson,l,mid);
		if(R>mid)
			update(rson,mid+1,r);
		pushup(k);
		return;
	}
	#undef lson
	#undef rson
	#undef mid
}

struct seq{
	int a[MAXN],S[MAXN];
	int top,sgn;
	inline void init(reg int _sgn){
		sgn=_sgn,a[0]=sgn*inf,S[0]=top=0;
		return;
	}
	inline void calc(reg int pos,reg int id){
		SegmentTree::L=SegmentTree::R=pos,SegmentTree::id=id,SegmentTree::val=a[pos]*sgn;
		SegmentTree::update(1,1,n);
		while((SegmentTree::val=(a[pos]-a[S[top]])*sgn)>0){
			SegmentTree::L=S[top-1]+1,SegmentTree::R=S[top],SegmentTree::update(1,1,n);
			--top;
		}
		S[++top]=pos;
		return;
	}
};

seq Max[3],Min[3];

int main(void){
	n=read();
	for(reg int i=1;i<=n;++i)
		Max[0].a[i]=Min[0].a[i]=read();
	for(reg int i=1;i<=n;++i)
		Max[1].a[i]=Min[1].a[i]=read();
	for(reg int i=1;i<=n;++i)
		Max[2].a[i]=Min[2].a[i]=read();
	reg uint ans=0;
	Max[0].init(1),Min[0].init(-1);
	Max[1].init(1),Min[1].init(-1);
	Max[2].init(1),Min[2].init(-1);
	SegmentTree::build(1,1,n);
	for(reg int i=1;i<=n;++i){
		Max[0].calc(i,0),Min[0].calc(i,0);
		Max[1].calc(i,1),Min[1].calc(i,1);
		Max[2].calc(i,2),Min[2].calc(i,2);
		ans+=SegmentTree::unit[1].v[7];
	}
	printf("%u\n",ans);
	return 0;
}