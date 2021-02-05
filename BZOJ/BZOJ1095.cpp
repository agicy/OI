#include<bits/stdc++.h>
using namespace std;
#define reg register
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
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

inline void writeln(reg int x){
	static char buf[32];
	reg int p=-1;
	if(x<0) x=-x,putchar('-');
	if(x==0) putchar('0');
	else while(x) buf[++p]=(x%10)^'0',x/=10;
	while(~p) putchar(buf[p--]);
	putchar('\n');
	return;
}

const int MAXN=1e5+5;
const int MAXLOG2N=17+1;

int n;
int cnt,head[MAXN],to[MAXN<<1],Next[MAXN<<1];

inline void Add_Edge(reg int u,reg int v){
	Next[++cnt]=head[u];
	to[cnt]=v;
	head[u]=cnt;
	return;
}

int fa[MAXN],dep[MAXN];
int tim,dfn[MAXN],rnk[MAXN];
int bac_tim,pos[MAXN],Rnk[MAXN<<1];

inline void dfs(reg int u,reg int father){
	dep[u]=dep[father]+1;
	rnk[dfn[u]=++tim]=u;
	Rnk[pos[u]=++bac_tim]=u;
	for(reg int i=head[u];i;i=Next[i]){
		reg int v=to[i];
		if(v!=father){
			dfs(v,u);
			Rnk[++bac_tim]=u;
		}
	}
	return;
}

namespace ST_LCA{
	int Log[MAXN<<1];
	int id[MAXLOG2N+1][MAXN<<1];
	inline void Init(reg int n){
		Log[0]=-1;
		for(reg int i=1;i<=n;++i)
			Log[i]=Log[i>>1]+1;
		for(reg int i=1;i<=n;++i)
			id[0][i]=Rnk[i];
		for(reg int j=1;j<MAXLOG2N+1;++j)
			for(reg int i=1;i+(1<<j)-1<=n;++i)
				if(dep[id[j-1][i]]<dep[id[j-1][i+(1<<(j-1))]])
					id[j][i]=id[j-1][i];
				else
					id[j][i]=id[j-1][i+(1<<(j-1))];
		return;
	}
	inline int query(reg int l,reg int r){
		reg int k=Log[r-l+1];
		if(dep[id[k][l]]<dep[id[k][r-(1<<k)+1]])
			return id[k][l];
		else
			return id[k][r-(1<<k)+1];
	}
}

inline int LCA(reg int u,reg int v){
	return ST_LCA::query(min(pos[u],pos[v]),max(pos[u],pos[v]));
}

inline int getDis(reg int u,reg int v){
	reg int lca=LCA(u,v);
	return dep[u]+dep[v]-(dep[lca]<<1);
}

namespace SegmentTree{
	#define lson ( (k) << 1 )
	#define rson ( (k) << 1 | 1 )
	#define mid ( ( (l) + (r) ) >> 1 )
	struct Node{
		int dis;
		int cnt,p[2];
		#define cnt(x) unit[(x)].cnt
		#define dis(x) unit[(x)].dis
		#define p(x) unit[(x)].p
	};
	bool tag[MAXN];
	Node unit[MAXN<<2];
	inline Node operator+(const Node& a,const Node& b){
		Node res;
		res.dis=-1,res.cnt=0,res.p[0]=res.p[1]=0;
		if(a.dis==-1)
			res=b;
		else if(b.dis==-1)
			res=a;
		else{
			if(a.dis<b.dis)
				res=b;
			else
				res=a;
			for(reg int i=0;i<a.cnt;++i)
				for(reg int j=0;j<b.cnt;++j){
					reg int dis=getDis(a.p[i],b.p[j]);
					if(dis>res.dis)
						res.dis=dis,res.p[0]=a.p[i],res.p[1]=b.p[j];
				}
			res.cnt=2;
		}
		return res;
	}
	inline void pushup(reg int k){
		unit[k]=unit[lson]+unit[rson];
		return;
	}
	inline void build(reg int k,reg int l,reg int r){
		if(l==r){
			tag[l]=true,cnt(k)=1,p(k)[0]=rnk[l],dis(k)=0;
			return;
		}
		build(lson,l,mid),build(rson,mid+1,r);
		pushup(k);
		return;
	}
	inline void update(reg int k,reg int l,reg int r,reg int pos){
		if(l==r){
			if(tag[l])
				tag[l]=false,cnt(k)=0,dis(k)=-1;
			else
				tag[l]=true,cnt(k)=1,p(k)[0]=rnk[l],dis(k)=0;
			return;
		}
		if(pos<=mid)
			update(lson,l,mid,pos);
		else
			update(rson,mid+1,r,pos);
		pushup(k);
		return;
	}
	inline Node query(reg int k,reg int l,reg int r,reg int L,reg int R){
		if(L<=l&&r<=R)
			return unit[k];
		if(L<=mid&&mid<R)
			return query(lson,l,mid,L,R)+query(rson,mid+1,r,L,R);
		else if(L<=mid)
			return query(lson,l,mid,L,R);
		else
			return query(rson,mid+1,r,L,R);
	}
	#undef lson
	#undef rson
	#undef mid
}

int main(void){
	n=read();
	for(reg int i=1;i<n;++i){
		static int u,v;
		u=read(),v=read();
		Add_Edge(u,v),Add_Edge(v,u);
	}
	dfs(1,0);
	ST_LCA::Init(bac_tim);
	SegmentTree::build(1,1,n);
	reg int q=read();
	while(q--){
		static char opt;
		static int i;
		do
			opt=getchar();
		while(!isalpha(opt));
		switch(opt){
			case 'C':{
				i=read();
				SegmentTree::update(1,1,n,dfn[i]);
				break;
			}
			case 'G':{
				writeln(SegmentTree::query(1,1,n,1,n).dis);
				break;
			}
		}
	}
	flush();
	return 0;
}