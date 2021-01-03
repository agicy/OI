#include<bits/stdc++.h>
using namespace std;
#define reg register
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
#define flush() (fwrite(wbuf,1,wp1,stdout),wp1=0)
#define putchar(c)(wp1==wp2&&(flush(),0),wbuf[wp1++]=c)
static char wbuf[1<<21];int wp1;const int wp2=1<<21;
inline int read(void){
	reg bool f=false;
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))f|=(ch=='-'),ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return f?-res:res;
}

inline void write(reg int x){
	static char buf[32];
	reg int p=-1;
	if(x==0) putchar('0');
	else while(x) buf[++p]=(x%10)^'0',x/=10;
	while(~p) putchar(buf[p--]);
	return;
}

const int MAXN=1e5+5;
const int MAXM=2e5+5;
const int MAXK=3e5+5;
const int MAXLOG2K=19+1;
const int MAXSIZE=MAXK*MAXLOG2K+MAXM;
const int MAXVCNT=(MAXN<<2)+MAXN;
const int inf=1e9;

inline void Read(void);
inline void Work(void);

int main(void){
	Read();
	Work();
	flush();
	return 0;
}

int n,s,m;
int indeg[MAXVCNT],f[MAXVCNT],Min[MAXVCNT];
int cnt,head[MAXVCNT],to[MAXSIZE],w[MAXSIZE],Next[MAXSIZE];

inline void Add_Edge(reg int u,reg int v,reg int len){
	Next[++cnt]=head[u];
	to[cnt]=v;
	w[cnt]=len;
	head[u]=cnt;
	++indeg[v];
	return;
}

namespace SegmentTree{
	#define mid ( ( (l) + (r) ) >> 1 )
	struct Node{
		int lson,rson;
		#define lson(x) unit[(x)].lson
		#define rson(x) unit[(x)].rson
	};
	int tot,id[MAXN];
	Node unit[MAXVCNT];
	inline void build(reg int k,reg int l,reg int r){
		if(l==r){
			id[l]=k;
			//tot=max(tot,k);
			return;
		}
		lson(k)=++tot,rson(k)=++tot;
		build(lson(k),l,mid),build(rson(k),mid+1,r);
		Add_Edge(k,lson(k),0),Add_Edge(k,rson(k),0);
		return;
	}
	inline void update(reg int k,reg int l,reg int r,reg int L,reg int R,reg int pos){
		if(L<=l&&r<=R){
			Add_Edge(pos,k,1);
			return;
		}
		if(L<=mid&&mid<R)
			update(lson(k),l,mid,L,R,pos),update(rson(k),mid+1,r,L,R,pos);
		else if(L<=mid)
			update(lson(k),l,mid,L,R,pos);
		else
			update(rson(k),mid+1,r,L,R,pos);
		return;
	}
	#undef mid
}

using namespace SegmentTree;

inline void Read(void){
	n=read(),s=read(),m=read();
	SegmentTree::tot=1;
	SegmentTree::build(1,1,n);
	for(reg int i=1;i<=s;++i){
		static int p,d;
		p=read(),d=read();
		Min[id[p]]=f[id[p]]=d;
	}
	for(reg int i=1;i<=m;++i){
		static int l,r,k;
		l=read(),r=read(),k=read();
		reg int ptr=l;
		++tot;
		for(reg int j=1;j<=k;++j){
			static int x;
			x=read();
			Add_Edge(id[x],tot,0);
			if(ptr<=x-1)
				SegmentTree::update(1,1,n,ptr,x-1,tot);
			ptr=x+1;
		}
		if(ptr<=r)
			SegmentTree::update(1,1,n,ptr,r,tot);
	}
	return;
}

bool flag;
bool vis[MAXVCNT],ins[MAXVCNT];

inline void dfs(reg int u){
	vis[u]=ins[u]=true;
	for(reg int i=head[u];i&&flag;i=Next[i]){
		if(ins[to[i]]){
			flag=false;
			return;
		}
		if(!vis[to[i]])
			dfs(to[i]);
	}
	ins[u]=false;
	return;
}

int Q[MAXVCNT];

inline void Work(void){
	reg int h=0,t=0;
	for(reg int i=1;i<=tot;++i){
		if(!f[i])
			f[i]=inf;
		if(!vis[i]){
			flag=true;
			dfs(i);
			if(!flag){
				putchar('N'),putchar('o'),putchar('\n');
				return;
			}
		}
		if(!indeg[i])
			Q[t++]=i;
	}
	while(h<t){
		reg int u=Q[h++];
		for(reg int i=head[u];i;i=Next[i]){
			reg int v=to[i];
			--indeg[v];
			if(Min[v]>f[u]-w[i]){
				putchar('N'),putchar('o'),putchar('\n');
				return;
			}
			f[v]=min(f[v],f[u]-w[i]);
			if(!indeg[v])
				Q[t++]=v;
			if(f[v]<1){
				putchar('N'),putchar('o'),putchar('\n');
				return;
			}
		}
	}
	putchar('Y'),putchar('e'),putchar('s'),putchar('\n');
	for(reg int i=1;i<=n;++i)
		write(f[id[i]]),putchar(i==n?'\n':' ');
	return;
}