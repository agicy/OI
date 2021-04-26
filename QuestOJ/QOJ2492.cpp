#include<cstdio>
#include<algorithm>
#include<cctype>
using namespace std;
#define reg register
typedef long long ll;
typedef unsigned long long ull;
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

inline int max(reg int a,reg int b){
	return a>b?a:b;
}

inline int min(reg int a,reg int b){
	return a<b?a:b;
}

const int MAXN=1e5;
const int MAXK=1e5;
const int MAXA=1e5;
const int X=781+1;

struct interval{
	int l,r;
	inline bool operator<(const interval& a)const{
		return l<a.l;
	}
};

int n,m,p;
int a[MAXN];
int tot,b[MAXN];
int T[MAXA];
int sum[MAXN];

struct BITSET{
	ull unit[X];
	inline void reset(void){
		for(reg int i=0;i<X;++i)
			unit[i]=0;
		return;
	}
	inline void set(reg int x){
		unit[x>>6]|=(1ull<<(x&63));
		return;
	}
	inline void set0(reg int x){
		unit[x>>6]&=~(1ull<<(x&63));
		return;
	}
	inline int count(void){
		reg int res=0;
		for(reg int i=0;i<X;++i)
			res+=__builtin_popcountl(unit[i]);
		return res;
	}
	inline void operator|=(const BITSET& a){
		for(reg int i=0;i<X;++i)
			unit[i]|=a.unit[i];
		return;
	}
};

namespace BLK{
	const int MAXCNT=65;
	const int MAXLOG2CNT=7;
	int lef[MAXCNT],rig[MAXCNT];
	int id[MAXN];
	int lg[MAXCNT+1];
	BITSET col[MAXLOG2CNT][MAXCNT];
	inline void Init(void){
		reg int B=max(n>>6,1),tot=(n+B-1)/B,i,j;
		for(i=0;i<tot;++i){
			lef[i]=i*B,rig[i]=min((i+1)*B,n)-1;
			for(j=lef[i];j<=rig[i];++j)
				id[j]=i;
		}
		lg[0]=-1;
		for(i=1;i<=tot;++i)
			lg[i]=lg[i>>1]+1;
		for(i=0;i<n;++i)
			col[0][id[i]].set(a[i]);
		for(j=1;(1<<j)<=tot;++j)
			for(i=0;i+(1<<j)-1<tot;++i){
				col[j][i]|=col[j-1][i];
				col[j][i]|=col[j-1][i+(1<<(j-1))];
			}
		return;
	}
	inline void query(reg int l,reg int r,BITSET& ans){
		reg int lid=id[l],rid=id[r],i,k;
		if(lid==rid)
			for(i=l;i<=r;++i)
				ans.set(a[i]);
		else{
			for(i=l;i<=rig[lid];++i)
				ans.set(a[i]);
			for(i=lef[rid];i<=r;++i)
				ans.set(a[i]);
			if(lid+1<rid){
				k=lg[rid-lid-1];
				ans|=col[k][lid+1];
				ans|=col[k][rid-(1<<k)];
			}
		}
		return;
	}
}

interval q[MAXK];
BITSET ans;

inline int solve(reg int k){
	reg int i,cnt=0;
	ans.reset();
	for(i=0;i<k;++i){
		BLK::query(q[i].l,q[i].r,ans);
		cnt+=sum[q[i].r]-(q[i].l?sum[q[i].l-1]:0);
	}
	return ans.count()+cnt-(ans.unit[0]&1);
}

int main(void){
	n=read(),m=read(),p=read();
	reg int i,j,lastans=0,k,x,y,ptr;
	for(i=0;i<n;++i)
		++T[a[i]=read()];
	for(i=0;i<n;++i){
		if(T[a[i]]>1)
			b[tot++]=a[i];
		else
			a[i]=0;
		sum[i]=(i?sum[i-1]:0)+(!a[i]);
	}
	sort(b,b+tot),tot=unique(b,b+tot)-b;
	for(i=0;i<n;++i)
		if(T[a[i]]>1)
			a[i]=lower_bound(b,b+tot,a[i])-b+1;
	BLK::Init();
	for(i=0;i<m;++i){
		k=read();
		if(p&&i)
			for(j=0;j<k;++j){
				x=(read()^lastans)%n,y=(read()^lastans)%n;
				q[j].l=min(x,y),q[j].r=max(x,y);
			}
		else
			for(j=0;j<k;++j)
				q[j].l=read()-1,q[j].r=read()-1;
		sort(q,q+k);
		ptr=1;
		for(j=1;j<k;++j)
			if(q[j].l<=q[ptr-1].r+1)
				q[ptr-1].r=max(q[ptr-1].r,q[j].r);
			else
				q[ptr++]=q[j];
		k=ptr;
		writeln(lastans=solve(k));
	}
	return 0;
}