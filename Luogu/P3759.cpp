#include<bits/stdc++.h>
using namespace std;
#define reg register
#define MOD 1000000007
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(ch<'0'||'9'<ch)ch=getchar();
	while('0'<=ch&&ch<='9')res=10*res+ch-'0',ch=getchar();
	return res;
}

inline int Add(reg int x,reg int y){
	reg int sum=x+y;
	return sum>=MOD?sum-MOD:sum;
}

inline int Dec(reg int x,reg int y){
	reg int sum=x-y;
	return sum<0?sum+MOD:sum;
}

inline int Mul(reg int x,reg int y){
	return 1ll*x*y%MOD;
}

const int MAXN=50000+5;

namespace SegmentTree{
	const int MAXA=500000+5;
	namespace SegmentTree{
		#define mid ( ( (l) + (r) ) >> 1 )
		struct Node{
			int lson,rson;
			int cntP,cntB;
			inline void Init(void){
				lson=rson=cntP=cntB=0;
				return;
			}
			#define lson(x) unit[(x)].lson
			#define rson(x) unit[(x)].rson
			#define cntP(x) unit[(x)].cntP
			#define cntB(x) unit[(x)].cntB
		};
		const int MAXSIZE=MAXN*256;
		int tot;
		int root[MAXSIZE];
		Node unit[MAXSIZE];
		int top,Stack[MAXSIZE];
		inline void Del(reg int &k){
			unit[k].Init();
			Stack[++top]=k;
			k=0;
			return;
		}
		inline int New(void){
			if(top)
				return Stack[top--];
			else
				return ++tot;
		}
		inline void Update(reg int &k,reg int l,reg int r,reg int pos,reg int valP,reg int valB){
			if(!k)
				k=New();
			cntP(k)=Add(cntP(k),valP),cntB(k)=Add(cntB(k),valB);
			if(l==r){
				if(!cntB(k))
					Del(k);
				return;
			}
			if(pos<=mid)
				Update(lson(k),l,mid,pos,valP,valB);
			else
				Update(rson(k),mid+1,r,pos,valP,valB);
			if(!cntB(k))
				Del(k);
			return;
		}
		inline pair<int,int> Query(reg int k,reg int l,reg int r,reg int L,reg int R){
			if(!k)
				return make_pair(0,0);
			if(L<=l&&r<=R)
				return make_pair(cntP(k),cntB(k));
			if(L<=mid&&mid<R){
				pair<int,int> left=Query(lson(k),l,mid,L,R),right=Query(rson(k),mid+1,r,L,R);
				return make_pair(Add(left.first,right.first),Add(left.second,right.second));
			}
			else if(L<=mid)
				return Query(lson(k),l,mid,L,R);
			else
				return Query(rson(k),mid+1,r,L,R);
		}
		#undef lson
		#undef rson
		#undef cntP
		#undef cntB
		#undef mid
	}
	using SegmentTree::root;
	#define lson ( (k) << 1 )
	#define rson ( (k) << 1 | 1 )
	#define mid ( ( (l) + (r) ) >> 1 )
	inline void Update(reg int k,reg int l,reg int r,reg int pos,reg int a,reg int v){
		SegmentTree::Update(root[k],1,MAXA,a,v,1);
		if(l==r)
			return;
		if(pos<=mid)
			Update(lson,l,mid,pos,a,v);
		else
			Update(rson,mid+1,r,pos,a,v);
		return;
	}
	inline void Del(reg int k,reg int l,reg int r,reg int pos,reg int a,reg int v){
		SegmentTree::Update(root[k],1,MAXA,a,-v,-1);
		if(l==r)
			return;
		if(pos<=mid)
			Del(lson,l,mid,pos,a,v);
		else
			Del(rson,mid+1,r,pos,a,v);
		return;
	}
	inline pair<int,int> Query(reg int k,reg int l,reg int r,reg int L,reg int R,reg int inL,reg int inR){
		if(L<=l&&r<=R)
			return SegmentTree::Query(root[k],1,MAXA,inL,inR);
		if(L<=mid&&mid<R){
			pair<int,int> left=Query(lson,l,mid,L,R,inL,inR),right=Query(rson,mid+1,r,L,R,inL,inR);
			return make_pair(Add(left.first,right.first),Add(left.second,right.second));
		}
		else if(L<=mid)
			return Query(lson,l,mid,L,R,inL,inR);
		else
			return Query(rson,mid+1,r,L,R,inL,inR);
	}
	#undef lson
	#undef rson
	#undef mid
}

using namespace SegmentTree;

int n,m;
int a[MAXN],v[MAXN];

int main(void){
	n=read(),m=read();
	for(reg int i=1;i<=n;++i)
		a[i]=read(),v[i]=read();
	for(reg int i=1;i<=n;++i)
		Update(1,1,n,i,a[i],v[i]);
	reg int ans=0;
	for(reg int i=1;i<=n;++i){
		pair<int,int> P=Query(1,1,n,i+1,n,1,a[i]);
		ans=Add(ans,Add(Mul(v[i],P.second),P.first));
 	}
	while(m--){
		static int x,y;
		x=read(),y=read();
		if(x>y)
			swap(x,y);
		if(x!=y){
			int L=a[x],R=a[y];
			reg int Min=min(L,R),Max=max(L,R);
			reg int cntP,cntB;
			pair<int,int> tP;

			tP=Query(1,1,n,x,y,Min+1,Max-1);
			cntP=tP.first,cntB=tP.second;

			if(Min==L)
				ans=Add(ans,Add(Mul(2,cntP),Mul((cntB+1),(Add(v[x],v[y])))));
			else
				ans=Dec(ans,Add(Mul(2,cntP),Mul((cntB+1),(Add(v[x],v[y])))));

			tP=Query(1,1,n,x,y,1,Min-1);
			cntB=tP.second;
			ans=Add(ans,Mul(cntB,Dec(v[y],v[x])));

			tP=Query(1,1,n,x,y,Max+1,n);
			cntB=tP.second;
			ans=Add(ans,Mul(cntB,Dec(v[x],v[y])));
			Del(1,1,n,x,a[x],v[x]),Del(1,1,n,y,a[y],v[y]);
			Update(1,1,n,x,a[y],v[y]),Update(1,1,n,y,a[x],v[x]);
			swap(a[x],a[y]),swap(v[x],v[y]);
		}
		printf("%d\n",ans);
	}
	return 0;
}