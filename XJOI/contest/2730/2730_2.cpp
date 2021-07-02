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

inline char* read(reg char* s){
	*s=getchar();
	while(!isalpha(*s)) *s=getchar();
	while(isalpha(*s)) *(++s)=getchar();
	*s='\0';
	return s;
}

inline void writeln(reg int x){
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

const int MAXN=1e5+5;
const int MAXQ=1e5+5;
const int lim=26;

struct querys{
	int id,l,r;
	inline bool operator<(const querys& a)const{
		return r<a.r;
	}
};

int n;
char s[MAXN];
int mat[MAXN];
int q;
querys qu[MAXQ];
int ans[MAXQ];

namespace SAM{
	const int MAXSIZE=MAXN<<1;
	struct Data{
		int Maxl,Maxr;
		inline Data(reg int Maxl=0,reg int Maxr=0):Maxl(Maxl),Maxr(Maxr){
			return;
		}
	};
	inline Data operator+(const Data& a,const Data& b){
		return Data(max(a.Maxl,b.Maxl),max(a.Maxr,b.Maxr));
	}
	namespace SegmentTree{
		#define lson ( (k) << 1 )
		#define rson ( (k) << 1 | 1 )
		#define mid ( ( (l) + (r) ) >> 1 )
		struct Node{
			Data dat;
			#define dat(x) unit[(x)].dat
		};
		Node unit[MAXN<<2];
		inline void update(reg int k,reg int l,reg int r,reg int L,reg int R,const Data& val){
			if(L<=l&&r<=R){
				dat(k)=dat(k)+val;
				return;
			}
			if(L<=mid)
				update(lson,l,mid,L,R,val);
			if(R>mid)
				update(rson,mid+1,r,L,R,val);
			return;
		}
		inline Data query(reg int k,reg int l,reg int r,reg int pos){
			if(l==r)
				return dat(k);
			if(pos<=mid)
				return dat(k)+query(lson,l,mid,pos);
			else
				return dat(k)+query(rson,mid+1,r,pos);
		}
		#undef lson
		#undef rson
		#undef mid
		#undef dat
	}
	namespace LCT{
		struct Node{
			int fa,ch[2];
			int val,Max;
			int epos;
			#define fa(x) unit[(x)].fa
			#define ch(x) unit[(x)].ch
			#define val(x) unit[(x)].val
			#define Max(x) unit[(x)].Max
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
			Max(p)=val(p);
			if(lson(p)) Max(p)=max(Max(p),Max(lson(p)));
			if(rson(p)) Max(p)=max(Max(p),Max(rson(p)));
			return;
		}
		inline void setVal(reg int p,reg int v){
			val(p)=Max(p)=v;
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
			if(lson(p)) epos(lson(p))=epos(p);
			if(rson(p)) epos(rson(p))=epos(p);
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
				rson(p)=0,pushup(p);
				if(epos(p)&&Max(p)){
					reg int l=epos(p)-Max(p)+1,r=epos(p);
					if(l>1)
						SegmentTree::update(1,1,n,1,l-1,Data(Max(p),0));
					SegmentTree::update(1,1,n,l,r,Data(0,r));
				}
				rson(p)=pre;
				pushup(p);
			}
			splay(tmp);
			cover(tmp,v);
			return;
		}
		#undef fa
		#undef ch
		#undef val
		#undef Max
		#undef epos
		#undef lson
		#undef rson
	}
	struct Node{
		int fa,len;
		int ch[lim];
		#define fa(x) unit[(x)].fa
		#define len(x) unit[(x)].len
		#define ch(x) unit[(x)].ch
	};
	int tot,las;
	Node unit[MAXSIZE];
	inline int getId(void){
		reg int p=++tot;
		//memset(&unit[p],0,sizeof(Node));
		return p;
	}
	inline void init(void){
		tot=0;
		las=getId();
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
	inline void build(void){
		for(reg int i=1;i<=tot;++i)
			LCT::unit[i].fa=fa(i),LCT::setVal(i,len(i));
		return;
	}
	inline void update(reg int p,reg int id){
		LCT::update(p,id);
		return;
	}
	inline int query(reg int pos){
		Data res=SegmentTree::query(1,1,n,pos);
		return max(res.Maxl,res.Maxr-pos+1);
	}
	#undef fa
	#undef len
	#undef ch
}

bool ed;

int main(void){
	n=read(s+1)-(s+1);
	SAM::init();
	for(reg int i=1;i<=n;++i)
		mat[i]=SAM::insert(s[i]-'a');
	SAM::build();
	q=read();
	for(reg int i=1;i<=q;++i)
		qu[i].id=i,qu[i].l=read(),qu[i].r=read();
	sort(qu+1,qu+q+1);
	for(reg int i=1,ptr=1;i<=n;++i){
		SAM::update(mat[i],i);
		while(ptr<=q&&qu[ptr].r==i){
			ans[qu[ptr].id]=SAM::query(qu[ptr].l);
			++ptr;
		}
	}
	for(reg int i=1;i<=q;++i)
		writeln(ans[i]);
	flush();
	fprintf(stderr,"%.3lf s\n",1.0*clock()/CLOCKS_PER_SEC);
	fprintf(stderr,"%.3lf MiB\n",(&ed-&st)/1048576.0);
	return 0;
}