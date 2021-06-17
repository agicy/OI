#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
static char buf[1<<21],*p1=buf,*p2=buf;
#define flush() (fwrite(wbuf,1,wp1,stdout),wp1=0)
#define putchar(c) (wp1==wp2&&(flush(),0),wbuf[wp1++]=c)
static char wbuf[1<<21];int wp1;const int wp2=1<<21;
inline int read(void){
	reg bool f=false;
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch)) f|=(ch=='-'),ch=getchar();
	while(isdigit(ch)) res=10*res+(ch^'0'),ch=getchar();
	return f?-res:res;
}

inline unsigned readu(void){
	reg char ch=getchar();
	reg unsigned res=0;
	while(!isdigit(ch)) ch=getchar();
	while(isdigit(ch)) res=10*res+(ch^'0'),ch=getchar();
	return res;
}

inline ll readllu(void){
	reg char ch=getchar();
	reg ll res=0;
	while(!isdigit(ch)) ch=getchar();
	while(isdigit(ch)) res=10*res+(ch^'0'),ch=getchar();
	return res;
}

inline void writeln(reg ll x){
	static char buf[32];
	reg int p=-1;
	if(!x) putchar('0');
	else while(x) buf[++p]=(x%10)^'0',x/=10;
	while(~p) putchar(buf[p--]);
	putchar('\n');
	return;
}

inline int max(reg int a,reg int b){
	return a>b?a:b;
}

inline ll max(reg ll a,reg ll b){
	return a>b?a:b;
}

inline size_t max(reg size_t a,reg size_t b){
	return a>b?a:b;
}

inline int min(reg int a,reg int b){
	return a<b?a:b;
}

inline ll min(reg ll a,reg ll b){
	return a<b?a:b;
}

inline size_t min(reg size_t a,reg size_t b){
	return a<b?a:b;
}

typedef vector<ll> convex;

inline convex popfront(convex a){
	if(a.empty())
		return a;
	else
		return convex(a.begin()+1,a.end());
}

inline convex operator+(const convex& a,const convex& b){
	reg int lim1=min(a.size(),b.size()),lim2=max(a.size(),b.size());
	convex ans(lim2);
	for(reg int i=0;i<lim1;++i) ans[i]=max(a[i],b[i]);
	for(reg int i=lim1,sa=a.size();i<lim2;++i) ans[i]=i<sa?a[i]:b[i];
	return ans;
}

inline convex operator*(const convex& a,const convex& b){
	if(a.empty()||b.empty()) return {};
	convex res;
	res.reserve(a.size()+b.size());
	res.push_back(a.front()+b.front());
	reg int i=1,sa=a.size(),j=1,sb=b.size();
	while(i<sa&&j<sb)
		if(a[i]-a[i-1]>b[j]-b[j-1]) res.push_back(res.back()+a[i]-a[i-1]),++i;
		else res.push_back(res.back()+b[j]-b[j-1]),++j;
	while(i<sa) res.push_back(res.back()+a[i]-a[i-1]),++i;
	while(j<sb) res.push_back(res.back()+b[j]-b[j-1]),++j;
	return res;
}

const int MAXN=3e5+5;
const int MAXQ=3e5+5;
const ll inf=0x3f3f3f3f3f3f3f3f;

struct querys{
	int id,l,r;
	ll k;
	inline bool operator<(const querys& a)const{
		return k>a.k;
	}
};

int n,q;
int a[MAXN];
querys qu[MAXQ];
ll res[2];

namespace SegmentTree{
	#define lson ( (k) << 1 )
	#define rson ( (k) << 1 | 1 )
	#define mid ( ( (l) + (r) ) >> 1 )
	struct Node{
		convex con[2][2];
		int ptr[2][2];
		#define con(x) unit[(x)].con
		#define ptr(x) unit[(x)].ptr
	};
	Node unit[MAXN<<2];
	inline void pushup(reg int k){
		for(reg int i=0;i<2;++i){
			convex tmp1=con(lson)[i][0]+con(lson)[i][1],tmp2=con(lson)[i][0]+popfront(con(lson)[i][1]);
			for(reg int j=0;j<2;++j)
				con(k)[i][j]=tmp1*con(rson)[0][j]+tmp2*con(rson)[1][j];
		}
		return;
	}
	inline void build(reg int k,reg int l,reg int r){
		if(l==r){
			con(k)[0][0]={0},con(k)[1][1]={-inf,a[l]};
			return;
		}
		build(lson,l,mid),build(rson,mid+1,r);
		pushup(k);
		return;
	}
	inline void query(reg int k,reg int l,reg int r,reg int L,reg int R,reg ll K){
		if(L<=l&&r<=R){
			reg ll tmp[2]={res[0],res[1]};
			res[0]=res[1]=-inf;
			for(reg int i=0;i<2;++i)
				for(reg int j=0;j<2;++j){
					if(con(k)[i][j].empty()) continue;
					reg convex &c=con(k)[i][j];
					reg int &p=ptr(k)[i][j],sc=c.size();
					while(p<sc-1&&K<=c[p+1]-c[p]) ++p;
					res[j]=max(res[j],max(tmp[0],tmp[1]+i*K)+c[p]-K*(ll)p);
				}
			return;
		}
		if(L<=mid) query(lson,l,mid,L,R,K);
		if(R>mid) query(rson,mid+1,r,L,R,K);
		return;
	}
	#undef lson
	#undef rson
	#undef mid
	#undef con
	#undef ptr
}

ll ans[MAXQ];

int main(void){
	n=readu(),q=readu();
	for(reg int i=1;i<=n;++i)
		a[i]=read();
	for(reg int i=1;i<=q;++i)
		qu[i].id=i,qu[i].l=readu(),qu[i].r=readu(),qu[i].k=readllu();
	sort(qu+1,qu+q+1);
	SegmentTree::build(1,1,n);
	for(reg int i=1;i<=q;++i){
		res[0]=0,res[1]=-qu[i].k;
		SegmentTree::query(1,1,n,qu[i].l,qu[i].r,qu[i].k);
		ans[qu[i].id]=max(res[0],res[1]);
	}
	for(reg int i=1;i<=q;++i) writeln(ans[i]);
	flush();
	return 0;
}