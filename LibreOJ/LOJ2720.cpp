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

const int MAXS=5e5+5;
const int MAXT=1e6+5;
const int lim=26;

int n;

namespace SegmentTree{
	const int MAXSIZE=MAXS*80;
	#define mid ( ( (l) + (r) ) >> 1 )
	struct Node{
		int lson,rson;
		#define lson(x) unit[(x)].lson
		#define rson(x) unit[(x)].rson
	};
	int tot;
	Node unit[MAXSIZE];
	inline void update(reg int &p,reg int l,reg int r,reg int pos){
		if(!p)
			p=++tot;
		if(l==r)
			return;
		if(pos<=mid)
			update(lson(p),l,mid,pos);
		else
			update(rson(p),mid+1,r,pos);
		return;
	}
	inline int add(reg int pos){
		int p=++tot;
		update(p,1,n,pos);
		return p;
	}
	inline int merge(reg int x,reg int y){
		if(!x||!y)
			return x|y;
		reg int p=++tot;
		lson(p)=merge(lson(x),lson(y)),rson(p)=merge(rson(x),rson(y));
		return p;
	}
	inline bool query(reg int p,reg int l,reg int r,reg int L,reg int R){
		if(!p)
			return false;
		if(L<=l&&r<=R)
			return true;
		if(L<=mid&&mid<R)
			return query(lson(p),l,mid,L,R)||query(rson(p),mid+1,r,L,R);
		else if(L<=mid)
			return query(lson(p),l,mid,L,R);
		else
			return query(rson(p),mid+1,r,L,R);
	}
	#undef mid
}

namespace SAM1{
	struct Node{
		int fa,len;
		int ch[lim];
		int rt;
		#define fa(x) unit[(x)].fa
		#define len(x) unit[(x)].len
		#define ch(x) unit[(x)].ch
		#define rt(x) unit[(x)].rt
	};
	int tot,las;
	Node unit[MAXS<<1];
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
	inline void insert(reg int c,reg int id){
		reg int np=getId(),p=las;
		len(np)=len(p)+1;
		if(id)
			rt(np)=SegmentTree::add(id);
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
		return;
	}
	int cnt[MAXS];
	int dfn[MAXS<<1];
	inline void build(void){
		for(reg int i=1;i<=tot;++i)
			++cnt[len(i)];
		for(reg int i=1;i<=n;++i)
			cnt[i]+=cnt[i-1];
		for(reg int i=1;i<=tot;++i)
			dfn[--cnt[len(i)]]=i;
		for(reg int i=tot-1;i>=1;--i)
			rt(fa(dfn[i]))=SegmentTree::merge(rt(fa(dfn[i])),rt(dfn[i]));
		return;
	}
	inline void find(reg int& p,reg int& len,reg int L,reg int R,reg int c){
		while(true){
			if(ch(p)[c]&&SegmentTree::query(rt(ch(p)[c]),1,n,L+len,R)){
				++len;
				p=ch(p)[c];
				break;
			}
			if(!len)
				break;
			if(--len==len(fa(p)))
				p=fa(p);
		}
		return;
	}
	#undef fa
	#undef len
	#undef ch
	#undef rt
}

namespace SAM2{
	struct Node{
		int fa,len;
		int ch[lim];
		int Min;
		#define fa(x) unit[(x)].fa
		#define len(x) unit[(x)].len
		#define ch(x) unit[(x)].ch
		#define Min(x) unit[(x)].Min
	};
	int tot,las;
	Node unit[MAXT<<1];
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
	inline void insert(reg int c){
		reg int np=getId(),p=las;
		len(np)=len(p)+1;
		Min(np)=len(np);
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
		return;
	}
	inline ll calc(reg int p[]){
		reg ll res=0;
		for(reg int i=2;i<=tot;++i)
			res+=max(0,len(i)-max(len(fa(i)),p[Min(i)]));
		return res;
	}
	#undef fa
	#undef len
	#undef ch
	#undef Min
}

char s[MAXS];

bool ed;

int main(void){
	freopen("name.in","r",stdin);
	freopen("name.out","w",stdout);
	n=read(s+1)-(s+1);
	SAM1::init();
	for(reg int i=1;i<=n;++i)
		SAM1::insert(s[i]-'a',i);
	SAM1::build();
	reg int q=read();
	while(q--){
		static char t[MAXT];
		SAM2::init();
		reg int m=read(t+1)-(t+1);
		reg int l=read(),r=read();
		int ptr=1;
		static int pos[MAXT];
		for(reg int i=1;i<=m;++i){
			pos[i]=pos[i-1];
			SAM1::find(ptr,pos[i],l,r,t[i]-'a');
			SAM2::insert(t[i]-'a');
		}
		writeln(SAM2::calc(pos));
	}
	flush();
	fclose(stdin);
	fclose(stdout);
	fprintf(stderr,"%.3lf s\n",1.0*clock()/CLOCKS_PER_SEC);
	fprintf(stderr,"%.3lf MiB\n",(&ed-&st)/1048576.0);
	return 0;
}