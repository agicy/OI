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
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch)) ch=getchar();
	while(isdigit(ch)) res=10*res+(ch^'0'),ch=getchar();
	return res;
}

inline char* read(reg char *s){
	*s=getchar();
	while(!isalpha(*s)) *s=getchar();
	while(isalpha(*s)) *(++s)=getchar();
	*s='\0';
	return s;
}

inline void writeln(reg int x){
	static char buf[32];
	reg int p=-1;
	if(!x) putchar('0');
	else while(x) buf[++p]=(x%10)^'0',x/=10;
	while(~p) putchar(buf[p--]);
	putchar('\n');
	return;
}

const int MAXN=1e5+5;
const int MAXS=2e6+5;

namespace AC{
	const int lim=26;
	struct Node{
		int ch[lim],fail;
		#define ch(x) unit[(x)].ch
		#define fail(x) unit[(x)].fail
	};
	int tot;
	Node unit[MAXS];
	inline void init(void){
		tot=1;
		return;
	}
	inline int insert(reg char s[],reg int len){
		reg int p=1;
		for(reg int i=0;i<len;++i){
			reg int c=s[i]-'a';
			if(!ch(p)[c])
				ch(p)[c]=++tot;
			p=ch(p)[c];
		}
		return p;
	}
	inline void build(void){
		fail(1)=1;
		reg int _head=0,_tail=0;
		static int Q[MAXS];
		for(reg int i=0;i<lim;++i)
			if(ch(1)[i])
				fail(ch(1)[i])=1,Q[_tail++]=ch(1)[i];
			else
				ch(1)[i]=1;
		while(_head<_tail){
			reg int u=Q[_head++];
			for(reg int i=0;i<lim;++i)
				if(ch(u)[i])
					fail(ch(u)[i])=ch(fail(u))[i],Q[_tail++]=ch(u)[i];
				else
					ch(u)[i]=ch(fail(u))[i];
		}
		return;
	}
	vector<int> G[MAXS];
	int fa[MAXS],dep[MAXS];
	int siz[MAXS],son[MAXS];
	inline void dfs1(reg int u,reg int father){
		siz[u]=1;
		fa[u]=father;
		dep[u]=dep[father]+1;
		for(int v:G[u]){
			dfs1(v,u);
			siz[u]+=siz[v];
			if(siz[son[u]]<siz[v])
				son[u]=v;
		}
		return;
	}
	int top[MAXS];
	int tim,dfn[MAXS];
	inline void dfs2(reg int u,reg int topf){
		top[u]=topf;
		dfn[u]=++tim;
		if(!son[u])
			return;
		dfs2(son[u],topf);
		for(int v:G[u])
			if(v!=son[u])
				dfs2(v,v);
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
	namespace BIT{
		inline int lowbit(reg int x){
			return x&(-x);
		}
		int n,unit[MAXS];
		inline void init(reg int s){
			n=s;
			return;
		}
		inline void update(reg int id,reg int val){
			for(reg int i=id;i<=n;i+=lowbit(i))
				unit[i]+=val;
			return;
		}
		inline int query(reg int id){
			reg int res=0;
			for(reg int i=id;i;i^=lowbit(i))
				res+=unit[i];
			return res;
		}
	}
	inline bool cmp(reg int a,reg int b){
		return dfn[a]<dfn[b];
	}
	inline void update(reg char s[],reg int len){
		static int S[MAXS];
		S[0]=1;
		for(reg int i=0;i<len;++i)
			S[i+1]=ch(S[i])[s[i]-'a'];
		sort(S+1,S+len+1,cmp);
		for(reg int i=1;i<=len;++i)
			BIT::update(dfn[S[i]],1);
		for(reg int i=1;i<len;++i)
			BIT::update(dfn[LCA(S[i],S[i+1])],-1);
		return;
	}
	inline int query(reg int p){
		return BIT::query(dfn[p]+siz[p]-1)-BIT::query(dfn[p]-1);
	}
	inline void solve(void){
		for(int i=2;i<=tot;++i)
			G[fail(i)].push_back(i);
		dfs1(1,0),dfs2(1,1);
		BIT::init(tot);
		return;
	}
}

int n;
int mat[MAXN];


int main(void){
	n=read();
	AC::init();
	for(reg int i=1;i<=n;++i){
		static char s[MAXS];
		reg int len=read(s)-s;
		mat[i]=AC::insert(s,len);
	}
	AC::build();
	AC::solve();
	reg int q=read();
	while(q--)
		switch(read()){
			case 1:{
				static char p[MAXS];
				reg int len=read(p)-p;
				AC::update(p,len);
				break;
			}
			case 2:{
				writeln(AC::query(mat[read()]));
				break;
			}
		}
	flush();
	return 0;
}