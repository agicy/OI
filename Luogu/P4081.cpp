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

bool st;

const int MAXN=1e5+5;
const int MAXS=1e5+5;

namespace SAM{
	const int lim=26;
	namespace SAM{
		struct Node{
			int fa,len;
			int ch[lim];
			int mat;
			#define fa(x) unit[(x)].fa
			#define len(x) unit[(x)].len
			#define ch(x) unit[(x)].ch
			#define mat(x) unit[(x)].mat
		};
		int tot;
		Node unit[MAXS<<1];
		inline void init(void){
			tot=1;
			return;
		}
		inline int insert(reg int las,reg int c){
			reg int np=++tot,p=las;
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
					reg int nq=++tot;
					unit[nq]=unit[q];
					len(nq)=len(p)+1;
					fa(np)=fa(q)=nq;
					while(p&&ch(p)[c]==q)
						ch(p)[c]=nq,p=fa(p);
				}
			}
			return np;
		}
		inline void update(reg int p,reg int id){
			while(p&&mat(p)!=id&&mat(p)!=-1){
				if(!mat(p))
					mat(p)=id;
				else
					mat(p)=-1;
				p=fa(p);
			}
			return;
		}
		inline void dfs(reg char s[],reg int len,reg int id){
			reg int p=1;
			for(reg int i=0;i<len;++i){
				reg int c=s[i]-'a';
				p=ch(p)[c];
				update(p,id);
			}
			return;
		}
		inline void solve(reg ll res[]){
			for(reg int i=2;i<=tot;++i)
				if(mat(i)!=-1)
					res[mat(i)]+=len(i)-len(fa(i));
			return;
		}
		#undef fa
		#undef len
		#undef ch
		#undef mat
	}
	namespace Trie{
		struct Node{
			int ch[lim];
			int spos;
			#define ch(x) unit[(x)].ch
			#define spos(x) unit[(x)].spos
		};
		int tot;
		Node unit[MAXS];
		inline void init(void){
			tot=1;
			return;
		}
		inline void insert(reg char s[],reg int len){
			reg int p=1;
			for(reg int i=0;i<len;++i){
				reg int c=s[i]-'a';
				if(!ch(p)[c])
					ch(p)[c]=++tot;
				p=ch(p)[c];
			}
			return;
		}
		inline void build(void){
			reg int _head=0,_tail=0;
			static int Q[MAXS];
			SAM::init();
			spos(1)=1,Q[_tail++]=1;
			while(_head<_tail){
				reg int u=Q[_head++];
				for(reg int i=0;i<lim;++i)
					if(ch(u)[i])
						spos(ch(u)[i])=SAM::insert(spos(u),i),Q[_tail++]=ch(u)[i];
			}
			return;
		}
		#undef ch
		#undef spos
	}
	inline void init(void){
		Trie::init();
		return;
	}
	inline void insert(reg char s[],reg int len){
		Trie::insert(s,len);
		return;
	}
	inline void build(void){
		Trie::build();
		return;
	}
	inline void dfs(reg char s[],reg int len,reg int id){
		SAM::dfs(s,len,id);
		return;
	}
	inline void solve(reg ll res[]){
		SAM::solve(res);
		return;
	}
}

int n;
char s[MAXS];
int slen[MAXS];
ll ans[MAXN];

bool ed;

int main(void){
	n=read();
	SAM::init();
	for(reg int i=1;i<=n;++i){
		slen[i]=read(s+slen[i-1])-s;
		SAM::insert(s+slen[i-1],slen[i]-slen[i-1]);
	}
	SAM::build();
	for(reg int i=1;i<=n;++i)
		SAM::dfs(s+slen[i-1],slen[i]-slen[i-1],i);
	SAM::solve(ans);
	for(reg int i=1;i<=n;++i)
		writeln(ans[i]);
	flush();
	fprintf(stderr,"%.3lf s\n",1.0*clock()/CLOCKS_PER_SEC);
	fprintf(stderr,"%.3lf MiB\n",(&ed-&st)/1048576.0);
	return 0;
}