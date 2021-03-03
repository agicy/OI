#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar()(p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
#define flush() (fwrite(wbuf,1,wp1,stdout),wp1=0)
#define putchar(c) (wp1==wp2&&(flush(),0),wbuf[wp1++]=c)
static char wbuf[1<<21];int wp1;const int wp2=1<<21;
inline int read(void){
	reg bool f=false;
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))f|=(ch=='-'),ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return f?-res:res;
}

inline void writeln(reg ll u){
	static char buf[32];
	reg int e=-1;
	if(u==0) putchar('0');
	else while(u) buf[++e]=(u%10)^'0',u/=10;
	while(~e) putchar(buf[e--]);
	putchar('\n');
	return;
}

inline ll max(reg ll a,reg ll b){
	return a>b?a:b;
}

const int MAXN=5e3+5;

struct Edge{
	int u,v,col;
	ll val;
	inline bool operator<(const Edge& a)const{
		return val<a.val||(val==a.val&&col<a.col);
	}
};

namespace UnionFind{
	int fa[MAXN];
	inline void Init(reg int n){
		for(reg int i=1;i<=n;++i)
			fa[i]=i;
		return;
	}
	inline int find(reg int u){
		if(u==fa[u])
			return u;
		else
			return fa[u]=find(fa[u]);
	}
	inline void merge(reg int a,reg int b){
		reg int ra=find(a),rb=find(b);
		fa[rb]=ra;
		return;
	}
	inline bool search(reg int a,reg int b){
		return find(a)==find(b);
	}
}

int n,m;
Edge e[MAXN<<1];
ll sum;
int tot;
ll ans[MAXN];

inline void kruskal(void){
	sum=tot=0;
	sort(e+1,e+m+1);
	UnionFind::Init(n);
	for(reg int i=1,cnt=0;i<=m&&cnt<n-1;++i)
		if(!UnionFind::search(e[i].u,e[i].v)){
			++cnt;
			if(e[i].col==0)
				++tot;
			sum+=e[i].val;
			UnionFind::merge(e[i].u,e[i].v);
		}
	return;
}

inline void solve(reg int L,reg int R,reg int lef,reg int rig){
	if(lef>rig||L>R)
		return;
	reg int k=(L+R)>>1;
	reg ll tmp=0;
	reg int l=lef,r=rig,mid;
	while(l<r){
		mid=(0ll+l+r)>>1;
		for(reg int i=1;i<=m;++i)
			if(!e[i].col)
				e[i].val-=mid;
		kruskal();
		if(tot>=k){
			tmp=sum+1ll*k*mid;
			r=mid;
		}
		else
			l=mid+1;
		for(reg int i=1;i<=m;++i)
			if(!e[i].col)
				e[i].val+=mid;
	}
	ans[k]=tmp;
	solve(L,k-1,lef,l+1),solve(k+1,R,l-1,rig);
	return;
}

int main(void){
	n=read();
	reg ll Max=0;
	for(reg int i=1;i<n;++i){
		e[i].u=read(),e[i].v=read(),e[i].val=read(),e[i].col=1;
		Max=max(Max,abs(e[i].val));
	}
	for(reg int i=n;i<(n<<1)-1;++i){
		e[i].u=read(),e[i].v=read(),e[i].val=read(),e[i].col=0;
		Max=max(Max,abs(e[i].val));
	}
	m=(n-1)<<1;
	solve(0,n-1,-Max*2,Max*2);
	for(reg int i=0;i<n;++i)
		writeln(ans[i]);
	flush();
	return 0;
}