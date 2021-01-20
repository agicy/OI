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
	while(!isdigit(ch))f|=(ch=='-'),ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return f?-res:res;
}

const int MAXN=1e5+5;
const int MAXQ=1e5+5;
const int inf=2e9;

int rt[MAXN];

namespace SegmentTree{
	const int MAXSIZE=MAXN*90;
	#define mid ( ( 0ll + (l) + (r) ) >> 1 )
	struct Node{
		int lson,rson;
		int cnt;
		double sum;
		#define lson(x) unit[(x)].lson
		#define rson(x) unit[(x)].rson
		#define cnt(x) unit[(x)].cnt
		#define sum(x) unit[(x)].sum
	};
	int tot;
	Node unit[MAXSIZE];
	inline void Init(void){
		tot=0;
		return;
	}
	inline int New(void){
		reg int p=++tot;
		lson(p)=rson(p)=cnt(p)=sum(p)=0;
		assert(tot<MAXSIZE);
		return p;
	}
	inline int update(reg int pre,reg int l,reg int r,reg int pos){
		reg int p=New();
		unit[p]=unit[pre],++cnt(p),sum(p)+=pos;
		if(l!=r){
			if(pos<=mid)
				lson(p)=update(lson(pre),l,mid,pos);
			else
				rson(p)=update(rson(pre),mid+1,r,pos);
		}
		return p;
	}
	inline pair<int,double> query(reg int pre,reg int p,reg int l,reg int r,reg int k){
		if(l==r)
			return make_pair(l,0);
		reg int Sum=cnt(lson(p))-cnt(lson(pre));
		pair<int,double>  res;
		if(Sum>=k){
			pair<int,double> res=query(lson(pre),lson(p),l,mid,k);
			res.second+=(sum(rson(p))-sum(rson(pre)))-1.0*res.first*(cnt(rson(p))-cnt(rson(pre)));
			return res;
		}
		else{
			pair<int,double> res=query(rson(pre),rson(p),mid+1,r,k-Sum);
			res.second+=1.0*res.first*(cnt(lson(p))-cnt(lson(pre)))-(sum(lson(p))-sum(lson(pre)));
			return res;
		}
	}
}

struct querys{
	int l,r;
};

int n,q,k;
vector<int> a[MAXN];
querys Q[MAXQ];
double ans[MAXQ];

int main(void){
	n=read(),q=read(),k=read();
	assert(n<=1e5),assert(q<=1e5),assert(k<=10);
	for(reg int i=1;i<=n;++i){
		a[i].resize(k);
		for(reg int j=0;j<k;++j){
			a[i][j]=read();
			assert(abs(a[i][j])<=1e9);
		}
	}
	for(reg int i=1;i<=q;++i){
		Q[i].l=read(),Q[i].r=read();
		assert(1<=Q[i].l&&Q[i].l<=n);
		assert(1<=Q[i].r&&Q[i].r<=n);
		assert(Q[i].l<=Q[i].r);
	}
	for(reg int i=0;i<k;++i){
		SegmentTree::Init();
		for(reg int j=1;j<=n;++j)
			rt[j]=SegmentTree::update(rt[j-1],-inf,inf,a[j][i]);
		for(reg int j=1;j<=q;++j)
			ans[j]+=SegmentTree::query(rt[Q[j].l-1],rt[Q[j].r],-inf,inf,(Q[j].r-Q[j].l+2)>>1).second;
	}
	for(reg int i=1;i<=q;++i)
		printf("%.8lf\n",ans[i]);
	return 0;
}