#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
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
	while(!isalpha(*s))*s=getchar();
	while(isalpha(*s))*(++s)=getchar();
	*s='\0';
	return s;
}

const int MAXN=8e5+5;
const int MAXS=8e6+5;

namespace SAM{
	struct Node{
		int fa,dep;
		int ch[3];
		int siz;
		ll sum;
		#define fa(x) unit[(x)].fa
		#define dep(x) unit[(x)].dep
		#define ch(x) unit[(x)].ch
		#define siz(x) unit[(x)].siz
		#define sum(x) unit[(x)].sum
	};
	int tot;
	Node unit[MAXN<<1];
	inline void Init(void){
		tot=1;
		return;
	}
	inline int insert(reg int las,reg int c,reg int cnt){
		if(ch(las)[c]&&dep(ch(las)[c])==dep(las)+1){
			siz(ch(las)[c])+=cnt;
			return ch(las)[c];
		}
		reg int np=++tot,p=las;
		dep(np)=dep(p)+1;
		while(p&&!ch(p)[c])
			ch(p)[c]=np,p=fa(p);
		if(!p)
			fa(np)=1;
		else{
			reg int q=ch(p)[c];
			if(dep(p)+1==dep(q))
				fa(np)=q;
			else{
				reg bool flag=false;
				if(dep(np)==dep(p)+1)
					flag=true;
				reg int nq=++tot;
				memcpy(ch(nq),ch(q),sizeof(ch(q)));
				fa(nq)=fa(q);
				dep(nq)=dep(p)+1;
				fa(q)=fa(np)=nq;
				while(p&&ch(p)[c]==q)
					ch(p)[c]=nq,p=fa(p);
				if(flag)
					np=nq;
			}
		}
		siz(np)+=cnt;
		return np;
	}
	int tax[MAXN<<1],ord[MAXN<<1];
	inline void build(void){
		for(reg int i=1;i<=tot;++i)
			++tax[dep(i)];
		for(reg int i=1;i<=tot;++i)
			tax[i]+=tax[i-1];
		for(reg int i=1;i<=tot;++i)
			ord[tax[dep(i)]--]=i;
		for(reg int i=tot;i>=1;--i){
			reg int u=ord[i];
			siz(fa(u))+=siz(u);
		}
		for(reg int i=1;i<=tot;++i)
			sum(i)=1ll*siz(i)*(dep(i)-dep(fa(i)));
		for(reg int i=1;i<=tot;++i){
			reg int u=ord[i];
			sum(u)+=sum(fa(u));
		}
		return;
	}
	inline ll solve(reg char str[],reg int len){
		reg int p=1,Max=0;
		reg ll ans=0;
		for(reg int i=1;i<=len;++i){
			reg int c=str[i]-'a';
			while(p&&!ch(p)[c])
				p=fa(p),Max=dep(p);
			if(!p)
				p=1,Max=0;
			else{
				++Max;
				p=ch(p)[c];
				ans+=sum(fa(p))+1ll*siz(p)*(Max-dep(fa(p)));
			}
		}
		return ans;
	}
	#undef dep
	#undef fa
	#undef ch
	#undef siz
	#undef sum
}

namespace Trie{
	const int MAXSIZE=MAXN*2;
	int tot;
	struct Node{
		int ch[3],siz,spos;
		#define ch(x) unit[(x)].ch
		#define siz(x) unit[(x)].siz
		#define spos(x) unit[(x)].spos
	};
	Node unit[MAXSIZE];
	inline void Init(void){
		tot=1;
		return;
	}
	inline int insert(reg int p,reg int c){
		if(!ch(p)[c])
			ch(p)[c]=++tot;
		p=ch(p)[c];
		++siz(p);
		return p;
	}
	queue<int> Q;
	inline void build(void){
		SAM::Init();
		spos(1)=1;
		Q.push(1);
		while(!Q.empty()){
			reg int u=Q.front();
			Q.pop();
			for(reg int i=0;i<3;++i)
				if(ch(u)[i]){
					int v=ch(u)[i];
					spos(v)=SAM::insert(spos(u),i,siz(v));
					Q.push(v);
				}
		}
		return;
	}
	#undef ch
	#undef siz
	#undef spos
}

int n;
int pos[MAXN];
char str[MAXS];

int main(void){
	n=read();
	pos[1]=1;
	Trie::Init();
	for(reg int i=2;i<=n;++i){
		static int fa;
		static char c;
		fa=read();
		do
			c=getchar();
		while(!isalpha(c));
		pos[i]=Trie::insert(pos[fa],c-'a');
	}
	Trie::build(),SAM::build();
	reg int len=read(str+1)-(str+1);
	printf("%lld\n",SAM::solve(str,len));
	return 0;
}