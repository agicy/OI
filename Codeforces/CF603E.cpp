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
	while(!isdigit(ch))f|=(ch=='-'),ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return f?-res:res;
}

inline void writeln(reg int x){
	static char buf[32];
	reg int p=-1;
	if(x<0) x=-x,putchar('-');
	if(x==0) putchar('0');
	else while(x) buf[++p]=(x%10)^'0',x/=10;
	while(~p) putchar(buf[p--]);
	putchar('\n');
	return;
}

inline int max(reg int a,reg int b){
	return a>b?a:b;
}

const int MAXN=1e5+5;
const int MAXM=3e5+5;

int n,m,cnt;

struct querys{
	int id,u,v,val;
	inline querys(reg int id=0,reg int u=0,reg int v=0,reg int val=0):id(id),u(u),v(v),val(val){
		return;
	}
};

struct Edge{
	int tim,u,v,val;
	inline Edge(reg int tim=0,reg int u=0,reg int v=0,reg int val=0):tim(tim),u(u),v(v),val(val){
		return;
	}
	inline bool operator<(const Edge& a)const{
		return val<a.val||(val==a.val&&tim<a.tim);
	}
};

Edge e[MAXM];
querys q[MAXM];
int ans[MAXM];

namespace UnionFind{
	int fa[MAXN],siz[MAXN];
	inline void Init(reg int n){
		for(reg int i=1;i<=n;++i)
			fa[i]=i,siz[i]=1;
		return;
	}
	inline int find(reg int x){
		if(x==fa[x])
			return x;
		else
			return find(fa[x]);
	}
	struct Event{
		int rb;
		inline Event(reg int rb=0):rb(rb){
			return;
		}
	};
	int top;
	Event S[MAXN];
	inline void merge(reg int a,reg int b){
		int ra=find(a),rb=find(b);
		if(ra!=rb){
			if(siz[rb]>siz[ra])
				swap(ra,rb);
			S[++top]=Event(rb);
			cnt-=((siz[ra]&1)&&(siz[rb]&1))<<1;
			fa[rb]=ra,siz[ra]+=siz[rb];
		}
		return;
	}
	inline void roll(const Event& e){
		reg int rb=e.rb,ra=fa[rb];
		siz[ra]-=siz[rb],fa[rb]=rb;
		cnt+=((siz[ra]&1)&&(siz[rb]&1))<<1;
		return;
	}
	inline void undo(reg int lim){
		while(top>lim)
			roll(S[top--]);
		return;
	}
}

inline void solve(reg int L,reg int R,reg int l,reg int r){
	if(l>r||L>R)
		return;
	reg int mid=(L+R)>>1;
	reg int tmp=UnionFind::top;
	reg int ptr=l;
	for(reg int i=L;i<=mid;++i)
		if(q[i].val<=l)
			UnionFind::merge(q[i].u,q[i].v);
	for(reg int i=l;i<=r&&cnt;++i,++ptr)
		if(e[i].tim<=mid)
			UnionFind::merge(e[i].u,e[i].v);
	reg int LIM=max(ptr-1,l);
	if(!cnt)
		ans[q[mid].id]=e[LIM].val;
	else
		ans[q[mid].id]=-1;
	UnionFind::undo(tmp);
	for(reg int i=l;i<=LIM;++i)
		if(e[i].tim<=L)
			UnionFind::merge(e[i].u,e[i].v);
	solve(L,mid-1,LIM,r);
	UnionFind::undo(tmp);
	for(reg int i=L;i<=mid;++i)
		if(q[i].val<=l)
			UnionFind::merge(q[i].u,q[i].v);
	solve(mid+1,R,l,LIM);
	UnionFind::undo(tmp);
	return;
}

int main(void){
	n=read(),m=read();
	for(reg int i=1;i<=m;++i){
		static int a,b,l;
		a=read(),b=read(),l=read();
		e[i]=Edge(i,a,b,l),q[i]=querys(i,a,b,0);
	}
	sort(e+1,e+m+1);
	for(reg int i=1;i<=m;++i)
		q[e[i].tim].val=i;
	cnt=n;
	UnionFind::Init(n);
	solve(1,m,1,m);
	for(reg int i=1;i<=m;++i)
		writeln(ans[i]);
	flush();
	return 0;
}