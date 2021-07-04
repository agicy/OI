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

inline char* read(reg char* s){
	*s=getchar();
	while(!isalpha(*s)) *s=getchar();
	while(isalpha(*s)) *(++s)=getchar();
	*s='\0';
	return s;
}

inline void write(reg int x){
	static char buf[32];
	reg int p=-1;
	if(!x) putchar('0');
	else while(x) buf[++p]=(x%10)^'0',x/=10;
	while(~p) putchar(buf[p--]);
	return;
}

inline int max(reg int a,reg int b){
	return a>b?a:b;
}

inline int min(reg int a,reg int b){
	return a<b?a:b;
}

const int MAXN=5e5+5;
const int MAXT=5e4+5;
const int MAXLOG2T=17+1;

int n;
char s[MAXN];
int m;

struct Data{
	int cnt,id;
	inline Data(reg int cnt=0,reg int id=0):cnt(cnt),id(id){
		return;
	}
};

inline Data operator+(const Data& a,const Data& b){
	if(a.cnt>=b.cnt)
		return a;
	else
		return b;
}

namespace SegmentTree{
	const int MAXSIZE=MAXT*60;
	#define mid ( ( (l) +(r) ) >> 1 )
	struct Node{
		int lson,rson;
		Data dat;
		#define lson(x) unit[(x)].lson
		#define rson(x) unit[(x)].rson
		#define dat(x) unit[(x)].dat
	};
	int tot;
	Node unit[MAXSIZE];
	inline void init(void){
		tot=0;
		return;
	}
	inline int getId(void){
		reg int p=++tot;
		//memset(&unit[p],0,sizeof(Node));
		return p;
	}
	inline void pushup(reg int p){
		dat(p)=dat(lson(p))+dat(rson(p));
		return;
	}
	inline void update(reg int &p,reg int l,reg int r,reg int pos){
		if(!p)
			p=getId();
		if(l==r){
			++dat(p).cnt,dat(p).id=l;
			return;
		}
		if(pos<=mid)
			update(lson(p),l,mid,pos);
		else
			update(rson(p),mid+1,r,pos);
		pushup(p);
		return;
	}
	inline int merge(reg int x,reg int y,reg int l,reg int r){
		if(!x||!y)
			return x|y;
		reg int p=getId();
		if(l==r)
			dat(p)=Data(dat(x).cnt+dat(y).cnt,l);
		else{
			lson(p)=merge(lson(x),lson(y),l,mid);
			rson(p)=merge(rson(x),rson(y),mid+1,r);
			pushup(p);
		}
		return p;
	}
	inline Data query(reg int p,reg int l,reg int r,reg int L,reg int R){
		if(!p)
			return Data(0,max(L,l));
		if(L<=l&&r<=R)
			return dat(p);
		if(L<=mid&&mid<R)
			return query(lson(p),l,mid,L,R)+query(rson(p),mid+1,r,L,R);
		else if(L<=mid)
			return query(lson(p),l,mid,L,R);
		else
			return query(rson(p),mid+1,r,L,R);
	}
	#undef mid
	#undef lson
	#undef rson
	#undef dat
}


namespace SAM{
	const int MAXSIZE=MAXT<<1;
	const int lim=26;
	int rt[MAXSIZE];
	namespace Graph{
		int cnt,head[MAXSIZE],to[MAXSIZE],nxt[MAXSIZE];
		inline void init(void){
			cnt=0;
			//memset(head,0,sizeof(head));
			return;
		}
		inline void Add_Edge(reg int u,reg int v){
			nxt[++cnt]=head[u];
			to[cnt]=v;
			head[u]=cnt;
			return;
		}
		int fa[MAXSIZE][MAXLOG2T+1];
		inline void dfs(reg int u){
			for(reg int i=1;fa[u][i-1];++i)
				fa[u][i]=fa[fa[u][i-1]][i-1];
			for(reg int i=head[u];i;i=nxt[i]){
				reg int v=to[i];
				fa[v][0]=u;
				dfs(v);
				rt[u]=SegmentTree::merge(rt[u],rt[v],1,m);
			}
			return;
		}
	}
	namespace SAM{
		struct Node{
			int fa,len;
			int ch[lim];
			#define fa(x) unit[(x)].fa
			#define len(x) unit[(x)].len
			#define ch(x) unit[(x)].ch
		};
		int tot;
		Node unit[MAXSIZE];
		inline int getId(void){
			reg int p=++tot;
			//memset(&unit[p],0,sizeof(Node));
			return p;
		}
		inline void init(void){
			tot=0,getId();
			return;
		}
		inline int insert(reg int las,reg int c,const vector<int>& S){
			reg int np=getId(),p=las;
			len(np)=len(p)+1;
			for(int x:S)
				SegmentTree::update(rt[np],1,m,x);
			while(p&&!ch(p)[c])
				ch(p)[c]=np,p=fa(p);
			if(!p)
				fa(np)=1;
			else{
				reg int q=ch(p)[c];
				if(len(q)==len(p)+1)
					fa(np)=q;
				else{
					reg int nq=getId();
					unit[nq]=unit[q];
					len(nq)=len(p)+1;
					fa(np)=fa(q)=nq;
					while(p&&ch(p)[c]==q)
						ch(p)[c]=nq,p=fa(p);
				}
			}
			return np;
		}
		inline void build(void){
			Graph::init();
			for(reg int i=2;i<=tot;++i)
				Graph::Add_Edge(fa(i),i);
			return;
		}
		inline void dfs(reg char* s,reg int len,reg int mat[],reg int Maxl[]){
			reg int p=1,l=0;
			for(reg int i=0;i<len;++i){
				reg int c=s[i]-'a';
				while(p&&!ch(p)[c])
					p=fa(p),l=len(p);
				if(ch(p)[c])
					p=ch(p)[c],++l;
				else
					p=1,l=0;
				mat[i]=p,Maxl[i]=l;
			}
			return;
		}
		#undef fa
		#undef len
		#undef ch
	}
	namespace Trie{
		struct Node{
			int ch[lim];
			int spos;
			vector<int> V;
			#define ch(x) unit[(x)].ch
			#define spos(x) unit[(x)].spos
			#define V(x) unit[(x)].V
		};
		int tot;
		Node unit[MAXSIZE];
		inline int getId(void){
			reg int p=++tot;
			//memset(&unit[p],0,sizeof(Node));
			return p;
		}
		inline void init(void){
			tot=0,getId();
			return;
		}
		inline void insert(reg char s[],reg int len,int id){
			reg int p=1;
			for(reg int i=0;i<len;++i){
				reg int c=s[i]-'a';
				if(!ch(p)[c])
					ch(p)[c]=getId();
				p=ch(p)[c];
				V(p).push_back(id);
			}
			return;
		}
		inline void build(void){
			reg int _head=0,_tail=0;
			static int Q[MAXSIZE];
			SAM::init();
			spos(1)=1,Q[_tail++]=1;
			while(_head<_tail){
				reg int u=Q[_head++];
				for(reg int i=0;i<lim;++i)
					if(ch(u)[i])
						spos(ch(u)[i])=SAM::insert(spos(u),i,V(ch(u)[i])),Q[_tail++]=ch(u)[i];
			}
			return;
		}
		#undef ch
		#undef spos
		#undef V
	}
	inline void init(void){
		Trie::init();
		return;
	}
	inline void insert(reg char s[],reg int len,reg int id){
		Trie::insert(s,len,id);
		return;
	}
	inline void build(void){
		Trie::build();
		SAM::build();
		Graph::dfs(1);
		return;
	}
	int mat[MAXN],Maxl[MAXN];
	inline void dfs(reg char* s,reg int len){
		SAM::dfs(s,len,mat,Maxl);
		return;
	}
	inline Data query(reg int l,reg int r,reg int pl,reg int pr){
		if(pr-pl+1>Maxl[pr])
			return Data(0,l);
		reg int p=mat[pr];
		for(reg int i=MAXLOG2T;i>=0;--i)
			if(Graph::fa[p][i]&&SAM::unit[Graph::fa[p][i]].len>=pr-pl+1)
				p=Graph::fa[p][i];
		return SegmentTree::query(rt[p],1,m,l,r);
	}
}

bool ed;

int main(void){
	n=read(s)-s;
	m=read();
	SAM::init();
	for(reg int i=1;i<=m;++i){
		static char t[MAXT];
		reg int l=read(t)-t;
		SAM::insert(t,l,i);
	}
	SAM::build();
	SAM::dfs(s,n);
	reg int q=read();
	while(q--){
		static int l,r,pl,pr;
		l=read(),r=read(),pl=read()-1,pr=read()-1;
		Data res=SAM::query(l,r,pl,pr);
		write(res.id),putchar(' '),write(res.cnt),putchar('\n');
	}
	flush();
	fprintf(stderr,"%.3lf s\n",1.0*clock()/CLOCKS_PER_SEC);
	fprintf(stderr,"%.3lf MiB\n",(&ed-&st)/1048576.0);
	return 0;
}