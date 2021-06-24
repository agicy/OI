#pragma GCC optimize("Ofast")
#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

bool st;

#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?exit(0),EOF:*p1++)
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
	int cnt,head[MAXN<<1],to[MAXN<<1],Next[MAXN<<1];
	inline void Add_Edge(reg int u,reg int v){
		Next[++cnt]=head[u];
		to[cnt]=v;
		head[u]=cnt;
		return;
	}
	inline void build(void){
		cnt=0;
		for(reg int i=1;i<=tot;++i)
			head[i]=0;
		for(reg int i=2;i<=tot;++i)
			Add_Edge(fa(i),i);
		return;
	}
	inline void dfs(reg int u){
		for(reg int i=head[u];i;i=Next[i]){
			reg int v=to[i];
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
	int S[lim];
	inline bool check(void){
		for(reg int i=0;i<lim;++i)
			S[i]=0;
		for(reg int i=0;i<lim;++i)
			for(reg int j=0;j<lim;++j)
				if(cnt[i][j])
					S[i]|=1<<j;
		for(reg int i=0;i<lim;++i)
			for(reg int j=0;j<lim;++j)
				if((S[j]>>i)&1)
					S[j]|=S[i];
		for(reg int i=0;i<lim;++i)
			if((S[i]>>i)&1)
				return true;
		return false;
	}
}

inline void dfs(reg int u){
	if(!ST::head[u]){
		if(!Graph::check())
			ans[ST::id(u)]=1;
		return;
	}
	for(reg int i=ST::head[u];i;i=ST::Next[i]){
		for(reg int j=ST::head[u];j;j=ST::Next[j])
			if(i!=j){
				reg int v1=ST::to[i],c1=s[ST::dep(u)+ST::id(v1)];
				reg int v2=ST::to[j],c2=s[ST::dep(u)+ST::id(v2)];
				++cnt[c1][c2];
			}
		dfs(ST::to[i]);
		for(reg int j=ST::head[u];j;j=ST::Next[j])
			if(i!=j){
				reg int v1=ST::to[i],c1=s[ST::dep(u)+ST::id(v1)];
				reg int v2=ST::to[j],c2=s[ST::dep(u)+ST::id(v2)];
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
	flush();
	fprintf(stderr,"%.3lf s\n",1.0*clock()/CLOCKS_PER_SEC);
	fprintf(stderr,"%.3lf MiB\n",(&ed-&st)/1048576.0);
	return 0;
}