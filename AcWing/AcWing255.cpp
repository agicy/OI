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

const int MAXN=1e5+5;
const int MAXM=1e4+5;

int n,m;
int a[MAXN];
vector<int> V;

namespace SegmentTree{
	#define mid ( ( (l) + (r) ) >> 1 )
	const int MAXSIZE=MAXN*40;
	struct Node{
		int lson,rson,sum;
		#define lson(x) unit[(x)].lson
		#define rson(x) unit[(x)].rson
		#define sum(x) unit[(x)].sum
	};
	int tot,root[MAXN];
	Node unit[MAXSIZE];
	inline void build(reg int &k,reg int l,reg int r){
		k=++tot;
		if(l==r)
			return;
		build(lson(k),l,mid),build(rson(k),mid+1,r);
		return;
	}
	inline void update(reg int &k,reg int pre,reg int l,reg int r,reg int pos,reg int val){
		k=++tot;
		lson(k)=lson(pre),rson(k)=rson(pre),sum(k)=sum(pre)+val;
		if(l==r)
			return;
		if(pos<=mid)
			update(lson(k),lson(pre),l,mid,pos,val);
		else
			update(rson(k),rson(pre),mid+1,r,pos,val);
		return;
	}
	inline int query(reg int pre,reg int las,reg int l,reg int r,reg int val){
		if(l==r)
			return l;
		reg int s=sum(lson(las))-sum(lson(pre));
		if(s<val)
			return query(rson(pre),rson(las),mid+1,r,val-s);
		else
			return query(lson(pre),lson(las),l,mid,val);
	}
	#undef mid
}

using namespace SegmentTree;

int main(void){
	n=read(),m=read();
	for(reg int i=1;i<=n;++i){
		a[i]=read();
		V.push_back(a[i]);
	}
	sort(V.begin(),V.end());
	V.erase(unique(V.begin(),V.end()),V.end());
	reg int s=V.size();
	build(root[0],1,s);
	for(reg int i=1;i<=n;++i){
		a[i]=lower_bound(V.begin(),V.end(),a[i])-V.begin()+1;
		update(root[i],root[i-1],1,s,a[i],1);
	}
	while(m--){
		static int l,r,k;
		l=read(),r=read(),k=read();
		reg int ptr=query(root[l-1],root[r],1,s,k);
		printf("%d\n",V[ptr-1]);
	}
	return 0;
}