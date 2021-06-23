#pragma GCC optimize("Ofast")
#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

bool st;

#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?exit(0),EOF:*p1++)
static char buf[1<<21],*p1=buf,*p2=buf;
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

const int MAXN=1e5+5;
const int lim=12;

namespace ST{
	struct Node{
		int fa,dep,id;
		int ch[lim];
		#define fa(x) unit[(x)].fa
		#define dep(x) unit[(x)].dep
		#define ch(x) unit[(x)].ch
		#define id(x) unit[(x)].id
	};
	int tot,las;
	Node unit[MAXN<<1];
	inline int getId(void){
		reg int p=++tot;
		memset(&unit[p],0,sizeof(unit[p]));
		return p;
	}
	inline void init(void){
		tot=0;
		las=getId();
		return;
	}
	inline void insert(reg int c,reg int Id){
		reg int p=las,np=getId();
		dep(np)=dep(p)+1,id(np)=Id;
		while(p&&!ch(p)[c])
			ch(p)[c]=np,p=fa(p);
		if(!p)
			fa(np)=1;
		else{
			reg int q=ch(p)[c];
			if(dep(q)==dep(p)+1)
				fa(np)=q;
			else{
				reg int nq=getId();
				dep(nq)=dep(p)+1;
				memcpy(ch(nq),ch(q),sizeof(ch(q)));
				fa(nq)=fa(q),fa(q)=fa(np)=nq;
				while(ch(p)[c]==q)
					ch(p)[c]=nq,p=fa(p);
			}
		}
		las=np;
		return;
	}
	vector<int> G[MAXN<<1];
	inline void build(void){
		for(reg int i=1;i<=tot;++i)
			G[i].clear();
		for(int i=2;i<=tot;++i)
			G[fa(i)].push_back(i);
		return;
	}
	inline void dfs(reg int u){
		for(int v:G[u]){
			dfs(v);
			id(u)=id(v);
		}
		return;
	}
}

int n;
char s[MAXN];
char ans[MAXN];
int cnt[lim][lim];

namespace Graph{
	int inDeg[lim];
	vector<int> G[lim];
	inline bool check(void){
		for(reg int i=0;i<lim;++i)
			inDeg[i]=0,G[i].clear();
		for(reg int i=0;i<lim;++i)
			for(int j=0;j<lim;++j)
				if(cnt[i][j])
					G[i].push_back(j),++inDeg[j];
		reg int _head=0,_tail=0;
		static int Q[lim];
		for(reg int i=0;i<lim;++i)
			if(!inDeg[i])
				Q[_tail++]=i;
		reg int cnt=0;
		while(_head<_tail){
			reg int u=Q[_head++];
			++cnt;
			for(int v:G[u]){
				--inDeg[v];
				if(!inDeg[v])
					Q[_tail++]=v;
			}
		}
		return cnt<lim;
	}
}

inline void dfs(reg int u){
	if(ST::G[u].empty()){
		if(!Graph::check())
			ans[ST::id(u)]=1;
		return;
	}
	for(int v1:ST::G[u]){
		reg int c1=s[ST::dep(u)+ST::id(v1)];
		for(int v2:ST::G[u])
			if(v1!=v2){
				reg int c2=s[ST::dep(u)+ST::id(v2)];
				++cnt[c1][c2];
			}
		dfs(v1);
		for(int v2:ST::G[u])
			if(v1!=v2){
				reg int c2=s[ST::dep(u)+ST::id(v2)];
				--cnt[c1][c2];
			}
	}
	return;
}

bool ed;

int main(void){
	reg int t=read();
	while(t--){
		n=read(s)-s;
		for(reg int i=0;i<n;++i)
			s[i]-='a';
		ST::init();
		for(reg int i=n-1;i>=0;--i)
			ST::insert(s[i],i);
		ST::build();
		ST::dfs(1);
		dfs(1);
		for(reg int i=0;i<n;++i)
			putchar(ans[i]+'0'),ans[i]=0;
		putchar('\n');
	}
	fprintf(stderr,"%.3lf s\n",1.0*clock()/CLOCKS_PER_SEC);
	fprintf(stderr,"%.3lf MiB\n",(&ed-&st)/1048576.0);
	return 0;
}