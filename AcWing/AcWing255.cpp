#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define INF 0X3F3F3F3F
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
	const int MAXSIZE=40*MAXN;
	#define mid ( ( (l) + (r) ) >> 1 )
	struct Node{
		int lson,rson;
		int cnt;
		#define lson(x) unit[(x)].lson
		#define rson(x) unit[(x)].rson
		#define cnt(x) unit[(x)].cnt
	};
	int tot;
	int root[MAXN];
	Node unit[MAXSIZE];
	inline int build(reg int l,reg int r){
		reg int k=++tot;
		if(l==r)
			return k;
		lson(k)=build(l,mid);
		rson(k)=build(mid+1,r);
		return k;
	}
	inline int update(reg int pre,reg int l,reg int r,reg int pos){
		reg int k=++tot;
		lson(k)=lson(pre),rson(k)=rson(pre),cnt(k)=cnt(pre)+1;
		if(l==r)
			return k;
		if(pos<=mid)
			lson(k)=update(lson(pre),l,mid,pos);
		if(pos>mid)
			rson(k)=update(rson(pre),mid+1,r,pos);
		return k;
	}
	inline int query(reg int pre,reg int las,reg int l,reg int r,reg int k){
		if(l==r)
			return l;
		reg int sum=cnt(lson(las))-cnt(lson(pre));
		if(k<=sum)
			return query(lson(pre),lson(las),l,mid,k);
		else
			return query(rson(pre),rson(las),mid+1,r,k-sum);
	}
	#undef mid
}

int main(void){
	using namespace SegmentTree;
	n=read(),m=read();
	for(reg int i=1;i<=n;++i){
		a[i]=read();
		V.push_back(a[i]);
	}
	sort(V.begin(),V.end());
	V.erase(unique(V.begin(),V.end()),V.end());
	for(reg int i=1;i<=n;++i)
		a[i]=lower_bound(V.begin(),V.end(),a[i])-V.begin()+1;
	reg int S=V.size();
	root[0]=build(1,S);
	for(reg int i=1;i<=n;++i)
		root[i]=update(root[i-1],1,S,a[i]);
	while(m--){
		static int l,r,k;
		l=read(),r=read(),k=read();
		reg int pos=query(root[l-1],root[r],1,S,k);
		printf("%d\n",V[pos-1]);
	}
	return 0;
}