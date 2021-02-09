#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return res;
}

inline void read(vector<int>& s){
	reg int siz=read();
	s.resize(siz);
	for(reg int i=0;i<siz;++i)
		s[i]=read();
	return;
}

const int MAXN=5e4+5;
const int MAXM=1e5+5;
const int MAXSIZE=2e5+5;

int n,m;
vector<int> s[MAXN][2];
int mat[MAXM];

namespace Tree{
	int cnt,head[MAXSIZE],to[MAXSIZE],Next[MAXSIZE];
	inline void Add_Edge(reg int u,reg int v){
		Next[++cnt]=head[u];
		to[cnt]=v;
		head[u]=cnt;
		return;
	}
	int val[MAXSIZE];
	int fa[MAXSIZE],dep[MAXSIZE];
	int siz[MAXSIZE],son[MAXSIZE];
	int top[MAXSIZE];
	int tim=-1,dfn[MAXSIZE];
	inline void dfs1(reg int u,reg int father){
		siz[u]=1;
		fa[u]=father;
		dep[u]=dep[father]+val[u];
		for(reg int i=head[u];i;i=Next[i]){
			reg int v=to[i];
			dfs1(v,u);
			siz[u]+=siz[v];
			if(!son[u]||siz[son[u]]<siz[v])
				son[u]=v;
		}
		return;
	}
	inline void dfs2(reg int u,reg int topf){
		top[u]=topf;
		dfn[u]=++tim;
		if(!son[u])
			return;
		dfs2(son[u],topf);
		for(reg int i=head[u];i;i=Next[i]){
			reg int v=to[i];
			if(v!=son[u])
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
	int tag[MAXM];
	inline void dfs(reg int u){
		for(reg int i=head[u];i;i=Next[i]){
			reg int v=to[i];
			dfs(v);
			tag[u]+=tag[v];
		}
		return;
	}
}

int cnt,S[MAXSIZE];

namespace AC{
	struct Node{
		map<int,int> ch;
		int fail;
		int tag;
		int fa;
		#define ch(x) unit[(x)].ch
		#define fail(x) unit[(x)].fail
		#define tag(x) unit[(x)].tag
		#define fa(x) unit[(x)].fa
	};
	int tot=1;
	Node unit[MAXSIZE];
	inline void insert(reg int id,const vector<int>& s){
		reg int p=1;
		for(reg int j=0,siz=s.size();j<siz;++j){
			int c=s[j];
			if(!ch(p)[c])
				ch(p)[c]=++tot;
			p=ch(p)[c];
		}
		++tag(p);
		mat[id]=p;
		return;
	}
	inline void build(void){
		queue<int> Q;
		Q.push(1);
		while(!Q.empty()){
			reg int u=Q.front();
			Q.pop();
			for(map<int,int>::iterator it=ch(u).begin();it!=ch(u).end();++it){
				int v=it->second,c=it->first;
				Q.push(v);
				reg int fa=fail(u),p;
				while(fa&&!(p=ch(fa)[c]))
					fa=fail(fa);
				if(!fa)
					p=1;
				fail(v)=p;
				fa(v)=fa=tag(p)?p:fa(p);
				if(tag(v))
					Tree::Add_Edge(fa,v);
			}
		}
		for(reg int i=0;i<=tot;++i)
			Tree::val[i]=tag(i);
		return;
	}
	inline void query(const vector<int>& s){
		reg int p=1;
		for(reg int i=0,siz=s.size();i<siz;++i){
			int c=s[i],las;
			while(p&&!(las=ch(p)[c]))
				p=fail(p);
			if(!p)
				p=1;
			else{
				p=las;
				if(tag(p))
					S[++cnt]=p;
				else if(tag(fa(p)))
					S[++cnt]=fa(p);
			}
		}
		return;
	}
}

using Tree::dep;
using Tree::siz;
using Tree::dfn;
using Tree::tag;

inline bool cmp(reg int a,reg int b){
	return dfn[a]<dfn[b];
}

int ans[MAXN];

int main(void){
	n=read(),m=read();
	for(reg int i=1;i<=n;++i)
		read(s[i][0]),read(s[i][1]);
	for(reg int i=1;i<=m;++i){
		static vector<int> tmp;
		read(tmp);
		AC::insert(i,tmp);
	}
	AC::build();
	Tree::dfs1(0,0);
	Tree::dfs2(0,0);
	for(reg int i=1;i<=n;++i){
		cnt=0;
		AC::query(s[i][0]),AC::query(s[i][1]);
		if(!cnt)
			continue;
		sort(S+1,S+cnt+1,cmp);
		reg int top=1;
		for(reg int j=2;j<=cnt;++j)
			if(dfn[S[j]]>dfn[S[top]]+siz[S[top]]-1)
				S[++top]=S[j];
			else
				S[top]=S[j];
		reg int sum=dep[S[1]];
		++tag[S[1]];
		for(reg int j=2;j<=top;++j){
			reg int lca=Tree::LCA(S[j],S[j-1]);
			--tag[lca],++tag[S[j]];
			sum+=dep[S[j]]-dep[lca];
		}
		ans[i]=sum;
	}
	Tree::dfs(0);
	for(reg int i=1;i<=m;++i)
		printf("%d\n",tag[mat[i]]);
	for(reg int i=1;i<=n;++i)
		printf("%d%c",ans[i],i==n?'\n':' ');
	return 0;
}