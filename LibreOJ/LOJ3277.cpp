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

const int MAXN=200000+5;
const int MAXM=200000+5;

int n,m;
int a[MAXN];

namespace SegmentTree{
	const int MAXSIZE=MAXN*80;
	#define mid ( ( (l) + (r) ) >> 1 )
	struct Node{
		int lson,rson;
		ll Max,tag;
		#define lson(x) unit[(x)].lson
		#define rson(x) unit[(x)].rson
		#define Max(x) unit[(x)].Max
		#define tag(x) unit[(x)].tag
	};
	int tot;
	int root[MAXN];
	Node unit[MAXSIZE];
	inline int New(void){
		return ++tot;
	}
	inline void pushup(reg int k){
		Max(k)=max(Max(lson(k)),Max(rson(k)));
		return;
	}
	inline void Add(reg int k,reg ll Val){
		Max(k)+=Val;
		tag(k)+=Val;
		return;
	}
	inline void pushdown(reg int k){
		if(tag(k)){
			if(lson(k))
				Add(lson(k),tag(k));
			if(rson(k))
				Add(rson(k),tag(k));
			tag(k)=0;
		}
		return;
	}
	inline void Update(reg int &k,reg int l,reg int r,reg int pos,ll Val){
		if(!k)
			k=New();
		Max(k)=max(Max(k),Val);
		if(l==r)
			return;
		pushdown(k);
		if(pos<=mid)
			Update(lson(k),l,mid,pos,Val);
		else
			Update(rson(k),mid+1,r,pos,Val);
		pushup(k);
		return;
	}
	inline void Update(reg int k,reg int l,reg int r,reg int L,reg int R,reg ll Val){
		if(!k)
			return;
		if(L<=l&&r<=R){
			Add(k,Val);
			return;
		}
		pushdown(k);
		if(L<=mid)
			Update(lson(k),l,mid,L,R,Val);
		if(R>mid)
			Update(rson(k),mid+1,r,L,R,Val);
		pushup(k);
		return;
	}
	inline ll Query(reg int k,reg int l,reg int r,reg int L,reg int R){
		if(!k)
			return 0;
		if(L<=l&&r<=R)
			return Max(k);
		pushdown(k);
		if(L<=mid&&mid<R)
			return max(Query(lson(k),l,mid,L,R),Query(rson(k),mid+1,r,L,R));
		else if(L<=mid)
			return Query(lson(k),l,mid,L,R);
		else
			return Query(rson(k),mid+1,r,L,R);
	}
	inline int merge(int x,int y){
		if(!x||!y)
			return x+y;
		pushdown(x),pushdown(y);
		reg int k=New();
		Max(k)=max(Max(x),Max(y));
		lson(k)=merge(lson(x),lson(y)),rson(k)=merge(rson(x),rson(y));
		return k;
	}
	#undef mid
}

using namespace SegmentTree;

inline void merge(reg int x,reg int y,reg int h){
	reg ll a=Query(root[x],0,n,0,h),b=Query(root[y],0,n,0,h);
	Update(root[x],0,n,h,n,b),Update(root[y],0,n,h,n,a);
	reg ll sum=Query(root[x],0,n,0,h-1)+Query(root[y],0,n,0,h-1);
	Update(root[x],0,n,h-1,sum);
	root[y]=merge(root[x],root[y]);
	return;
}

struct Star{
	int y,c;
	inline Star(reg int y=0,reg int c=0):y(y),c(c){
		return;
	}
};

int ch[MAXN][2];
vector<Star> V[MAXN];

inline void Solve(reg int ID){
	for(reg int i=0,size=V[ID].size();i<size;++i)
		SegmentTree::Update(root[ID],0,n,V[ID][i].y,V[ID][i].c);
	if(ch[ID][0]){
		Solve(ch[ID][0]);
		merge(ch[ID][0],ID,a[ID]);
	}
	if(ch[ID][1]){
		Solve(ch[ID][1]);
		merge(ch[ID][1],ID,a[ID]);
	}
	return;
}

int main(void){
	n=read();
	for(reg int i=1;i<=n;++i)
		a[i]=read();
	static int S[MAXN];
	reg int top=0;
	for(reg int i=1;i<=n;++i){
		while(top&&a[i]>=a[S[top]])
			ch[i][0]=S[top--];
		if(top)
			ch[S[top]][1]=i;
		S[++top]=i;
	}
	int Root=S[1];
	m=read();
	reg ll sum=0;
	for(reg int i=1;i<=m;++i){
		static int x,y,c;
		x=read(),y=read(),c=read();
		V[x].push_back(Star(y,c));
		sum+=c;
	}
	Solve(Root);
	printf("%lld\n",sum-Query(root[Root],0,n,0,n));
	return 0;
}