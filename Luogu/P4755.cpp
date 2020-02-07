#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
typedef unsigned long long ull;
#define INF 0X3F3F3F3F3F3F3F3Fll
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

const int MAXN=100000+5;
const int MAXLOG2N=17+1;
const int MAXSIZE=MAXN*25;

inline void Read(void);
inline void Work(void);

int main(void){
	Read();
	Work();
	return 0;
}

int n,m;
ll a[MAXN],b[MAXN];

inline void Read(void){
	n=read();
	for(reg int i=1;i<=n;++i)
		a[i]=b[i]=read();
	return;
}

struct ST_List{
	ll Log[MAXN];
	ll pos[MAXN][MAXLOG2N];
	inline void Init(reg ll a[],reg int n){
		Log[0]=-1;
		for(reg int i=1;i<MAXN;++i)
			Log[i]=Log[i>>1]+1;
		for(reg int i=1;i<=n;++i)
			pos[i][0]=i;
		for(reg int j=1;j<MAXLOG2N;++j)
			for(reg int i=1;i+(1<<j)-1<=n;++i)
				if(a[pos[i][j-1]]>a[pos[i+(1<<(j-1))][j-1]])
					pos[i][j]=pos[i][j-1];
				else
					pos[i][j]=pos[i+(1<<(j-1))][j-1];
		return;
	}
	inline int Query(reg int l,reg int r,reg ll a[]){
		reg int k=Log[r-l+1];
		if(a[pos[l][k]]>a[pos[r-(1<<k)+1][k]])
			return pos[l][k];
		else
			return pos[r-(1<<k)+1][k];
	}
};

struct SegmentTree{
	#define mid ( ( (l) + (r) ) >> 1 )
	ll cnt;
	ll root[MAXN];
	ll sum[MAXSIZE],lson[MAXSIZE],rson[MAXSIZE];
	inline int Build(reg int l,reg int r){
		reg int root=++cnt;
		if(l==r)
			sum[root]=lson[root]=rson[root]=0;
		else
			sum[root]=0,lson[root]=Build(l,mid),rson[root]=Build(mid+1,r);
		return root;
	}
	inline int Update(reg int pre,reg int l,reg int r,reg ll val){
		reg int dir=++cnt;
		sum[dir]=sum[pre]+1,lson[dir]=lson[pre],rson[dir]=rson[pre];
		if(l==r)
			return dir;
		if(val<=mid)
			lson[dir]=Update(lson[pre],l,mid,val);
		else
			rson[dir]=Update(rson[pre],mid+1,r,val);
		return dir;
	}
	inline ll Query(reg int pre,reg int dir,reg int l,reg int r,reg int L,reg int R){
		if(r<L||R<l)
			return 0;
		if(L<=l&&r<=R)
			return sum[dir]-sum[pre];
		reg ll res=0;
		if(L<=mid)
			res+=Query(lson[pre],lson[dir],l,mid,L,R);
		if(R>mid)
			res+=Query(rson[pre],rson[dir],mid+1,r,L,R);
		return res;
	}
	#undef mid
};

ll ans;
ST_List ST;
SegmentTree T;

inline void Solve(reg int l,reg int r){
	if(r<l)
		return;
	if(l==r){
		if(b[a[l]]==1)
			++ans;
		return;
	}
	reg int mid=ST.Query(l,r,a);
	if(mid-l+1<=r-(mid+1)+1)
		for(reg int i=l;i<=mid;++i){
			reg ll k=upper_bound(b+1,b+m+1,b[a[mid]]/b[a[i]])-(b+1);
			ans+=T.Query(T.root[mid-1],T.root[r],1,m,1,k);
		}
	else
		for(reg int i=mid;i<=r;++i){
			reg ll k=upper_bound(b+1,b+m+1,b[a[mid]]/b[a[i]])-(b+1);
			ans+=T.Query(T.root[l-1],T.root[mid],1,m,1,k);
		}
	Solve(l,mid-1),Solve(mid+1,r);
	return;
}

inline void Work(void){
	sort(b+1,b+n+1);
	m=unique(b+1,b+n+1)-(b+1);
	for(reg int i=1;i<=n;++i)
		a[i]=lower_bound(b+1,b+m+1,a[i])-b;
	T.root[0]=T.Build(1,m);
	for(reg int i=1;i<=n;++i)
		T.root[i]=T.Update(T.root[i-1],1,m,a[i]);
	ST.Init(a,n);
	Solve(1,n);
	printf("%lld\n",ans);
	return;
}
