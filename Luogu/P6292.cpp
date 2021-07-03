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

inline void writeln(reg ll x){
	static char buf[32];
	reg int p=-1;
	if(!x) putchar('0');
	else while(x) buf[++p]=(x%10)^'0',x/=10;
	while(~p) putchar(buf[p--]);
	putchar('\n');
	return;
}

const int MAXN=1e5+5;
const int MAXM=2e5+5;

struct querys{
	int id,l,r;
	inline bool operator<(const querys& a)const{
		return r<a.r;
	}
};

int n,m;
char s[MAXN];
querys q[MAXM];
int mat[MAXN];
ll ans[MAXM];

namespace SAM{
	const int MAXSIZE=MAXN<<1;
	const int lim=26;
	namespace BIT{
		inline int lowbit(reg int x){
			return x&(-x);
		}
		struct Node{
			ll v,vi;
			inline Node(reg ll v=0,reg ll vi=0):v(v),vi(vi){
				return;
			}
		};
		inline Node operator+(const Node& a,const Node& b){
			return Node(a.v+b.v,a.vi+b.vi);
		}
		inline Node operator-(const Node& a,const Node& b){
			return Node(a.v-b.v,a.vi-b.vi);
		}
		int n;
		Node unit[MAXN];
		inline void init(reg int s){
			n=s;
			//fill(unit+1,unit+n+1,Node());
			return;
		}
		inline void update(reg int id,const Node& val){
			for(reg int i=id;i<=n;i+=lowbit(i))
				unit[i]=unit[i]+val;
			return;
		}
		inline Node query(reg int id){
			Node res(0,0);
			for(reg int i=id;i;i^=lowbit(i))
				res=res+unit[i];
			return res;
		}
		inline void update(reg int l,reg int r,reg int x){
			update(l,Node(x,1ll*x*l)),update(r+1,Node(-x,1ll*(-x)*(r+1)));
			return;
		}
		inline ll query(reg int l,reg int r){
			Node tmp1=query(r),tmp2=query(l-1);
			return (tmp1.v*(r+1)-tmp1.vi)-(tmp2.v*l-tmp2.vi);
		}
	}
	struct Node{
		int fa,len;
		int ch[lim];
		#define fa(x) unit[(x)].fa
		#define len(x) unit[(x)].len
		#define ch(x) unit[(x)].ch
	};
	int tot,las;
	Node unit[MAXN<<1];
	inline int getId(void){
		reg int p=++tot;
		//memset(&unit[p],0,sizeof(Node));
		return p;
	}
	inline void init(void){
		tot=0,las=getId();
		return;
	}
	inline int insert(reg int c){
		reg int np=getId(),p=las;
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
				reg int nq=getId();
				unit[nq]=unit[q];
				len(nq)=len(p)+1;
				fa(np)=fa(q)=nq;
				while(p&&ch(p)[c]==q)
					ch(p)[c]=nq,p=fa(p);
			}
		}
		las=np;
		return np;
	}
	namespace LCT{
		struct Node{
			int fa,ch[2];
			int val,Min;
			int epos;
			#define fa(x) unit[(x)].fa
			#define ch(x) unit[(x)].ch
			#define val(x) unit[(x)].val
			#define Min(x) unit[(x)].Min
			#define epos(x) unit[(x)].epos
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
		inline void pushup(reg int p){
			Min(p)=val(p);
			if(lson(p)) Min(p)=min(Min(p),Min(lson(p)));
			if(rson(p)) Min(p)=min(Min(p),Min(rson(p)));
			return;
		}
		inline void setVal(reg int p,reg int v){
			val(p)=Min(p)=v;
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
		inline void cover(reg int p,reg int v){
			epos(p)=v;
			return;
		}
		inline void pushdown(reg int p){
			if(lson(p)) cover(lson(p),epos(p));
			if(rson(p)) cover(rson(p),epos(p));
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
			reg int tmp=p;
			for(reg int pre=0;p;pre=p,p=fa(p)){
				splay(p);
				rson(p)=pre;
				pushup(p);
				if(epos(p))
					BIT::update(epos(p)-SAM::len(p)+1,epos(p)-Min(p)+1,-1);
			}
			splay(tmp);
			cover(tmp,v);
			BIT::update(v-SAM::len(tmp)+1,v,1);
			return;
		}
		#undef fa
		#undef ch
		#undef val
		#undef Min
		#undef epos
		#undef lson
		#undef rson
	}
	#define fa(x) unit[(x)].fa
	#define len(x) unit[(x)].len
	#define ch(x) unit[(x)].ch
	inline void build(void){
		BIT::init(n);
		for(reg int i=1;i<=tot;++i)
			LCT::unit[i].fa=SAM::fa(i),LCT::setVal(i,len(fa(i))+1);
		return;
	}
	inline void update(reg int p,reg int id){
		LCT::update(p,id);
		return;
	}
	inline ll query(reg int l,reg int r){
		return BIT::query(l,r);
	}
	#undef fa
	#undef len
	#undef ch
}

bool ed;

int main(void){
	n=read(s+1)-(s+1);
	m=read();
	for(reg int i=1;i<=m;++i)
		q[i].id=i,q[i].l=read(),q[i].r=read();
	sort(q+1,q+m+1);
	SAM::init();
	for(reg int i=1;i<=n;++i)
		mat[i]=SAM::insert(s[i]-'a');
	SAM::build();
	for(reg int i=1,ptr=1;i<=n;++i){
		SAM::update(mat[i],i);
		while(ptr<=m&&q[ptr].r==i){
			ans[q[ptr].id]=SAM::query(q[ptr].l,q[ptr].r);
			++ptr;
		}
	}
	for(reg int i=1;i<=m;++i)
		writeln(ans[i]);
	flush();
	fprintf(stderr,"%.3lf s\n",1.0*clock()/CLOCKS_PER_SEC);
	fprintf(stderr,"%.3lf MiB\n",(&ed-&st)/1048576.0);
	return 0;
}