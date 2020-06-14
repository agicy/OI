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

const int MAXN=20000+5;

int n,m;
int a[MAXN];
int cnt,V[MAXN];
vector<int> pos[MAXN];

inline int GetID(int x){
	return lower_bound(V+1,V+cnt+1,x)-V;
}

namespace SegmentTree{
	#define mid ( ( (l) + (r) ) >> 1 )
	const int MAXSIZE=MAXN*40;
	struct Node{
		int sum,lMax,rMax;
		int lson,rson;
		bool L,R;
		#define sum(x) unit[(x)].sum
		#define lson(x) unit[(x)].lson
		#define rson(x) unit[(x)].rson
		#define lMax(x) unit[(x)].lMax
		#define rMax(x) unit[(x)].rMax
		#define cl(x) unit[(x)].L
		#define cr(x) unit[(x)].R
	};
	int tot;
	int root[MAXN];
	Node unit[MAXSIZE];
	inline void pushup(reg int k){
		sum(k)=sum(lson(k))+sum(rson(k));
		lMax(k)=max(lMax(lson(k)),sum(lson(k))+lMax(rson(k)));
		rMax(k)=max(rMax(rson(k)),sum(rson(k))+rMax(lson(k)));
		return;
	}
	inline int Build(reg int l,reg int r){
		reg int k=++tot;
		if(l==r){
			if(GetID(a[l])<=1)
				sum(k)=lMax(k)=rMax(k)=-1;
			else
				sum(k)=lMax(k)=rMax(k)=1;
			return k;
		}
		cl(k)=cr(k)=true;
		lson(k)=Build(l,mid);
		rson(k)=Build(mid+1,r);
		pushup(k);
		return k;
	}
	inline int Update(reg int k,reg int y,reg int l,reg int r,reg int pos,reg int c,reg bool nc){
		if(!nc)
			k=++tot;
		if(l==r){
			sum(k)=lMax(k)=rMax(k)=c;
			return k;
		}
		if(pos<=mid){
			if(!cr(k))
				rson(k)=rson(y);
			if(!cl(k)){
				cl(k)=true;
				lson(k)=Update(k,lson(y),l,mid,pos,c,false);
			}
			else
				lson(k)=Update(lson(k),lson(y),l,mid,pos,c,true);
		}
		else{
			if(!cl(k))
				lson(k)=lson(y);
			if(!cr(k)){
				cr(k)=true;
				rson(k)=Update(k,rson(y),mid+1,r,pos,c,false);
			}
			else
				rson(k)=Update(rson(k),rson(y),mid+1,r,pos,c,true);
		}
		pushup(k);
		return k;
	}
	inline int Query(reg int k,reg int l,reg int r,reg int L,reg int R){
		if(L<=l&&r<=R)
			return sum(k);
		reg int res=0;
		if(L<=mid)
			res+=Query(lson(k),l,mid,L,R);
		if(R>mid)
			res+=Query(rson(k),mid+1,r,L,R);
		return res;
	}
	inline Node QueryL(reg int k,reg int l,reg int r,reg int L,reg int R){
		if(L<=l&&r<=R)
			return unit[k];
		if(L<=mid&&mid<R){
			Node res;
			Node left=QueryL(lson(k),l,mid,L,R),right=QueryL(rson(k),mid+1,r,L,R);
			res.sum=left.sum+right.sum;
			res.lMax=max(left.lMax,left.sum+right.lMax);
			return res;
		}
		else if(L<=mid)
			return QueryL(lson(k),l,mid,L,R);
		else
			return QueryL(rson(k),mid+1,r,L,R);
	}
	inline Node QueryR(reg int k,reg int l,reg int r,reg int L,reg int R){
		if(L<=l&&r<=R)
			return unit[k];
		if(L<=mid&&mid<R){
			Node res;
			Node left=QueryR(lson(k),l,mid,L,R),right=QueryR(rson(k),mid+1,r,L,R);
			res.sum=left.sum+right.sum;
			res.rMax=max(right.rMax,right.sum+left.rMax);
			return res;
		}
		else if(L<=mid)
			return QueryR(lson(k),l,mid,L,R);
		else
			return QueryR(rson(k),mid+1,r,L,R);
	}
	#undef mid
}

using namespace SegmentTree;

int A,B,C,D;

inline bool check(reg int val){
	reg int size=0;
	if(B+1<=C-1)
		size=Query(root[val],1,n,B+1,C-1);
	reg int L=QueryL(root[val],1,n,C,D).lMax;
	reg int R=QueryR(root[val],1,n,A,B).rMax;
	return (L+size+R)>=0;
}

int main(void){
	n=read();
	for(reg int i=1;i<=n;++i){
		a[i]=read();
		V[++cnt]=a[i];
	}
	sort(V+1,V+cnt+1);
	cnt=unique(V+1,V+cnt+1)-(V+1);
	for(int i=1;i<=n;++i)
		pos[GetID(a[i])].push_back(i);
	root[1]=Build(1,n);
	for(reg int i=2;i<=cnt;++i)
		for(reg int j=0,size=pos[i-1].size();j<size;++j)
			root[i]=Update(root[i],root[i-1],1,n,pos[i-1][j],-1,root[i]>0);
	reg int Q=read();
	reg int lastans=0;
	while(Q--){
		static int q[4];
		A=read(),B=read(),C=read(),D=read();
		q[0]=(A+lastans)%n+1,
		q[1]=(B+lastans)%n+1,
		q[2]=(C+lastans)%n+1,
		q[3]=(D+lastans)%n+1,
		sort(q,q+4);
		A=q[0],B=q[1],C=q[2],D=q[3];
		reg int l=1,r=cnt,mid,ans=0;
		while(l<=r){
			mid=(l+r)>>1;
			if(check(mid))
				ans=mid,l=mid+1;
			else
				r=mid-1;
		}
		printf("%d\n",lastans=V[ans]);
	}
	return 0;
}