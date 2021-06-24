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
	while(!isalpha(*s)) *s=getchar();
	while(isalpha(*s)) *(++s)=getchar();
	*s='\0';
	return s;
}

inline void writeln(reg int x){
	static char buf[32];
	reg int p=-1;
	if(x<0) x=-x,putchar('-');
	if(!x) putchar('0');
	else while(x) buf[++p]=(x%10)^'0',x/=10;
	while(~p) putchar(buf[p--]);
	putchar('\n');
	return;
}

const int MAXS=1e6+5;

namespace SAM{
	const int lim=26;
	namespace SAM{
		struct Node{
			int fa,len;
			int ch[lim];
			#define fa(x) unit[(x)].fa
			#define len(x) unit[(x)].len
			#define ch(x) unit[(x)].ch
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
					fa(q)=fa(np)=nq;
					while(p&&ch(p)[c]==q)
						ch(p)[c]=nq,p=fa(p);
				}
			}
			return np;
		}
		inline ll solve(void){
			reg ll res=0;
			for(reg int i=2;i<=tot;++i)
				res+=len(i)-len(fa(i));
			return res;
		}
	}
	namespace Trie{
		struct Node{
			int spos;
			int ch[lim];
			#define spos(x) unit[(x)].spos
			#define ch(x) unit[(x)].ch
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
			SAM::init();
			reg int _head=0,_tail=0;
			static int Q[MAXS];
			spos(1)=1,Q[_tail++]=1;
			while(_head<_tail){
				reg int u=Q[_head++];
				for(reg int i=0;i<lim;++i)
					if(ch(u)[i])
						spos(ch(u)[i])=SAM::insert(spos(u),i),Q[_tail++]=ch(u)[i];
			}
			return;
		}
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
	inline ll solve(void){
		return SAM::solve();
	}
}

int main(void){
	reg int n=read();
	SAM::init();
	while(n--){
		static char s[MAXS];
		reg int len=read(s)-s;
		SAM::insert(s,len);
	}
	SAM::build();
	printf("%lld\n",SAM::solve());
	return 0;
}