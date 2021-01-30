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

inline void writeln(reg ll x){
	static char buf[32];
	reg int p=-1;
	if(x==0) putchar('0');
	else while(x) buf[++p]=(x%10)^'0',x/=10;
	while(~p) putchar(buf[p--]);
	putchar('\n');
	return;
}

const int MAXN=2e4+5;
const int MAXM=5e4+5;
const int MAXQ=5e4+5;

struct Edge{
	int u,v,w;
	inline Edge(reg int u=0,reg int v=0,reg int w=0):u(u),v(v),w(w){
		return;
	}
};

int u[MAXN+MAXM+MAXQ];
int v[MAXN+MAXM+MAXQ];
int w[MAXN+MAXM+MAXQ];

namespace LCT{
	const int MAXSIZE=MAXN+MAXM+MAXQ;
	struct Node{
		int fa,ch[2];
		int Max,id;
		bool tRev;
		#define fa(x) unit[(x)].fa
		#define ch(x) unit[(x)].ch
		#define Max(x) unit[(x)].Max
		#define id(x) unit[(x)].id
		#define tRev(x) unit[(x)].tRev
	};
	#define lson(x) ch(x)[0]
	#define rson(x) ch(x)[1]
	Node unit[MAXSIZE];
	inline void New(reg int p,reg int v){
		fa(p)=lson(p)=rson(p)=0;
		Max(p)=id(p)=v;
		tRev(p)=false;
		return;
	}
	inline bool get(reg int p){
		return rson(fa(p))==p;
	}
	inline bool isRoot(reg int p){
		return lson(fa(p))!=p&&rson(fa(p))!=p;
	}
	inline void pushup(reg int p){
		Max(p)=id(p);
		if(lson(p)&&w[Max(lson(p))]>w[Max(p)])
			Max(p)=Max(lson(p));
		if(rson(p)&&w[Max(rson(p))]>w[Max(p)])
			Max(p)=Max(rson(p));
		return;
	}
	inline void rotate(reg int p){
		if(isRoot(p))
			return;
		reg int f=fa(p),ff=fa(f),dir=get(p);
		if(!isRoot(f)) ch(ff)[get(f)]=p;
		if(ch(p)[dir^1]) fa(ch(p)[dir^1])=f;
		ch(f)[dir]=ch(p)[dir^1];
		ch(p)[dir^1]=f,fa(f)=p;
		fa(p)=ff;
		pushup(f),pushup(p);
		return;
	}
	inline void Rev(reg int p){
		swap(lson(p),rson(p));
		tRev(p)=!tRev(p);
		return;
	}
	inline void pushdown(reg int p){
		if(tRev(p)){
			if(lson(p))
				Rev(lson(p));
			if(rson(p))
				Rev(rson(p));
			tRev(p)=false;
		}
		return;
	}
	inline void update(reg int p){
		if(!isRoot(p))
			update(fa(p));
		pushdown(p);
		return;
	}
	inline void splay(reg int p){
		update(p);
		for(reg int f;f=fa(p),!isRoot(p);rotate(p))
			if(!isRoot(f))
				rotate(get(p)==get(f)?f:p);
		pushup(p);
		return;
	}
	inline void access(reg int p){
		for(reg int pre=0;p;pre=p,p=fa(p))
			splay(p),rson(p)=pre,pushup(p);
		return;
	}
	inline void makeRoot(reg int p){
		access(p),splay(p),Rev(p);
		return;
	}
	inline void link(reg int x,reg int y){
		makeRoot(x),fa(x)=y;
		return;
	}
	inline void split(reg int x,reg int y){
		makeRoot(x),access(y),splay(y);
		return;
	}
	inline void cut(reg int x,reg int y){
		split(x,y);
		fa(x)=lson(y)=0;
		pushup(y);
		return;
	}
	inline int find(reg int p){
		access(p),splay(p),pushdown(p);
		while(lson(p))
			pushdown(p=lson(p));
		splay(p);
		return p;
	}
	#undef lson
	#undef rson
}

namespace SegmentTree{
	#define lson ( (k) << 1 )
	#define rson ( (k) << 1 | 1 )
	#define mid ( ( (l) + (r) ) >> 1 )
	struct Node{
		vector<Edge> V;
		#define V(x) unit[(x)].V
	};
	Node unit[MAXQ<<2];
	inline void update(reg int k,reg int l,reg int r,reg int L,reg int R,const Edge& val){
		if(L<=l&&r<=R){
			V(k).push_back(val);
			return;
		}
		if(L<=mid)
			update(lson,l,mid,L,R,val);
		if(R>mid)
			update(rson,mid+1,r,L,R,val);
		return;
	}
	struct Event{
		int opt,u,v;
		inline Event(reg int opt=0,reg int u=0,reg int v=0):opt(opt),u(u),v(v){
			return;
		}
	};
	int top;
	Event S[2*(MAXM+MAXQ)];
	ll sum;
	inline void Do(const Edge& e){
		if(LCT::find(e.u)==LCT::find(e.v)){
			LCT::split(e.u,e.v);
			reg int id=LCT::Max(e.v);
			if(w[id]>w[e.w]){
				LCT::cut(u[id],id),LCT::cut(v[id],id);
				S[++top]=Event(2,u[id],id),S[++top]=Event(2,v[id],id);
				LCT::link(e.u,e.w),LCT::link(e.v,e.w);
				S[++top]=Event(1,e.u,e.w),S[++top]=Event(1,e.v,e.w);
				sum-=(w[id]<<1);
				sum+=(w[e.w]<<1);
			}
		}
		else{
			LCT::link(e.u,e.w),LCT::link(e.v,e.w);
			S[++top]=Event(1,e.u,e.w),S[++top]=Event(1,e.v,e.w);
			sum+=(w[e.w]<<1);
		}
		return;
	}
	inline void unDo(const Event& E){
		switch(E.opt){
			case 1:{
				LCT::cut(E.u,E.v);
				sum-=w[E.u]+w[E.v];
				break;
			}
			case 2:{
				LCT::link(E.u,E.v);
				sum+=w[E.u]+w[E.v];
				break;
			}
		}
		return;
	}
	inline void query(reg int k,reg int l,reg int r){
		reg int tmp=top;
		for(reg int i=0,siz=V(k).size();i<siz;++i)
			Do(V(k)[i]);
		if(l==r)
			writeln(sum>>1);
		else
			query(lson,l,mid),query(rson,mid+1,r);
		while(top>tmp)
			unDo(S[top--]);
		return;
	}
	#undef lson
	#undef rson
	#undef mid
}

int n,m,q;
int x[MAXM],y[MAXM],z[MAXM];
vector<pair<int,int>/**/> S[MAXM];

int main(void){
	n=read(),m=read(),q=read();
	for(reg int i=1;i<=n+m+q;++i)
		LCT::New(i,i<=n?0:i);
	for(reg int i=1;i<=m;++i){
		static int z;
		x[i]=read(),y[i]=read(),z=read();
		u[i+n]=x[i],v[i+n]=y[i],w[i+n]=z;
		S[i].push_back(make_pair(1,i+n));
	}
	for(int i=1;i<=q;++i){
		static int k,d;
		k=read(),d=read();
		u[i+n+m]=x[k],v[i+n+m]=y[k],w[i+n+m]=d;
		S[k].push_back(make_pair(i,i+n+m));
	}
	for(reg int i=1;i<=m;++i){
		S[i].push_back(make_pair(q+1,0));
		for(reg int j=1,siz=S[i].size();j<siz;++j)
			if(S[i][j-1].first<=S[i][j].first-1)
				SegmentTree::update(1,1,q,S[i][j-1].first,S[i][j].first-1,Edge(x[i],y[i],S[i][j-1].second));
	}
	SegmentTree::query(1,1,q);
	flush();
	return 0;
}