#include<bits/stdc++.h>
using namespace std;
#define reg register
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

const int MAXN=100000+1;
const int MAXM=300000+1;
const int MAXX=500+1;
const int delta=MAXN*MAXX;

namespace SegmentTree{
	#define mid ( ( (l) + (r) ) >> 1 )
	int tot,root;
	struct Node{
		int lson,rson;
		int tag;
		#define lson(x) unit[(x)].lson
		#define rson(x) unit[(x)].rson
		#define tag(x) unit[(x)].tag
	};
	Node unit[delta*2];
	inline void Update(reg int &k,reg int l,reg int r,reg int L,reg int R,reg int val){
		if(r<L||R<l)
			return;
		if(!k){
			k=++tot;
			lson(k)=rson(k)=tag(k)=0;
		}
		if(L<=l&&r<=R){
			tag(k)+=val;
			return;
		}
		if(L<=mid)
			Update(lson(k),l,mid,L,R,val);
		if(R>mid)
			Update(rson(k),mid+1,r,L,R,val);
		return;
	}
	inline int Query(reg int k,reg int l,reg int r,reg int pos){
		if(!k)
			return 0;
		if(l==r)
			return tag(k);
		if(pos<=mid)
			return Query(lson(k),l,mid,pos)+tag(k);
		else
			return Query(rson(k),mid+1,r,pos)+tag(k);
	}
	inline void Init(void){
		tot=root=0;
	}
	#undef mid
}

using namespace SegmentTree;

struct Querys{
	char opt;
	int x[2];
};

Querys Q[MAXM];

int n,m,ans[MAXM];
int x[2][MAXN];

inline int sgn(reg int x){
	return x>=0?(x>0?1:0):-1;
}

inline void Solve(reg int f){
	static int sum[MAXN];
	Init();
	sum[0]=1;
	for(reg int i=1;i<=n;++i)
		sum[i]=sum[i-1]+x[f][i];
	for(reg int i=2;i<=n;++i)
		Update(root,0,delta<<1,min(sum[i-1],sum[i])+delta,delta+max(sum[i-1],sum[i]),1);
	reg int Ans=0,tag=0,pos=1;
	for(reg int i=1;i<=n;++i)
		if(sgn(sum[i-1])!=sgn(sum[i]))
			++Ans;
	for(reg int i=1;i<=m;++i)
		switch(Q[i].opt){
			case 'B':{
				if(pos==1)
					break;
				--pos;
				sum[pos]-=tag;
				Update(root,0,delta<<1,min(sum[pos+1],sum[pos])+delta,delta+max(sum[pos+1],sum[pos]),1);
				break;
			}
			case 'F':{
				if(pos==n)
					break;
				Update(root,0,delta<<1,min(sum[pos+1],sum[pos])+delta,delta+max(sum[pos+1],sum[pos]),-1);
				sum[pos]+=tag;
				++pos;
				break;
			}
			case 'C':{
				Ans-=Query(root,0,delta<<1,delta-tag);
				if(sgn(sum[pos-1])!=sgn(sum[pos]+tag))
					--Ans;
				tag+=Q[i].x[f]-x[f][pos];
				x[f][pos]=Q[i].x[f];
				Ans+=Query(root,0,delta<<1,delta-tag);
				if(sgn(sum[pos-1])!=sgn(sum[pos]+tag))
					++Ans;
				break;
			}
			case 'Q':{
				ans[i]+=Ans;
				break;
			}
			default:break;
	 	}
	return;
}

int main(void){
	n=read();
	for(reg int i=1;i<=n;++i)
		x[0][i]=read(),x[1][i]=read();
	m=read();
	for(reg int i=1;i<=m;++i){
		static char opt;
		do
			opt=getchar();
		while(opt!='B'&&opt!='F'&&opt!='C'&&opt!='Q');
		Q[i].opt=opt;
		if(opt=='C')
			Q[i].x[0]=read(),Q[i].x[1]=read();
	}
	Solve(0),Solve(1);
	for(reg int i=1;i<=m;++i)
		if(Q[i].opt=='Q')
			printf("%d\n",ans[i]);
	return 0;
}