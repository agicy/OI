#include<bits/stdc++.h>
using namespace std;
#define reg register
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

const int MAXN=1e5+5;
const ll inf=0x3f3f3f3f3f3f3f3f;

int n;
int a[MAXN];
ll sum[MAXN];

namespace SegmentTree{
	const int MAXSIZE=MAXN*80;
	#define mid ( ( (l) + (r) ) >> 1 )
	struct Node{
		int lson,rson;
		pair<ll,int> dat;
		#define lson(x) unit[(x)].lson
		#define rson(x) unit[(x)].rson
		#define dat(x) unit[(x)].dat
	};
	int tot;
	Node unit[MAXSIZE];
	inline void Init(void){
		dat(0).first=-inf,dat(0).second=-1;
		return;
	}
	inline void pushup(reg int p){
		dat(p).first=-inf,dat(p).second=-1;
		dat(p)=max(dat(lson(p)),dat(rson(p)));
		return;
	}
	inline void update(reg int &p,reg ll l,reg ll r,reg ll pos,ll val,int Id){
		if(!p){
			p=++tot;
			dat(p)=make_pair(-inf,-1);
		}
		if(l==r){
			dat(p)=max(dat(p),make_pair(val,Id));
			return;
		}
		if(pos<=mid)
			update(lson(p),l,mid,pos,val,Id);
		else
			update(rson(p),mid+1,r,pos,val,Id);
		pushup(p);
		return;
	}
	inline pair<ll,int> query(reg int p,reg ll l,reg ll r,reg ll L,reg ll R){
		if(L<=l&&r<=R)
			return dat(p);
		if(L<=mid&&mid<R)
			return max(query(lson(p),l,mid,L,R),query(rson(p),mid+1,r,L,R));
		else if(L<=mid)
			return query(lson(p),l,mid,L,R);
		else
			return query(rson(p),mid+1,r,L,R);
	}
	#undef mid
}

ll d[MAXN];
int f[MAXN];

int main(void){
	n=read();
	for(reg int i=1;i<=n;++i)
		a[i]=read();
	for(reg int i=1;i<=n;++i)
		sum[i]=sum[i-1]+a[i];
	d[0]=0,sum[0]=0;
	SegmentTree::Init();
	int rt=0;
	SegmentTree::update(rt,0,1e18,0,0,0);
	for(reg int i=1;i<=n;++i){
		pair<ll,int> p=SegmentTree::query(rt,0,1e18,0,sum[i]);
		//printf("get [%d %lld]=(%lld,%d)\n",0,sum[i],p.first,p.second);
		d[i]=sum[i]-p.first;
		f[i]=f[p.second]+i-p.second-1;
		//printf("i=%d p=%d d=%lld f=%d\n",i,p.second,d[i],f[i]);
		SegmentTree::update(rt,0,1e18,sum[i]+d[i],sum[i],i);
		//printf("fix %lld %lld\n",sum[i]+d[i],sum[i]);
	}
	printf("%d\n",f[n]);
	return 0;
}