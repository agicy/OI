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

const int MAXN=2e5+5;
const int MAXLOG2N=18+1;

namespace ST{
	int lg[MAXN];
	int Min[MAXLOG2N][MAXN];
	inline void Init(reg int n,reg int a[]){
		lg[0]=-1;
		for(reg int i=1;i<=n;++i)
			lg[i]=lg[i>>1]+1;
		for(reg int i=1;i<=n;++i)
			Min[0][i]=a[i];
		for(reg int j=1;j<MAXLOG2N;++j)
			for(reg int i=1;i<=n;++i)
				Min[j][i]=min(Min[j-1][i],Min[j-1][i+(1<<(j-1))]);
		return;
	}
	inline int query(reg int l,reg int r){
		reg int k=lg[r-l+1];
		return min(Min[k][l],Min[k][r-(1<<k)+1]);
	}
}

namespace SegmentTree{
	const int MAXSIZE=MAXN*40;
	#define mid ( ( (l) + (r) ) >> 1 )
	struct Node{
		int lson,rson;
		int val;
		#define lson(x) unit[(x)].lson
		#define rson(x) unit[(x)].rson
		#define val(x) unit[(x)].val
	};
	int tot;
	Node unit[MAXSIZE];
	inline int update(reg int pre,reg int l,reg int r,reg int pos,reg int Val){
		reg int p=++tot;
		unit[p]=unit[pre];
		val(p)+=Val;
		if(l!=r){
			if(pos<=mid)
				lson(p)=update(lson(pre),l,mid,pos,Val);
			else
				rson(p)=update(rson(pre),mid+1,r,pos,Val);
		}
		return p;
	}
	inline int query(reg int p,reg int pre,reg int l,reg int r,reg int L,reg int R){
		if(L<=l&&r<=R)
			return val(p)-val(pre);
		if(L<=mid&&mid<R)
			return query(lson(p),lson(pre),l,mid,L,R)+query(rson(p),rson(pre),mid+1,r,L,R);
		else if(L<=mid)
			return query(lson(p),lson(pre),l,mid,L,R);
		else
			return query(rson(p),rson(pre),mid+1,r,L,R);
	}
	#undef mid
	#undef lson
	#undef rson
	#undef val
}

int n,q;
int a[MAXN];
int pos[MAXN],las[MAXN];
int rt[MAXN];

int main(void){
	n=read(),q=read();
	for(reg int i=1;i<=n;++i){
		a[i]=read();
		las[i]=pos[a[i]];
		pos[a[i]]=i;
	}
	ST::Init(n,a);
	for(reg int i=1;i<=n;++i)
		if(las[i]&&ST::query(las[i],i)<a[i])
			las[i]=0;
	for(reg int i=1;i<=n;++i)
		rt[i]=SegmentTree::update(rt[i-1],1,n,las[i]+1,1);
	while(q--){
		static int l,r;
		l=read(),r=read();
		writeln(SegmentTree::query(rt[r],rt[l-1],1,n,1,l));
	}
	flush();
	return 0;
}