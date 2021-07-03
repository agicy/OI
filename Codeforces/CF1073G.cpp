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

inline char* read(reg char* s){
	*s=getchar();
	while(!isalpha(*s)) *s=getchar();
	while(isalpha(*s)) *(++s)=getchar();
	*s='\0';
	return s;
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

const int MAXN=2e5+5;

int n;
char s[MAXN];
int q;

namespace SAM{
	const int MAXSIZE=MAXN<<1;
	const int lim=26;
	namespace Tree{
		int cnt,head[MAXSIZE],to[MAXSIZE],nxt[MAXSIZE];
		inline void Add_Edge(reg int u,reg int v){
			nxt[++cnt]=head[u];
			to[cnt]=v;
			head[u]=cnt;
			return;
		}
		int fa[MAXSIZE],dep[MAXSIZE];
		int siz[MAXSIZE],son[MAXSIZE];
		inline void dfs1(reg int u,reg int father){
			siz[u]=1;
			fa[u]=father;
			dep[u]=dep[father]+1;
			for(reg int i=head[u];i;i=nxt[i]){
				reg int v=to[i];
				dfs1(v,u);
				siz[u]+=siz[v];
				if(siz[son[u]]<siz[v])
					son[u]=v;
			}
			return;
		}
		int top[MAXSIZE];
		int tim,dfn[MAXSIZE],end[MAXSIZE];
		inline void dfs2(reg int u,reg int topf){
			top[u]=topf;
			dfn[u]=++tim;
			if(!son[u]){
				end[u]=++tim;
				return;
			}
			dfs2(son[u],topf);
			for(reg int i=head[u];i;i=nxt[i]){
				reg int v=to[i];
				if(v!=son[u])
					dfs2(v,v);
			}
			end[u]=++tim;
			return;
		}
		inline bool cmp1(reg int a,reg int b){
			return dfn[a]<dfn[b];
		}
		inline bool cmp2(reg int a,reg int b){
			return (a>0?dfn[a]:end[-a])<(b>0?dfn[b]:end[-b]);
		}
		inline int LCA(reg int x,reg int y){
			while(top[x]!=top[y])
				if(dep[top[x]]>dep[top[y]])
					x=fa[top[x]];
				else
					y=fa[top[y]];
			return dep[x]<dep[y]?x:y;
		}
	}
	struct Node{
		int fa,len;
		int ch[lim];
		#define fa(x) unit[(x)].fa
		#define len(x) unit[(x)].len
		#define ch(x) unit[(x)].ch
	};
	int tot,las;
	Node unit[MAXSIZE];
	inline int getId(void){
		reg int p=++tot;
		memset(&unit[p],0,sizeof(Node));
		return p;
	}
	inline void init(void){
		tot=0,las=getId();
		return;
	}
	int mat[MAXN];
	inline void insert(reg int c,reg int id){
		reg int np=getId(),p=las;
		len(np)=len(p)+1;
		while(p&&!ch(p)[c])
			ch(p)[c]=np,p=fa(p);
		if(!p)
			fa(np)=1;
		else{
			reg int q=ch(p)[c];
			if(len(q)==len(p)+1)
				fa(np)=q;
			else{
				reg int nq=getId();
				unit[nq]=unit[q];
				len(nq)=len(p)+1;
				fa(np)=fa(q)=nq;
				while(p&&ch(p)[c]==q)
					ch(p)[c]=nq,p=fa(p);
			}
		}
		las=np;
		mat[id]=np;
		return;
	}
	inline void build(void){
		for(reg int i=2;i<=tot;++i)
			Tree::Add_Edge(fa(i),i);
		Tree::dfs1(1,0),Tree::dfs2(1,1);
		return;
	}
	bool vis[MAXSIZE];
	ll f[MAXSIZE][2];
	inline ll solve(reg int a,reg int b){
		reg int tot=0;
		static int V[MAXSIZE<<1];
		for(reg int i=1;i<=a;++i){
			static int x;
			x=mat[n-read()+1];
			f[x][0]=1;
			if(!vis[x])
				vis[x]=true,V[++tot]=x;
		}
		for(reg int i=1;i<=b;++i){
			static int x;
			x=mat[n-read()+1];
			f[x][1]=1;
			if(!vis[x])
				vis[x]=true,V[++tot]=x;
		}
		sort(V+1,V+tot+1,Tree::cmp1);
		for(reg int i=1,lim=tot;i<lim;++i){
			reg int lca=Tree::LCA(V[i],V[i+1]);
			if(!vis[lca])
				vis[lca]=true,V[++tot]=lca;
		}
		for(reg int i=1;i<=tot;++i)
			vis[V[i]]=false;
		for(reg int i=1,lim=tot;i<=lim;++i)
			V[++tot]=-V[i];
		sort(V+1,V+tot+1,Tree::cmp2);
		reg ll res=0;
		reg int top=0;
		static int S[MAXSIZE];
		for(reg int i=1;i<=tot;++i){
			if(V[i]>0){
				reg int u=V[i];
				S[++top]=u;
				res+=SAM::len(u)*f[u][0]*f[u][1];
			}
			else
				if(top==1)
					f[S[top]][0]=f[S[top]][1]=0,--top;
				else{
					reg int u=S[top--],fa=S[top];
					res+=SAM::len(fa)*(f[fa][0]*f[u][1]+f[fa][1]*f[u][0]);
					f[fa][0]+=f[u][0],f[fa][1]+=f[u][1],f[u][0]=f[u][1]=0;
				}
		}
		return res;
	}
}

bool ed;

int main(void){
	n=read(),q=read(),read(s+1);
	reverse(s+1,s+n+1);
	SAM::init();
	for(reg int i=1;i<=n;++i)
		SAM::insert(s[i]-'a',i);
	SAM::build();
	while(q--){
		static int a,b;
		a=read(),b=read();
		writeln(SAM::solve(a,b));
	}
	flush();
	fprintf(stderr,"%.3lf s\n",1.0*clock()/CLOCKS_PER_SEC);
	fprintf(stderr,"%.3lf MiB\n",(&ed-&st)/1048576.0);
	return 0;
}