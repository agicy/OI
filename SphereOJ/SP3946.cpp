#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,10000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg bool f=false;
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))f|=(ch=='-'),ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return f?-res:res;
}

const int MAXN=1e5+5;
const int MAXM=5e3+5;

int rt[MAXN];

namespace SegmentTree{
	const int MAXSIZE=MAXN*30;
	#define mid ( ( (l) + (r) ) >> 1 )
	struct Node{
		int lson,rson;
		int cnt;
		#define lson(x) unit[(x)].lson
		#define rson(x) unit[(x)].rson
		#define cnt(x) unit[(x)].cnt
	};
	int tot;
	Node unit[MAXSIZE];
	inline int update(reg int pre,reg int l,reg int r,reg int pos){
		reg int p=++tot;
		unit[p]=unit[pre];
		++cnt(p);
		if(l!=r){
			if(pos<=mid)
				lson(p)=update(lson(pre),l,mid,pos);
			else
				rson(p)=update(rson(pre),mid+1,r,pos);
		}
		return p;
	}
	inline int query(reg int pre,reg int p,reg int l,reg int r,reg int k){
		if(l==r)
			return l;
		reg int sum=cnt(lson(p))-cnt(lson(pre));
		if(k<=sum)
			return query(lson(pre),lson(p),l,mid,k);
		else
			return query(rson(pre),rson(p),mid+1,r,k-sum);
	}
	#undef mid
}

int n,m;
int a[MAXN];
vector<int> V;

int main(void){
	n=read(),m=read();
	for(reg int i=1;i<=n;++i){
		a[i]=read();
		V.push_back(a[i]);
	}
	sort(V.begin(),V.end());
	V.erase(unique(V.begin(),V.end()),V.end());
	reg int siz=V.size();
	for(reg int i=1;i<=n;++i){
		reg int id=lower_bound(V.begin(),V.end(),a[i])-V.begin()+1;
		rt[i]=SegmentTree::update(rt[i-1],1,siz,id);
	}
	while(m--){
		static int i,j,k;
		i=read(),j=read(),k=read();
		printf("%d\n",V[SegmentTree::query(rt[i-1],rt[j],1,siz,k)-1]);
	}
	return 0;
}