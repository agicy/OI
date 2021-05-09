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
	reg int ans=0;
	while(!isdigit(ch))ch=getchar();
	while(isdigit(ch))ans=10*ans+(ch^'0'),ch=getchar();
	return ans;
}

inline void writeln(reg ll x){
	static char buf[32];
	reg int p=-1;
	if(x<0) x=-x,putchar('-');
	if(!x) putchar('0');
	else while(x) buf[++p]=(x%10)^'0',x/=10;
	while(~p) putchar(buf[p--]);
	putchar('\n');
	return;
}

const int MAXN=1e5+5;
const int MAXM=1e5+5;
const int MAXQ=1e5+5;
const int MAXLOG2A=30;

struct Basis{
	int tot,unit[MAXLOG2A];
	inline void insert(reg int x){
		if(tot==MAXLOG2A)
			return;
		for(reg int i=MAXLOG2A-1;i>=0;--i)
			if((x>>i)&1){
				if(!unit[i]){
					unit[i]=x;
					return;
				}
				x^=unit[i];
			}
		return;
	}
	inline int query(reg int x){
		for(reg int i=MAXLOG2A-1;i>=0;--i)
			if((x^unit[i])>x)
				x^=unit[i];
		return x;
	}
	inline void merge(const Basis& a){
		if(tot==MAXLOG2A)
			return;
		else if(a.tot==MAXLOG2A)
			*this=a;
		else
			for(reg int i=MAXLOG2A-1;i>=0;--i)
				if(a.unit[i])
					insert(a.unit[i]);
		return;
	}
	inline void clear(void){
		tot=0,fill(unit,unit+MAXLOG2A,0);
		return;
	}
};

int tim;
Basis bas;

struct Node{
	int fa,val;
	inline Node(reg int fa=0,reg int val=0):fa(fa),val(val){
		return;
	}
	inline Node Xor(reg int v){
		return Node(fa,val^v);
	}
};

namespace UnionFind{
	int fa[MAXN],val[MAXN],siz[MAXN],tim[MAXN];
	int top,S[MAXN];
	Basis bas[MAXN];
	inline void Init(reg int n){
		for(reg int i=1;i<=n;++i)
			fa[i]=i,val[i]=0,siz[i]=1,bas[i].clear();
		top=0;
		return;
	}
	inline Node find(int x){
		if(x==fa[x])
			return Node(x,0);
		else
			return Node(find(fa[x]).Xor(val[x]));
	}
	inline int query(reg int a,reg int b){
		Node ia=find(a),ib=find(b);
		if(ia.fa!=ib.fa)
			return -1;
		else
			return ia.val^ib.val;
	}
	inline int merge1(reg int a,reg int b,reg int w){
		static Node ia,ib;
		ia=find(a),ib=find(b);
		w^=ia.val^ib.val;
		if(ia.fa==ib.fa)
			return w;
		else{
			int ra=ia.fa,rb=ib.fa;
			if(siz[ra]>siz[rb])
				swap(ra,rb);
			S[++top]=ra,fa[ra]=rb,val[ra]=w,siz[rb]+=siz[ra];
			return 0;
		}
	}
	inline void merge2(reg int a,reg int b,reg int w){
		static Node ia,ib;
		ia=find(a),ib=find(b);
		w^=ia.val^ib.val;
		if(ia.fa==ib.fa)
			bas[ia.fa].insert(w);
		else{
			int ra=ia.fa,rb=ib.fa;
			if(siz[ra]>siz[rb])
				swap(ra,rb);
			S[++top]=ra,fa[ra]=rb,val[ra]=w,siz[rb]+=siz[ra];
			bas[rb].merge(bas[ra]);
		}
		return;
	}
	inline void rollback(reg int t){
		while(top>t){
			reg int x=S[top--];
			siz[fa[x]]-=siz[x],fa[x]=x,val[x]=0;
		}
		return;
	}
	inline void zip(reg int t){
		while(top>t){
			reg int x=S[top--];
			tim[x]=tim[fa[x]];
			if(tim[x]==::tim)
				::bas.merge(bas[x]);
			siz[fa[x]]-=siz[x],fa[x]=x,val[x]=0;
		}
		return;
	}
}

struct Edge{
	int u,v,w;
};

struct querys{
	int id,l,r,a,b;
	inline querys(reg int id=0,reg int l=0,reg int r=0,reg int a=0,reg int b=0):id(id),l(l),r(r),a(a),b(b){
		return;
	}
	inline bool operator<(const querys& a)const{
		return r<a.r;
	}
};

int n,m,q;
Edge e[MAXM];
int val[MAXM];
vector<querys> qu[MAXM];
int ans[MAXQ];

int main(void){
	n=read(),m=read(),q=read();
	for(reg int i=1;i<=m;++i)
		e[i].u=read(),e[i].v=read(),e[i].w=read();
	UnionFind::Init(n);
	reg int B=0.5*sqrt(n*log2(n));
	for(reg int i=1;i<=q;++i){
		static int l,r,a,b;
		l=read(),r=read(),a=read(),b=read();
		if(r-l+1<=B){
			bas.clear();
			for(reg int j=l;j<=r;++j)
				val[j]=UnionFind::merge1(e[j].u,e[j].v,e[j].w);
			reg int tmp=UnionFind::query(a,b);
			if(tmp==-1)
				ans[i]=-1;
			else{
				for(reg int j=l;j<=r;++j)
					if(val[j]&&UnionFind::query(a,e[j].u)>=0)
						bas.insert(val[j]);
				ans[i]=bas.query(tmp);
			}
			UnionFind::rollback(0);
		}
		else
			qu[(l-1)/B+1].push_back(querys(i,l,r,a,b));
	}
	for(reg int i=1,tot=(m-1)/B+1;i<=tot;++i)
		if(qu[i].size()){
			bas.clear();
			UnionFind::Init(n);
			sort(qu[i].begin(),qu[i].end());
			reg int ptr=i*B+1;
			for(querys ev:qu[i]){
				while(ptr<=ev.r)
					UnionFind::merge2(e[ptr].u,e[ptr].v,e[ptr].w),++ptr;
				reg int top=UnionFind::top;
				for(reg int j=ev.l;j<=i*B;++j)
					val[j]=UnionFind::merge1(e[j].u,e[j].v,e[j].w);
				bas=UnionFind::bas[UnionFind::find(ev.a).fa];
				reg int tmp=UnionFind::query(ev.a,ev.b);
				if(tmp==-1){
					ans[ev.id]=-1;
					UnionFind::rollback(top);
				}
				else{
					UnionFind::tim[UnionFind::find(ev.a).fa]=++tim;
					for(reg int j=ev.l;j<=i*B;++j)
						if(val[j]&&UnionFind::query(ev.a,e[j].u)>=0)
							bas.insert(val[j]);
					UnionFind::zip(top);
					ans[ev.id]=bas.query(tmp);
				}
			}
		}
	for(reg int i=1;i<=q;++i)
		writeln(ans[i]);
	flush();
	return 0;
}