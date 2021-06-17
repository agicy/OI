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

inline char* read(reg char *s){
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

inline int max(reg int a,reg int b){
	return a>b?a:b;
}

const int MAXQ=2e6+5;
const int MAXS=2e6+5;

int q;
int opt[MAXQ],k[MAXQ];
vector<char> s[MAXQ];

namespace SAM{
	ll ans[MAXS];
	ll delta[MAXS];
	namespace LCT{
		const int MAXSIZE=MAXS<<1;
		struct Node{
			int fa,ch[2];
			int dep;
			int val;
			#define fa(x) unit[(x)].fa
			#define ch(x) unit[(x)].ch
			#define dep(x) unit[(x)].dep
			#define val(x) unit[(x)].val
		};
		#define lson(x) ch(x)[0]
		#define rson(x) ch(x)[1]
		Node unit[MAXSIZE];
		inline bool get(reg int p){
			return rson(fa(p))==p;
		}
		inline bool isRoot(reg int p){
			return lson(fa(p))!=p&&rson(fa(p))!=p;
		}
		inline void rotate(reg int p){
			if(isRoot(p))
				return;
			reg int f=fa(p),ff=fa(f),dir=get(p);
			if(!isRoot(f)) ch(ff)[get(f)]=p;
			if(ch(p)[dir^1]) fa(ch(p)[dir^1])=f;
			ch(f)[dir]=ch(p)[dir^1];
			ch(p)[dir^1]=f,fa(f)=p;
			fa(p)=ff;
			return;
		}
		inline void pushdown(reg int p){
			if(val(p)){
				if(lson(p)) val(lson(p))=val(p);
				if(rson(p)) val(rson(p))=val(p);
			}
			return;
		}
		inline void update(reg int p){
			if(!isRoot(p))
				update(fa(p));
			pushdown(p);
			return;
		}
		inline void splay(reg int p){
			update(p);
			for(reg int f;f=fa(p),!isRoot(p);rotate(p))
				if(!isRoot(f))
					rotate(get(p)==get(f)?f:p);
			return;
		}
		inline void update(reg int p,reg int v){
			reg int pre=0;
			for(;p;rson(p)=pre,pre=p,p=fa(p)){
				splay(p);
				if(val(p)>=v)
					break;
				delta[dep(fa(p))+1]+=v-val(p);
				delta[dep(p)+1]-=v-val(p);
			}
			if(pre)
				val(pre)=v;
			return;
		}
		#undef fa
		#undef ch
		#undef dep
		#undef val
		#undef lson
		#undef rson
	}
	struct Node{
		int fa,dep;
		int ch[4];
		#define fa(x) unit[(x)].fa
		#define dep(x) unit[(x)].dep
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
				reg int nq=++tot;
				memcpy(ch(nq),ch(q),sizeof(ch(q)));
				fa(nq)=fa(q);
				dep(nq)=dep(p)+1;
				fa(q)=fa(np)=nq;
				while(p&&ch(p)[c]==q)
					ch(p)[c]=nq,p=fa(p);
			}
		}
		return np;
	}
	inline void build(void){
		for(reg int i=2;i<=tot;++i)
			LCT::unit[i].fa=fa(i),LCT::unit[i].dep=dep(i);
		return;
	}
	inline void update(reg int p,reg int val){
		LCT::update(p,val);
		return;
	}
	inline ll query(reg int k){
		return ans[k];
	}
	#undef fa
	#undef dep
	#undef ch
}

namespace Trie{
	const int MAXSIZE=MAXS*2;
	struct Node{
		int ch[4];
		int spos;
		#define ch(x) unit[(x)].ch
		#define spos(x) unit[(x)].spos
	};
	int tot;
	Node unit[MAXSIZE];
	inline void init(void){
		tot=1;
		return;
	}
	inline void insert(reg char s[],reg int len){
		reg int p=1;
		for(reg int i=1;i<=len;++i){
			reg int c=s[i]-'a';
			if(!ch(p)[c])
				ch(p)[c]=++tot;
			p=ch(p)[c];
		}
		return;
	}
	inline void query(const vector<char>& s,vector<int>& pos){
		reg int p=1;
		for(reg int i=0,siz=s.size();i<siz;++i){
			reg int c=s[i]-'a';
			if(!ch(p)[c])
				ch(p)[c]=++tot;
			p=ch(p)[c];
			pos.push_back(spos(p));
		}
		return;
	}
	inline void build(void){
		SAM::init();
		spos(1)=1;
		queue<int> Q;
		Q.push(1);
		while(!Q.empty()){
			reg int u=Q.front();
			Q.pop();
			for(reg int i=0;i<4;++i)
				if(ch(u)[i]){
					int v=ch(u)[i];
					spos(v)=SAM::insert(spos(u),i);
					Q.push(v);
				}
		}
		return;
	}
	#undef ch
	#undef spos
}

bool ed;

int main(void){
	reg int q=read();
	Trie::init();
	for(reg int i=1;i<=q;++i){
		opt[i]=read(),k[i]=read();
		if(opt[i]==1){
			static char str[MAXS];
			reg int len=read(str+1)-(str+1);
			Trie::insert(str,len);
			s[i].resize(len);
			for(reg int j=0;j<len;++j)
				s[i][j]=str[j+1];
		}
	}
	Trie::build();
	SAM::build();
	for(reg int i=1;i<=q;++i)
		switch(opt[i]){
			case 1:{
				vector<int> pos;
				Trie::query(s[i],pos);
				for(int x:pos)
					SAM::update(x,k[i]);
				for(reg int j=1,siz=s[i].size();j<=siz+1;++j)
					SAM::delta[j]+=SAM::delta[j-1];
				for(reg int j=1,siz=s[i].size();j<=siz+1;++j)
					SAM::ans[j]+=SAM::delta[j],SAM::delta[j]=0;
				break;
			}
			case 2:{
				writeln(SAM::query(k[i]));
				break;
			}
		}
	flush();
	fprintf(stderr,"%.3lf s\n",1.0*clock()/CLOCKS_PER_SEC);
	fprintf(stderr,"%.3lf MiB\n",(&ed-&st)/1048576.0);
	return 0;
}