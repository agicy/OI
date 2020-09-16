#include<bits/stdc++.h>
using namespace std;
#define reg register
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg bool f=false;
	reg char ch=getchar();
	reg int res=0;
	while(ch<'0'||'9'<ch)f|=(ch=='-'),ch=getchar();
	while('0'<=ch&&ch<='9')res=10*res+ch-'0',ch=getchar();
	return f?-res:res;
}

inline void Err(void){
	puts("NIE");
	exit(0);
	return;
}

inline void cMax(reg int &x,reg int y){
	if(x<y)
		x=y;
	return;
}

inline void cMin(reg int &x,reg int y){
	if(x>y)
		x=y;
	return;
}

const int MAXN=1e5+5;
const int MAXM=2e5+5;
const int MAXK=3e5+5;
const int MAXLOG2K=19+1;
const int MAXV=(MAXN<<2)+MAXN;
const int MAXE=MAXK*MAXLOG2K+MAXM;
const int inf=1e9;

int n,s,m;
int inDeg[MAXV],f[MAXV],Min[MAXV];
int cnt,head[MAXV],to[MAXE],w[MAXE],Next[MAXE];

inline void Add_Edge(reg int u,reg int v,reg int len){
	Next[++cnt]=head[u];
	to[cnt]=v;
	w[cnt]=len;
	head[u]=cnt;
	++inDeg[v];
	return;
}

int tot,id[MAXN];

namespace SegmentTree{
	#define mid ( ( (l) + (r) ) >> 1 )
	int lson[MAXV],rson[MAXV];
	inline void build(int k,reg int l,reg int r){
		if(l==r){
			id[l]=k;
			cMax(tot,k);
			return;
		}
		lson[k]=++tot,build(lson[k],l,mid),Add_Edge(k,lson[k],0);
		rson[k]=++tot,build(rson[k],mid+1,r),Add_Edge(k,rson[k],0);
		return;
	}
	inline void update(reg int k,reg int l,reg int r,reg int L,reg int R,reg int pos){
		if(L<=l&&r<=R){
			Add_Edge(pos,k,1);
			return;
		}
		if(L<=mid)
			update(lson[k],l,mid,L,R,pos);
		if(R>mid)
			update(rson[k],mid+1,r,L,R,pos);
		return;
	}
	#undef mid
}

bool flag;
bool vis[MAXV],ins[MAXV];

inline void dfs(reg int id){
	vis[id]=ins[id]=true;
	for(reg int i=head[id];i&&flag;i=Next[i]){
		reg int v=to[i];
		if(ins[v]){
			flag=false;
			return;
		}
		if(!vis[v])
			dfs(v);
	}
	ins[id]=false;
	return;
}

queue<int> Q;
using namespace SegmentTree;

int main(void){
	n=read(),s=read(),m=read();
	tot=1;
	build(1,1,n);
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
				update(1,1,n,ptr,x-1,tot);
			ptr=x+1;
		}
		if(ptr<=r)
			update(1,1,n,ptr,r,tot);
	}
	for(reg int i=1;i<=tot;++i)
		if(!f[i])
			f[i]=inf;
	for(reg int i=1;i<=tot;++i)
		if(!vis[i]){
			flag=true;
			dfs(i);
			if(!flag)
				Err();
		}
	for(int i=1;i<=tot;++i)
		if(!inDeg[i])
			Q.push(i);
	while(!Q.empty()){
		reg int u=Q.front();
		Q.pop();
		for(reg int i=head[u];i;i=Next[i]){
			int v=to[i];
			--inDeg[v];
			if(Min[v]>f[u]-w[i])
				Err();
			cMin(f[v],f[u]-w[i]);
			if(!inDeg[v])
				Q.push(v);
			if(f[v]<1)
				Err();
		}
	}
	puts("TAK");
	for(reg int i=1;i<=n;++i)
		printf("%d%c",f[id[i]],i==n?'\n':' ');
	return 0;
}