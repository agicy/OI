#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef unsigned int uint;
typedef long long ll;
#define getchar()(p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
#define flush() (fwrite(wbuf,1,wp1,stdout),wp1=0)
#define putchar(c)(wp1==wp2&&(flush(),0),wbuf[wp1++]=c)
static char wbuf[1<<21];int wp1;const int wp2=1<<21;
inline int read(void){
	reg bool f=false;
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))f|=(ch=='-'),ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return f?-res:res;
}

inline uint readu(void){
	reg char ch=getchar();
	reg uint res=0;
	while(!isdigit(ch))ch=getchar();
	while(isdigit(ch))res=10u*res+(ch^'0'),ch=getchar();
	return res;
}

inline void writeuln(reg uint x){
	static char buf[32];
	reg int p=-1;
	if(x==0) putchar('0');
	else while(x) buf[++p]=(x%10)^'0',x/=10;
	while(~p) putchar(buf[p--]);
	putchar('\n');
	return;
}

const int MAXN=3e5+5;
const int MAXQ=3e5+5;

namespace BIT{
	inline int lowbit(reg int x){
		return x&(-x);
	}
	int n;
	uint unit[MAXN];
	inline void Init(reg int s){
		n=s;
		return;
	}
	inline void update(reg int id,reg uint val){
		for(reg int i=id;i<=n;i+=lowbit(i))
			unit[i]^=val;
		return;
	}
	inline uint query(reg int id){
		reg uint res=0;
		for(reg int i=id;i;i^=lowbit(i))
			res^=unit[i];
		return res;
	}
	inline uint query(reg int l,reg int r){
		return query(r)^query(l-1);
	}
}

struct querys{
	int id,l,r;
	inline void Read(reg int i){
		id=i,l=read(),r=read();
		return;
	}
	inline bool operator<(const querys& a){
		return r<a.r;
	}
};

int n,q;
uint a[MAXN],sum[MAXN];
vector<uint> V;
int las[MAXN];
uint ans[MAXQ];
querys Q[MAXQ];

int main(void){
	n=read();
	V.resize(n);
	for(reg int i=1;i<=n;++i){
		a[i]=readu();
		sum[i]=sum[i-1]^a[i];
		V[i-1]=a[i];
	}
	sort(V.begin(),V.end());
	V.erase(unique(V.begin(),V.end()),V.end());
	for(reg int i=1;i<=n;++i)
		a[i]=lower_bound(V.begin(),V.end(),a[i])-V.begin()+1;
	q=read();
	for(reg int i=1;i<=q;++i)
		Q[i].Read(i);
	sort(Q+1,Q+q+1);
	BIT::Init(n);
	for(reg int i=1,ptr=1;i<=q;++i){
		while(ptr<=Q[i].r){
			if(las[a[ptr]])
				BIT::update(las[a[ptr]],V[a[ptr]-1]);
			las[a[ptr]]=ptr;
			BIT::update(ptr,V[a[ptr]-1]);
			++ptr;
		}
		ans[Q[i].id]=BIT::query(Q[i].l,Q[i].r)^sum[Q[i].r]^sum[Q[i].l-1];
	}
	for(reg int i=1;i<=q;++i)
		writeuln(ans[i]);
	flush();
	return 0;
}