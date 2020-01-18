#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
typedef unsigned long long ull;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,10000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg bool f=false;
	reg char ch=getchar();
	reg int res=0;
	while(ch<'0'||'9'<ch)f|=(ch=='-'),ch=getchar();
	while('0'<=ch&&ch<='9')res=10*res+ch-'0',ch=getchar();
	return f?-res:res;
}

const int MAXN=200000+5;
const int MAXLOG2N=18+1;

struct SegmentTree{
	#define mid ( ( (l) + (r) ) >> 1 )
	struct Node{
		int val,lson,rson;
		inline Node(reg int val=0,reg int lson=0,reg int rson=0):val(val),lson(lson),rson(rson){
			return;
		}
	};
	int cnt;
	int root[MAXN];
	Node unit[MAXN*MAXLOG2N];
	inline SegmentTree(void){
		cnt=0;
		return;
	}
	inline int Build(reg int l,reg int r){
		reg int root=++cnt;
		if(l==r)
			return root;
		unit[root]=Node(0,Build(l,mid),Build(mid+1,r));
		return root;
	}
	inline int Update(reg int pre,reg int l,reg int r,reg int x){
		reg int dir=++cnt;
		unit[dir]=Node(unit[pre].val+1,unit[pre].lson,unit[pre].rson);
		if(l==r)
			return dir;
		if(x<=mid)
			unit[dir].lson=Update(unit[pre].lson,l,mid,x);
		else
			unit[dir].rson=Update(unit[pre].rson,mid+1,r,x);
		return dir;
	}
	inline int Query(reg int u,reg int v,reg int l,reg int r,reg int k){
		if(l==r)
			return l;
		reg int x=unit[unit[v].lson].val-unit[unit[u].lson].val;
		if(x>=k)
			return Query(unit[u].lson,unit[v].lson,l,mid,k);
		else
			return Query(unit[u].rson,unit[v].rson,mid+1,r,k-x);
	}
	#undef mid
};

int n,m;
int a[MAXN],ind[MAXN];
SegmentTree Tree;

inline int GetID(reg int *s,reg int *t,reg int a){
	return lower_bound(s,t,(int)a)-ind;
}

int main(void){
	n=read(),m=read();
	for(reg int i=1;i<=n;++i)
		ind[i]=a[i]=read();
	sort(ind+1,ind+n+1);
	reg int len=unique(ind+1,ind+n+1)-ind-1;
	Tree.root[0]=Tree.Build(1,len);
	for(reg int i=1;i<=n;++i)
		Tree.root[i]=Tree.Update(Tree.root[i-1],1,len,GetID(ind+1,ind+len+1,a[i]));
	while(m--){
		static int x,y,z;
		x=read(),y=read(),z=read();
		reg int ID=Tree.Query(Tree.root[x-1],Tree.root[y],1,len,z);
		printf("%d\n",ind[ID]);
	}
	return 0;
}
