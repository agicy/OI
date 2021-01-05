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

const int MAXN=1e5+5;
const int MAXS=MAXN*20;

int n,c;
int col[MAXN];
int deg[MAXN];
int cnt,head[MAXN],to[MAXN<<1],Next[MAXN<<1];

inline void Add_Edge(reg int u,reg int v){
	Next[++cnt]=head[u];
	to[cnt]=v;
	head[u]=cnt;
	return;
}

namespace Trie{
	struct Node{
		int ch[10];
		int c,fa;
		#define ch(q) unit[(q)].ch
		#define c(q) unit[(q)].c
		#define fa(q) unit[(q)].fa
	};
	int tot=1;
	Node unit[MAXS];
	inline int insert(reg int p,reg int ch){
		if(!ch(p)[ch])
			ch(p)[ch]=++tot,c(ch(p)[ch])=ch,fa(ch(p)[ch])=p;
		return ch(p)[ch];
	}
}

inline void dfs(reg int u,reg int fa,reg int x){
	reg int mat=Trie::insert(x,col[u]);
	for(reg int i=head[u];i;i=Next[i]){
		reg int v=to[i];
		if(v!=fa)
			dfs(v,u,mat);
	}
	return;
}

namespace SAM{
	struct Node{
		int ch[10];
		int link,len;
		int pos;
		#define ch(q) unit[(q)].ch
		#define link(q) unit[(q)].link
		#define len(q) unit[(q)].len
		#define pos(q) unit[(q)].pos
	};
	int tot=1;
	Node unit[MAXS<<1];
	inline int insert(reg int ch,reg int las){
		reg int np=++tot;
		reg int p=las;
		len(np)=len(las)+1;
		while(p&&!ch(p)[ch])
			ch(p)[ch]=np,p=link(p);
		if(!p)
			link(np)=1;
		else{
			reg int q=ch(p)[ch];
			if(len(p)+1==len(q))
				link(np)=q;
			else{
				reg int nq=++tot;
				len(nq)=len(p)+1;
				for(reg int i=0;i<c;++i)
					ch(nq)[i]=ch(q)[i];
				while(p&&ch(p)[ch]==q)
					ch(p)[ch]=nq,p=link(p);
				link(nq)=link(q),link(np)=link(q)=nq;
			}
		}
		return np;
	}
	inline void build(void){
		queue<int> Q;
		for(reg int i=0;i<c;++i)
			if(Trie::ch(1)[i])
				Q.push(Trie::ch(1)[i]);
		pos(1)=1;
		while(!Q.empty()){
			reg int u=Q.front();
			Q.pop();
			pos(u)=insert(Trie::c(u),pos(Trie::fa(u)));
			for(reg int i=0;i<c;++i)
				if(Trie::ch(u)[i])
					Q.push(Trie::ch(u)[i]);
		}
		return;
	}
	inline ll Solve(void){
		reg ll res=0;
		for(reg int i=2;i<=tot;++i)
			res+=len(i)-len(link(i));
		return res;
	}
}

int main(void){
	n=read(),c=read();
	for(reg int i=1;i<=n;++i)
		col[i]=read();
	for(reg int i=1;i<n;++i){
		static int u,v;
		u=read(),v=read();
		++deg[u],++deg[v];
		Add_Edge(u,v);
		Add_Edge(v,u);
	}
	for(reg int i=1;i<=n;++i)
		if(deg[i]==1)
			dfs(i,0,1);
	SAM::build();
	printf("%lld\n",SAM::Solve());
	return 0;
}