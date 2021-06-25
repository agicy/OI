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
	while(!isdigit(ch))ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return res;
}

inline void writeln(const char *s){
	while(*s) putchar(*(s++));
	putchar('\n');
	return;
}

inline int max(reg int a,reg int b){
	return a>b?a:b;
}

inline int min(reg int a,reg int b){
	return a<b?a:b;
}

const int MAXN=1e5+5;
const int MAXM=1e5+5;

struct operation{
	int opt,x,y;
};

int n,m;
int a[MAXN],ch[MAXN][2];
bool isSon[MAXN];
int rt;
operation op[MAXM];

namespace Subtask1{
	const int MAXN=5e3+5;
	struct Node{
		int lson,rson,val;
		bool tRev;
	};
	Node unit[MAXN];
	inline void update(reg int p,reg int v){
		unit[p].val=v;
		return;
	}
	inline void reverse(reg int p){
		swap(unit[p].lson,unit[p].rson);
		unit[p].tRev=!unit[p].tRev;
		return;
	}
	inline void pushdown(reg int p){
		if(unit[p].tRev){
			if(unit[p].lson)
				reverse(unit[p].lson);
			if(unit[p].rson)
				reverse(unit[p].rson);
			unit[p].tRev=false;
		}
		return;
	}
	inline bool query(reg int p,reg int x){
		if(!p)
			return false;
		if(p==x)
			return true;
		pushdown(p);
		if(unit[x].val<unit[p].val)
			return query(unit[p].lson,x);
		else
			return query(unit[p].rson,x);
	}
	inline void Solve(void){
		for(reg int i=1;i<=n;++i)
			unit[i].val=a[i],unit[i].lson=ch[i][0],unit[i].rson=ch[i][1];
		for(reg int i=1;i<=m;++i)
			switch(op[i].opt){
				case 1:{
					update(op[i].x,op[i].y);
					break;
				}
				case 2:{
					reverse(op[i].x);
					break;
				}
				case 3:{
					reg bool res=query(rt,op[i].x);
					writeln(res?"YES":"NO");
					break;
				}
			}
		return;
	}
}

namespace Subtask2{
	const int inf=0x3f3f3f3f;
	vector<int> G[MAXN];
	int fa[MAXN],dep[MAXN];
	int siz[MAXN],son[MAXN];
	inline void dfs1(reg int u,reg int father){
		siz[u]=1;
		fa[u]=father;
		dep[u]=dep[father]+1;
		for(reg int i=0,_siz=G[u].size();i<_siz;++i){
			reg int v=G[u][i];
			dfs1(v,u);
			siz[u]+=siz[v];
			if(siz[son[u]]<siz[v])
				son[u]=v;
		}
		return;
	}
	int tim,dfn[MAXN];
	int top[MAXN];
	inline void dfs2(reg int u,reg int topf){
		dfn[u]=++tim;
		top[u]=topf;
		if(!son[u])
			return;
		dfs2(son[u],topf);
		for(reg int i=0,siz=G[u].size();i<siz;++i){
			reg int v=G[u][i];
			if(v!=son[u])
				dfs2(v,v);
		}
		return;
	}
	int le[MAXN],ri[MAXN];
	inline void dfs(reg int u,reg int lef,reg int rig){
		if(!u)
			return;
		if(!lef)
			le[u]=u;
		else
			le[u]=lef;
		if(!rig)
			ri[u]=u;
		else
			ri[u]=rig;
		dfs(ch[u][0],lef?lef:ch[u][0],rig?rig:u);
		dfs(ch[u][1],lef?lef:u,rig?rig:ch[u][1]);
		return;
	}
	namespace SegmentTree{
		#define lson ( (k) << 1 )
		#define rson ( (k) << 1 | 1 )
		#define mid ( ( (l) + (r) ) >> 1 )
		struct Node{
			int Max,Min;
			#define Max(x) unit[(x)].Max
			#define Min(x) unit[(x)].Min
		};
		Node unit[MAXN<<2];
		inline void pushup(reg int k){
			Max(k)=max(Max(lson),Max(rson));
			Min(k)=min(Min(lson),Min(rson));
			return;
		}
		inline void build(reg int k,reg int l,reg int r,reg int a[]){
			if(l==r){
				Max(k)=Min(k)=a[l];
				return;
			}
			build(lson,l,mid,a),build(rson,mid+1,r,a);
			pushup(k);
			return;
		}
		inline void update(reg int k,reg int l,reg int r,reg int pos,reg int val){
			if(l==r){
				Max(k)=Min(k)=val;
				return;
			}
			if(pos<=mid)
				update(lson,l,mid,pos,val);
			else
				update(rson,mid+1,r,pos,val);
			pushup(k);
			return;
		}
		inline int queryMax(reg int k,reg int l,reg int r,reg int L,reg int R){
			if(L<=l&&r<=R)
				return Max(k);
			if(L<=mid&&mid<R)
				return max(queryMax(lson,l,mid,L,R),queryMax(rson,mid+1,r,L,R));
			else if(L<=mid)
				return queryMax(lson,l,mid,L,R);
			else
				return queryMax(rson,mid+1,r,L,R);
		}
		inline int queryMin(reg int k,reg int l,reg int r,reg int L,reg int R){
			if(L<=l&&r<=R)
				return Min(k);
			if(L<=mid&&mid<R)
				return min(queryMin(lson,l,mid,L,R),queryMin(rson,mid+1,r,L,R));
			else if(L<=mid)
				return queryMin(lson,l,mid,L,R);
			else
				return queryMin(rson,mid+1,r,L,R);
		}
		#undef lson
		#undef rson
		#undef mid
	}
	inline int queryMax(reg int x){
		reg int res=-inf;
		while(top[x]!=rt){
			res=max(res,SegmentTree::queryMax(1,1,n,dfn[top[x]],dfn[x]));
			x=fa[top[x]];
		}
		res=max(res,SegmentTree::queryMax(1,1,n,dfn[rt],dfn[x]));
		return res;
	}
	inline int queryMin(reg int x){
		reg int res=inf;
		while(top[x]!=rt){
			res=min(res,SegmentTree::queryMin(1,1,n,dfn[top[x]],dfn[x]));
			x=fa[top[x]];
		}
		res=min(res,SegmentTree::queryMin(1,1,n,dfn[rt],dfn[x]));
		return res;
	}
	inline bool query(reg int u){
		reg int Max=queryMax(u),Min=queryMin(u);
		reg int lVal=a[le[u]],rVal=a[ri[u]];
		return Max==rVal&&Min==lVal;
	}
	inline void Solve(void){
		for(reg int i=1;i<=n;++i)
			for(reg int j=0;j<2;++j)
				if(ch[i][j])
					G[i].push_back(ch[i][j]);
		dfs1(rt,0),dfs2(rt,rt);
		static int val[MAXN];
		for(reg int i=1;i<=n;++i)
			val[dfn[i]]=a[i];
		SegmentTree::build(1,1,n,val);
		dfs(rt,0,0);
		for(reg int i=1;i<=m;++i)
			switch(op[i].opt){
				case 1:{
					a[op[i].x]=op[i].y;
					SegmentTree::update(1,1,n,dfn[op[i].x],op[i].y);
					break;
				}
				case 2:{
					puts("Hello, World!"),exit(0);
					break;
				}
				case 3:{
					reg bool res=query(op[i].x);
					writeln(res?"YES":"NO");
					break;
				}
			}
		return;
	}
}

namespace Subtask{
	vector<int> G[MAXN];
	int fa[MAXN],dep[MAXN];
	int siz[MAXN],son[MAXN];
	inline void dfs1(reg int u,reg int father){
		siz[u]=1;
		fa[u]=father;
		dep[u]=dep[father]+1;
		for(reg int i=0,_siz=G[u].size();i<_siz;++i){
			reg int v=G[u][i];
			dfs1(v,u);
			siz[u]+=siz[v];
			if(siz[son[u]]<siz[v])
				son[u]=v;
		}
		return;
	}
	int tim,dfn[MAXN];
	int top[MAXN];
	inline void dfs2(reg int u,reg int topf){
		dfn[u]=++tim;
		top[u]=topf;
		if(!son[u])
			return;
		dfs2(son[u],topf);
		for(reg int i=0,siz=G[u].size();i<siz;++i){
			reg int v=G[u][i];
			if(v!=son[u])
				dfs2(v,v);
		}
		return;
	}
	inline int LCA(reg int x,reg int y){
		while(top[x]!=top[y])
			if(dep[top[x]]>dep[top[y]])
				x=fa[top[x]];
			else
				y=fa[top[y]];
		return dep[x]<dep[y]?x:y;
	}
	struct Node{
		int lson,rson,val;
		bool tRev;
	};
	Node unit[MAXN];
	inline void update(reg int p,reg int v){
		unit[p].val=v;
		return;
	}
	inline void reverse(reg int p){
		swap(unit[p].lson,unit[p].rson);
		unit[p].tRev=!unit[p].tRev;
		return;
	}
	inline void pushdown(reg int p){
		if(unit[p].tRev){
			if(unit[p].lson)
				reverse(unit[p].lson);
			if(unit[p].rson)
				reverse(unit[p].rson);
			unit[p].tRev=false;
		}
		return;
	}
	inline bool query(reg int p,reg int x){
		if(!p)
			return false;
		if(p==x)
			return true;
		if(LCA(p,x)!=p)
			return false;
		pushdown(p);
		if(unit[x].val<unit[p].val)
			return query(unit[p].lson,x);
		else
			return query(unit[p].rson,x);
	}
	inline void Solve(void){
		for(reg int i=1;i<=n;++i)
			for(reg int j=0;j<2;++j)
				if(ch[i][j])
					G[i].push_back(ch[i][j]);
		dfs1(rt,0),dfs2(rt,rt);
		for(reg int i=1;i<=n;++i)
			unit[i].val=a[i],unit[i].lson=ch[i][0],unit[i].rson=ch[i][1];
		for(reg int i=1;i<=m;++i)
			switch(op[i].opt){
				case 1:{
					update(op[i].x,op[i].y);
					break;
				}
				case 2:{
					reverse(op[i].x);
					break;
				}
				case 3:{
					reg bool res=query(rt,op[i].x);
					writeln(res?"YES":"NO");
					break;
				}
			}
		return;
	}
}

int main(void){
	n=read(),m=read();
	for(reg int i=1;i<=n;++i){
		a[i]=read(),ch[i][0]=read(),ch[i][1]=read();
		isSon[ch[i][0]]=isSon[ch[i][1]]=true;
	}
	for(reg int i=1;i<=n;++i)
		if(!isSon[i]){
			rt=i;
			break;
		}
	reg bool subtask2flag=true;
	for(reg int i=1;i<=m;++i){
		op[i].opt=read();
		switch(op[i].opt){
			case 1:{
				op[i].x=read(),op[i].y=read();
				break;
			}
			case 2:{
				op[i].x=read();
				subtask2flag=false;
				break;
			}
			case 3:{
				op[i].x=read();
				break;
			}
		}
	}
	if(n<=5e3&&m<=5e3)
		Subtask1::Solve();
	else if(subtask2flag)
		Subtask2::Solve();
	else
		Subtask::Solve();
	flush();
	return 0;
}