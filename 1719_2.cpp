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
	reg bool f=false;
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch)) f|=(ch=='-'),ch=getchar();
	while(isdigit(ch)) res=10*res+(ch^'0'),ch=getchar();
	return f?-res:res;
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
	if(x<0) x=-x,putchar('-');
	if(!x) putchar('0');
	else while(x) buf[++p]=(x%10)^'0',x/=10;
	while(~p) putchar(buf[p--]);
	putchar('\n');
	return;
}

inline int max(reg int a,reg int b){
	return a>b?a:b;
}

const int MAXS=2e6+5;

namespace SAM{
	namespace BIT{
		inline int lowbit(reg int x){
			return x&(-x);
		}
		int n=2e6;
		ll unit[MAXS];
		inline void _update(reg int id,reg ll val){
			if(!id)
				return;
			for(reg int i=id;i<=n;i+=lowbit(i))
				unit[i]+=val;
			return;
		}
		inline ll _query(reg int id){
			reg ll res=0;
			for(reg int i=id;i;i^=lowbit(i))
				res+=unit[i];
			return res;
		}
	}
	namespace LCT{
		const int MAXSIZE=MAXS<<1;
		struct Node{
			int fa,ch[2];
			int dep;
			int val,tVal;
			#define fa(x) unit[(x)].fa
			#define ch(x) unit[(x)].ch
			#define dep(x) unit[(x)].dep
			#define val(x) unit[(x)].val
			#define tVal(x) unit[(x)].tVal
		};
		#define lson(x) ch(x)[0]
		#define rson(x) ch(x)[1]
		Node unit[MAXSIZE];
		inline void New(reg int p,reg int d,reg int f,reg int v){
			fa(p)=f;
			lson(p)=rson(p)=0;
			dep(p)=d;
			val(p)=v,tVal(p)=0;
			return;
		}
		inline bool get(reg int p){
			return rson(fa(p))==p;
		}
		inline bool isRoot(reg int p){
			return lson(fa(p))!=p&&rson(fa(p))!=p;
		}
		inline void pushup(reg int p){
			return;
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
			pushup(f),pushup(p);
			return;
		}
		inline void Cov(reg int p,reg int v){
			if(p) val(p)=tVal(p)=v;
			return;
		}
		inline void pushdown(reg int p){
			if(tVal(p)){
				if(lson(p)) Cov(lson(p),tVal(p));
				if(rson(p)) Cov(rson(p),tVal(p));
				tVal(p)=0;
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
			pushup(p);
			return;
		}
		inline void update(reg int p,reg int v){
			printf("LCT::update p=%d v=%d\n",p,v);
			reg int pre=0,las=0;
			for(;p;pre=p,p=fa(p)){
				printf("LCT::update p=%d v=%d\n",p,v);
				puts("splay");
				splay(p);
				puts("check");
				if(val(p)>=v)
					break;
				puts("bit");
				printf("dep=%d\n",dep(p));
				reg int del=v-val(p);
				BIT::_update(dep(p),del-las);
				las=del;
				puts("link");
				rson(p)=pre;
				puts("pushup");
				pushup(p);
			}
			if(pre)
				Cov(pre,v);
			printf("p=%d dep=%d\n",p,dep(p));
			BIT::_update(dep(p),-las);
			return;
		}
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
	int tot=1;
	Node unit[MAXS<<1];
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
				LCT::splay(q);
				LCT::New(nq,dep(nq),fa(nq),LCT::val(q));
				while(p&&ch(p)[c]==q)
					ch(p)[c]=nq,p=fa(p);
			}
		}
		LCT::New(np,dep(np),fa(np),LCT::val(np));
		return np;
	}
	inline void update(reg int p,reg int val){
		LCT::update(p,val);
		return;
	}
	inline ll query(reg int k){
		return BIT::_query(k);
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
	int tot=1;
	Node unit[MAXSIZE];
	inline void insert(reg char s[],reg int len,reg int val){
		reg int p=1;
		for(reg int i=1;i<=len;++i){
			reg int c=s[i]-'a';
			if(!ch(p)[c])
				ch(p)[c]=++tot,spos(ch(p)[c])=SAM::insert(spos(p),c);
			p=ch(p)[c];
			SAM::update(spos(p),val);
		}
		return;
	}
	#undef ch
	#undef spos
}

char s[MAXS];

bool ed;

int main(void){
	reg int q=read();
	SAM::LCT::New(1,0,0,1e9);
	Trie::unit[1].spos=1;
	while(q--){
		switch(read()){
			case 1:{
				reg int w=read();
				reg int len=read(s+1)-(s+1);
				Trie::insert(s,len,w);
				break;
			}
			case 2:{
				writeln(SAM::query(read()));
				break;
			}
		}
	}
	flush();
	fprintf(stderr,"%.3lf s\n",1.0*clock()/CLOCKS_PER_SEC);
	fprintf(stderr,"%.3lf MiB\n",(&ed-&st)/1048576.0);
	return 0;
}