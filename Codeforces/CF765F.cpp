#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
#define flush() (fwrite(wbuf,1,wp1,stdout),wp1=0)
#define putchar(c) (wp1==wp2&&(flush(),0),wbuf[wp1++]=c)
static char wbuf[1<<21];int wp1;const int wp2=1<<21;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return res;
}

inline void writeln(reg int x){
	static char buf[32];
	reg int p=-1;
	if(x==0) putchar('0');
	else while(x) buf[++p]=(x%10)^'0',x/=10;
	while(~p) putchar(buf[p--]);
	putchar('\n');
	return;
}

inline int min(reg int a,reg int b){
	return a<b?a:b;
}

const int MAXN=1e5+5;
const int MAXM=3e5+5;
const int inf=0x3f3f3f3f;

struct querys{
	int id,l,r;
	inline bool operator<(const querys& a)const{
		return r<a.r;
	}
};

namespace SegmentTree{
	const int MAXSIZE=MAXN*20;
	#define mid ( ( (l) + (r) ) >> 1 )
	struct Node{
		int lson,rson;
		int siz;
		#define lson(x) unit[(x)].lson
		#define rson(x) unit[(x)].rson
		#define siz(x) unit[(x)].siz
	};
	int tot;
	Node unit[MAXSIZE];
	inline int update(reg int pre,reg int l,reg int r,reg int pos){
		reg int p=++tot;
		unit[p]=unit[pre];
		++siz(p);
		if(l!=r){
			if(pos<=mid)
				lson(p)=update(lson(pre),l,mid,pos);
			else
				rson(p)=update(rson(pre),mid+1,r,pos);
		}
		return p;
	}
	inline int getRnk(reg int p,reg int pre,reg int l,reg int r,reg int pos){
		if(l==r)
			return siz(p)-siz(pre);
		if(pos<=mid)
			return getRnk(lson(p),lson(pre),l,mid,pos);
		else
			return siz(lson(p))-siz(lson(pre))+getRnk(rson(p),rson(pre),mid+1,r,pos);
	}
	inline int query(reg int p,reg int pre,reg int l,reg int r,reg int k){
		if(l==r)
			return l;
		reg int sum=siz(lson(p))-siz(lson(pre));
		if(k<=sum)
			return query(lson(p),lson(pre),l,mid,k);
		else
			return query(rson(p),rson(pre),mid+1,r,k-sum);
	}
	#undef mid
}

namespace BIT{
	inline int lowbit(reg int x){
		return x&(-x);
	}
	int n,unit[MAXN];
	inline void Init(reg int s){
		n=s;
		memset(unit,0x3f,sizeof(unit));
		return;
	}
	inline void update(reg int id,reg int val){
		for(reg int i=id;i;i^=lowbit(i))
			unit[i]=min(unit[i],val);
		return;
	}
	inline int query(reg int id){
		reg int res=inf;
		for(reg int i=id;i<=n;i+=lowbit(i))
			res=min(res,unit[i]);
		return res;
	}
}

int n,m;
int a[MAXN];
querys q[MAXM];
int rt[MAXN],rk[MAXN];
int ans[MAXM];

inline bool cmp(reg int x,reg int y){
	return a[x]<a[y];
}

inline void solve(void){
	static int S[MAXN];
	static int pos[MAXN];
	static int V[MAXN];
	for(reg int i=1;i<=n;++i)
		pos[i]=i;
	sort(pos+1,pos+n+1,cmp);
	reg int tot=0;
	SegmentTree::tot=0;
	BIT::Init(n);
	for(reg int i=1;i<=n;++i){
		if(a[pos[i]]!=a[pos[i-1]])
			V[++tot]=a[pos[i]];
		rk[pos[i]]=tot;
		rt[tot]=SegmentTree::update(rt[rk[pos[i-1]]],1,n,pos[i]);
	}
	V[0]=-inf,a[S[0]=0]=inf;
	reg int ptr=1,top=0;
	for(reg int i=1;i<=n;++i){
		while(a[S[top]]<a[i])
			--top;
		reg int j=S[top];
		while(j){
			BIT::update(j,a[j]-a[i]);
			if(a[i]==a[j])
				break;
			reg int p=upper_bound(V+1,V+tot+1,(a[i]+a[j]-1)>>1)-(V+1);
			if(V[p]<a[i])
				break;
			reg int siz=SegmentTree::getRnk(rt[p],rt[rk[i]-1],1,n,i);
			if(siz==1)
				break;
			j=SegmentTree::query(rt[p],rt[rk[i]-1],1,n,siz-1);
		}
		S[++top]=i;
		while(q[ptr].r==i){
			ans[q[ptr].id]=min(ans[q[ptr].id],BIT::query(q[ptr].l));
			++ptr;
		}
		if(ptr>m)
			break;
	}
	return;
}

int main(void){
	n=read();
	for(reg int i=1;i<=n;++i)
		a[i]=read();
	m=read();
	for(reg int i=1;i<=m;++i)
		q[i].id=i,q[i].l=read(),q[i].r=read();
	sort(q+1,q+m+1);
	memset(ans,0x3f,sizeof(ans));
	a[0]=ans[0],q[m+1].r=inf;
	solve();
	for(reg int i=1;i<=n;++i)
		a[i]=-a[i];
	solve();
	for(reg int i=1;i<=m;++i)
		writeln(ans[i]);
	flush();
	return 0;
}