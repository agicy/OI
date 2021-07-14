#pragma GCC optimize("Ofast")
#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

bool st;

#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
static char buf[1<<21],*p1=buf,*p2=buf;
#define flush() (fwrite(wbuf,1,wp1,stdout),wp1=0)
#define putchar(c) (wp1==wp2&&(flush(),0),wbuf[wp1++]=c)
static char wbuf[1<<21];int wp1;const int wp2=1<<21;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch)) ch=getchar();
	while(isdigit(ch)) res=10*res+(ch^'0'),ch=getchar();
	return res;
}

inline ll readll(void){
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

inline int min(reg int a,reg int b){
	return a<b?a:b;
}

inline int lowbit(reg int x){
	return x&(-x);
}

const int MAXN=1e5+5;
const int inf=0x3f3f3f3f;

int n,m;

struct Edge{
	int cnt;
	ll sum;
	inline Edge(void){return;}
	inline Edge(reg int cnt,reg ll sum):cnt(cnt),sum(sum){return;}
	inline Edge operator+(const Edge& a)const{return Edge(cnt+a.cnt,sum+a.sum);}
};

namespace Tree{
	namespace BIT{
		struct Data{
			ll v,vi;
			inline Data(void){return;}
			inline Data(const ll& v,const ll& vi):v(v),vi(vi){return;}
			inline Data operator+(const Data& a)const{return Data(v+a.v,vi+a.vi);}
			inline Data operator-(void)const{return Data(-v,-vi);}
		};
		int n;
		Data unit[MAXN];
		inline void init(reg int s){
			n=s;
			return;
		}
		inline void __update(reg int id,const Data& val){
			for(reg int i=id;i<=n;i+=lowbit(i))
				unit[i]=unit[i]+val;
			return;
		}
		inline ll __query(reg int id){
			Data res(0ll,0ll);
			for(reg int i=id;i;i^=lowbit(i))
				res=res+unit[i];
			return 1ll*(id+1)*res.v-res.vi;
		}
		inline void update(reg int l,reg int r,reg ll val){
			__update(l,Data(val,val*l)),__update(r+1,-Data(val,val*(r+1)));
			return;
		}
		inline ll query(reg int l,reg int r){
			return __query(r)-__query(l-1);
		}
	}
	int cnt,head[MAXN],to[MAXN<<1],nxt[MAXN<<1];
	ll w[MAXN<<1];
	inline void Add_Edge(reg int u,reg int v,reg ll len){
		nxt[++cnt]=head[u];
		to[cnt]=v,w[cnt]=len;
		head[u]=cnt;
		return;
	}
	int fa[MAXN],dep[MAXN];
	int siz[MAXN],son[MAXN];
	ll tmp[MAXN];
	inline void dfs1(reg int u,reg int father){
		siz[u]=1;
		fa[u]=father;
		dep[u]=dep[father]+1;
		for(reg int i=head[u];i;i=nxt[i]){
			reg int v=to[i];
			if(v!=fa[u]){
				tmp[v]=w[i];
				dfs1(v,u);
				siz[u]+=siz[v];
				if(siz[son[u]]<siz[v])
					son[u]=v;
			}
		}
		return;
	}
	int top[MAXN];
	int tim,dfn[MAXN];
	inline void dfs2(reg int u,reg int topf){
		top[u]=topf;
		dfn[u]=++tim;
		BIT::update(dfn[u],dfn[u],tmp[u]);
		if(!son[u])
			return;
		dfs2(son[u],topf);
		for(reg int i=head[u];i;i=nxt[i]){
			reg int v=to[i];
			if(v!=fa[u]&&v!=son[u])
				dfs2(v,v);
		}
		return;
	}
	inline int LCA(reg int x,reg int y){
		while(top[x]!=top[y])
			if(dep[top[x]]>dep[top[y]])
				x=fa[top[x]];
			else
				y=fa[top[y]];
		return dep[x]<dep[y]?x:y;
	}
	inline void update(reg int x,reg int y,reg ll v){
		while(top[x]!=top[y])
			if(dep[top[x]]>dep[top[y]])
				BIT::update(dfn[top[x]],dfn[x],v),x=fa[top[x]];
			else
				BIT::update(dfn[top[y]],dfn[y],v),y=fa[top[y]];
		if(dep[x]<dep[y])
			BIT::update(dfn[x]+1,dfn[y],v);
		if(dep[x]>dep[y])
			BIT::update(dfn[y]+1,dfn[x],v);
		return;
	}
	inline Edge query(reg int x,reg int y){
		Edge ans=Edge(0,0);
		while(top[x]!=top[y])
			if(dep[top[x]]>dep[top[y]])
				ans=ans+Edge(dfn[x]-dfn[top[x]]+1,BIT::query(dfn[top[x]],dfn[x])),x=fa[top[x]];
			else
				ans=ans+Edge(dfn[y]-dfn[top[y]]+1,BIT::query(dfn[top[y]],dfn[y])),y=fa[top[y]];
		if(dep[x]<dep[y])
			ans=ans+Edge(dep[y]-dep[x],BIT::query(dfn[x]+1,dfn[y]));
		if(dep[x]>dep[y])
			ans=ans+Edge(dep[x]-dep[y],BIT::query(dfn[y]+1,dfn[x]));
		return ans;
	}
	inline void init(void){
		for(reg int i=1;i<n;++i){
			static int x,y;
			static ll v;
			x=read(),y=read(),v=readll();
			Add_Edge(x,y,v),Add_Edge(y,x,v);
		}
		BIT::init(n);
		dep[0]=-1;
		dfs1(1,0),dfs2(1,1);
		return;
	}
	inline bool cmp(reg int a,reg int b){
		return dfn[a]<dfn[b];
	}
}

namespace Virtual{
	int n,L,R,k;
	ll ans;
	int cnt,head[MAXN],to[MAXN<<1],nxt[MAXN<<1];
	Edge w[MAXN<<1];
	inline void Add_Edge(reg int u,reg int v,const Edge& len){
		nxt[++cnt]=head[u];
		to[cnt]=v,w[cnt]=len;
		head[u]=cnt;
		return;
	}
	inline void link(reg int u,reg int v){
		Edge e=Tree::query(u,v);
		Add_Edge(u,v,e),Add_Edge(v,u,e);
		return;
	}
	bool del[MAXN],key[MAXN];
	inline void clear(reg int u){
		head[u]=0,del[u]=false;
		++n;
		return;
	}
	int rt,MaxPart,sum;
	int siz[MAXN];
	inline void getRt(reg int u,reg int father){
		siz[u]=1;
		reg int Max=0;
		for(reg int i=head[u];i;i=nxt[i]){
			reg int v=to[i];
			if(!del[v]&&v!=father){
				getRt(v,u);
				siz[u]+=siz[v];
				Max=max(Max,siz[v]);
			}
		}
		Max=max(Max,sum-siz[u]);
		if(Max<MaxPart)
			rt=u,MaxPart=Max;
		return;
	}
	struct Node{
		int u;
		Edge val;
		inline Node(void){return;}
		inline Node(const int& u,const Edge& val):u(u),val(val){return;}
	};
	int tot;
	Node p[MAXN];
	inline void dfs(int u,reg int father,const Edge& e){
		if(e.cnt>R)
			return;
		if(key[u])
			p[++tot]=Node(u,e);
		for(reg int i=head[u];i;i=nxt[i]){
			reg int v=to[i];
			if(!del[v]&&v!=father)
				dfs(v,u,e+w[i]);
		}
		return;
	}
	namespace BIT{
		struct Data{
			int cnt;
			ll sum;
			inline Data(void){return;}
			inline Data(const int& cnt,const ll& sum):cnt(cnt),sum(sum){return;}
			inline Data operator+(const Data& a)const{return Data(cnt+a.cnt,sum+a.sum);};
			inline Data operator-(void)const{return Data(-cnt,-sum);};
			inline Data operator-(const Data& a)const{return Data(cnt-a.cnt,sum-a.sum);};
		};
		int n;
		Data unit[MAXN];
		inline void init(reg int s){
			n=s;
			return;
		}
		inline void update(reg int id,const Data& val){
			for(reg int i=id;i<=n;i+=lowbit(i))
				unit[i]=unit[i]+val;
			return;
		}
		inline Data query(reg int id){
			Data res(0,0ll);
			for(reg int i=id;i;i^=lowbit(i))
				res=res+unit[i];
			return res;
		}
		inline Data query(reg int l,reg int r){
			return query(r)-query(l-1);
		}
	}
	inline ll query(const Node& p){
		reg int lef=max(0,L-p.val.cnt),rig=max(-1,R-p.val.cnt);
		if(lef<=rig){
			BIT::Data tmp=BIT::query(lef+1,rig+1);
			return 1ll*tmp.cnt*p.val.sum+tmp.sum;
		}
		else
			return 0;
	}
	inline void calc(int u){
		tot=0;
		if(key[u]){
			p[++tot]=Node(u,Edge(0,0));
			BIT::update(0+1,BIT::Data(1,0ll));
		}
		for(reg int i=head[u];i;i=nxt[i]){
			reg int v=to[i];
			if(!del[v]){
				reg int las=tot;
				dfs(v,0,w[i]);
				for(reg int i=las+1;i<=tot;++i)
					ans+=query(p[i]);
				for(reg int i=las+1;i<=tot;++i)
					BIT::update(p[i].val.cnt+1,BIT::Data(1,p[i].val.sum));
			}
		}
		for(reg int i=1;i<=tot;++i)
			BIT::update(p[i].val.cnt+1,-BIT::Data(1,p[i].val.sum));
		return;
	}
	inline void solve(reg int u){
		del[u]=true;
		calc(u);
		reg int las=sum;
		for(reg int i=head[u];i;i=nxt[i]){
			reg int v=to[i];
			if(!del[v]){
				reg int s=siz[v];
				if(s>siz[u]) s=las-siz[u];
				rt=-1,MaxPart=inf,sum=s;
				getRt(v,0),solve(rt);
			}
		}
		return;
	}
	int a[MAXN];
	inline void solve(void){
		L=read(),R=read(),k=read();
		ans=n=cnt=0;
		for(reg int i=1;i<=k;++i)
			a[i]=read();
		sort(a+1,a+k+1,Tree::cmp);
		reg int top=0;
		static int S[MAXN];
		clear(S[top=1]=1);
		for(reg int i=1;i<=k;++i){
			reg int u=Tree::LCA(S[top],a[i]);
			if(u!=S[top]){
				while(Tree::dep[u]<=Tree::dep[S[top-1]])
					link(S[top-1],S[top]),--top;
				if(S[top]!=u)
					clear(u),link(S[top],u),S[top]=u;
			}
			if(S[top]!=a[i])
				S[++top]=a[i],clear(a[i]);
		}
		while(top>1)
			link(S[top],S[top-1]),--top;
		for(reg int i=1;i<=k;++i)
			key[a[i]]=true;
		rt=-1,MaxPart=inf,sum=n;
		getRt(1,0),solve(rt);
		for(reg int i=1;i<=k;++i)
			key[a[i]]=false;
		printf("%lld\n",ans);
		return;
	}
}

bool ed;

int main(void){
	n=read(),m=read();
	Tree::init();
	Virtual::BIT::init(n);
	while(m--)
		switch(read()){
			case 1:{
				static int x,y;
				static ll v;
				x=read(),y=read(),v=readll();
				Tree::update(x,y,v);
				break;
			}
			case 2:{
				Virtual::solve();
				break;
			}
		}
	flush();
	fprintf(stderr,"%.3lf s\n",1.0*clock()/CLOCKS_PER_SEC);
	fprintf(stderr,"%.3lf MiB\n",(&ed-&st)/1048576.0);
	return 0;
}