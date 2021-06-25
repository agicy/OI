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

inline void writeln(reg int x){
	static char buf[32];
	reg int p=-1;
	if(x==0) putchar('0');
	else while(x) buf[++p]=(x%10)^'0',x/=10;
	while(~p) putchar(buf[p--]);
	putchar('\n');
	return;
}

const int MAXN=1e5+5;
const int MAXQ=1e5+5;
const int MAXLOG2A=25;
const int MAXSIZE=MAXN*40;

int n,q;
int a[MAXN],b[MAXN];
int c[MAXQ],d[MAXQ];
int id[MAXN];
int ans[MAXQ];

inline bool cmpb(reg int x,reg int y){
	return b[x]<b[y];
}

inline bool cmpd(reg int x,reg int y){
	return d[x]<d[y];
}

namespace SegmentTree{
	namespace TrieA{
		struct Node{
			int ch[2];
			int siz;
			#define ch(x) unit[(x)].ch
			#define siz(x) unit[(x)].siz
		};
		int tot,rt;
		Node unit[MAXSIZE];
		inline int New(void){
			reg int p=++tot;
			ch(p)[0]=ch(p)[1]=siz(p)=0;
			return p;
		}
		inline void clear(void){
			tot=0,rt=New();
			return;
		}
		inline void insert(reg int x,reg int val){
			reg int p=rt;
			siz(p)+=val;
			for(reg int i=MAXLOG2A-1;i>=0;--i){
				reg int c=(x>>i)&1;
				if(!ch(p)[c])
					ch(p)[c]=New();
				p=ch(p)[c];
				siz(p)+=val;
			}
			return;
		}
		inline int query(reg int x,reg int d,reg int c,reg int dep){
			if(!x)
				return 0;
			if(dep==-1)
				return siz(x);
			reg int dc=(d>>dep)&1,cc=(c>>dep)&1;
			if(!dc)
				return query(ch(x)[cc],d,c,dep-1);
			else
				return siz(ch(x)[cc])+query(ch(x)[cc^1],d,c,dep-1);
		}
		#undef ch
		#undef siz
	}
	namespace TrieB{
		struct Node{
			int ch[2];
			int siz;
			#define ch(x) unit[(x)].ch
			#define siz(x) unit[(x)].siz
		};
		int tot,rt;
		Node unit[MAXSIZE];
		inline int New(void){
			reg int p=++tot;
			ch(p)[0]=ch(p)[1]=siz(p)=0;
			return p;
		}
		inline void clear(void){
			tot=0,rt=New();
			return;
		}
		inline void insert(reg int p,reg int a,reg int b,reg int dep){
			if(!p)
				return;
			if(dep==-1){
				++siz(p);
				return;
			}
			if(!ch(p)[0])
				ch(p)[0]=New();
			if(!ch(p)[1])
				ch(p)[1]=New();
			reg int ac=(a>>dep)&1,bc=(b>>dep)&1;
			if(!bc)
				insert(ch(p)[ac],a,b,dep-1);
			else{
				++siz(ch(p)[ac]);
				insert(ch(p)[ac^1],a,b,dep-1);
			}
			return;
		}
		inline int query(reg int p,reg int d,reg int dep){
			if(!p)
				return 0;
			if(dep==-1)
				return siz(p);
			reg int c=(d>>dep)&1;
			return siz(p)+query(ch(p)[c],d,dep-1);
		}
		#undef ch
		#undef siz
	}
	#define lson ( (k) << 1 )
	#define rson ( (k) << 1 | 1 )
	#define mid ( ( (l) + (r) ) >> 1 )
	struct Node{
		vector<int> V;
		#define V(x) unit[(x)].V
	};
	Node unit[MAXN<<2];
	inline void update(reg int k,reg int l,reg int r,reg int L,reg int R,int val){
		if(L<=l&&r<=R){
			V(k).push_back(val);
			return;
		}
		if(L<=mid)
			update(lson,l,mid,L,R,val);
		if(R>mid)
			update(rson,mid+1,r,L,R,val);
		return;
	}
	inline void solve(reg int k,reg int l,reg int r){
		sort(V(k).begin(),V(k).end(),cmpd);
		for(reg int i=l;i<=r;++i)
			id[i]=i;
		sort(id+l,id+r+1,cmpb);
		TrieA::clear(),TrieB::clear();
		for(reg int i=l;i<=r;++i)
			TrieA::insert(a[id[i]],1);
		for(reg int i=0,j=l,siz=V(k).size();i<siz;++i){
			while(d[V(k)[i]]>=b[id[j]]&&j<=r){
				TrieA::insert(a[id[j]],-1);
				TrieB::insert(TrieB::rt,a[id[j]],b[id[j]],MAXLOG2A-1);
				++j;
			}
			ans[V(k)[i]]+=TrieA::query(TrieA::rt,d[V(k)[i]],c[V(k)[i]],MAXLOG2A-1);
			ans[V(k)[i]]+=TrieB::query(TrieB::rt,c[V(k)[i]],MAXLOG2A-1);
		}
		if(l!=r)
			solve(lson,l,mid),solve(rson,mid+1,r);
		return;
	}
	#undef lson
	#undef rson
	#undef mid
	#undef V
}

int main(void){
	n=read(),q=read();
	for(reg int i=1;i<=n;++i)
		a[i]=read(),b[i]=read();
	for(reg int i=1;i<=q;++i){
		static int l,r;
		l=read(),r=read(),c[i]=read(),d[i]=read();
		SegmentTree::update(1,1,n,l,r,i);
	}
	SegmentTree::solve(1,1,n);
	for(reg int i=1;i<=q;++i)
		writeln(ans[i]);
	flush();
	return 0;
}