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
const int inf=0x3f3f3f3f;

int n,m;
int a[MAXN],lson[MAXN],rson[MAXN];
bool Rson[MAXN];
int rt;
int fa[MAXN];
int siz[MAXN],son[MAXN];

inline void dfs1(reg int u){
	siz[u]=1;
	if(lson[u]){
		dfs1(lson[u]);
		siz[u]+=siz[lson[u]];
		if(siz[son[u]]<siz[lson[u]])
			son[u]=lson[u];
	}
	if(rson[u]){
		dfs1(rson[u]);
		siz[u]+=siz[rson[u]];
		if(siz[son[u]]<siz[rson[u]])
			son[u]=rson[u];
	}
	return;
}

int tim,dfn[MAXN],rnk[MAXN];
int top[MAXN];

inline void dfs2(reg int u,reg int topf){
	rnk[dfn[u]=++tim]=u;
	top[u]=topf;
	if(!son[u])
		return;
	dfs2(son[u],topf);
	if(lson[u]&&lson[u]!=son[u])
		dfs2(lson[u],lson[u]);
	if(rson[u]&&rson[u]!=son[u])
		dfs2(rson[u],rson[u]);
	return;
}

namespace SegmentTree{
	#define lson ( (k) << 1 )
	#define rson ( (k) << 1 | 1 )
	#define mid ( ( (l) + (r) ) >>  1 )
	struct Data{
		int lef,rig;
		inline Data(reg int lef=-inf,reg int rig=inf):lef(lef),rig(rig){
			return;
		}
	};
	inline Data operator+(const Data& a,const Data& b){
		return Data(max(a.lef,b.lef),min(a.rig,b.rig));
	}
	struct Node{
		Data dat[2];
		bool tag;
		bool tRev;
		#define dat(x) unit[(x)].dat
		#define tag(x) unit[(x)].tag
		#define tRev(x) unit[(x)].tRev
	};
	Node unit[MAXN<<2];
	inline void pushup(reg int k){
		dat(k)[0]=dat(lson)[0]+dat(rson)[0],dat(k)[1]=dat(lson)[1]+dat(rson)[1];
		return;
	}
	inline void build(reg int k,reg int l,reg int r){
		if(l==r){
			reg int u=rnk[l],f=fa[u];
			tag(k)=Rson[u];
			if(u==rt)
				dat(k)[0]=dat(k)[1]=Data(-inf,inf);
			else if(!tag(k))
				dat(k)[0]=Data(-inf,a[f]-1),dat(k)[1]=Data(a[f]+1,inf);
			else
				dat(k)[0]=Data(a[f]+1,inf),dat(k)[1]=Data(-inf,a[f]-1);
			return;
		}
		build(lson,l,mid),build(rson,mid+1,r);
		pushup(k);
		return;
	}
	inline void rev(reg int k){
		swap(dat(k)[0],dat(k)[1]);
		tag(k)=!tag(k);
		tRev(k)=!tRev(k);
		return;
	}
	inline void pushdown(reg int k){
		if(tRev(k)){
			rev(lson),rev(rson);
			tRev(k)=false;
		}
		return;
	}
	inline void update(reg int k,reg int l,reg int r,reg int pos){
		if(l==r){
			reg int u=rnk[l],f=fa[u];
			if(u==rt)
				dat(k)[0]=dat(k)[1]=Data(-inf,inf);
			else if(!tag(k))
				dat(k)[0]=Data(-inf,a[f]-1),dat(k)[1]=Data(a[f]+1,inf);
			else
				dat(k)[0]=Data(a[f]+1,inf),dat(k)[1]=Data(-inf,a[f]-1);
			return;
		}
		pushdown(k);
		if(pos<=mid)
			update(lson,l,mid,pos);
		else
			update(rson,mid+1,r,pos);
		pushup(k);
		return;
	}
	inline void update(reg int k,reg int l,reg int r,reg int L,reg int R){
		if(L<=l&&r<=R){
			rev(k);
			return;
		}
		pushdown(k);
		if(L<=mid)
			update(lson,l,mid,L,R);
		if(R>mid)
			update(rson,mid+1,r,L,R);
		pushup(k);
		return;
	}
	inline Data query(reg int k,reg int l,reg int r,reg int L,reg int R){
		if(L<=l&&r<=R)
			return dat(k)[0];
		pushdown(k);
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
	n=read(),m=read();
	for(reg int i=1;i<=n;++i){
		a[i]=read(),lson[i]=read(),rson[i]=read();
		if(lson[i])
			fa[lson[i]]=i;
		if(rson[i])
			Rson[rson[i]]=true,fa[rson[i]]=i;
	}
	for(reg int i=1;i<=n;++i)
		if(!fa[i]){
			rt=i;
			break;
		}
	dfs1(rt),dfs2(rt,rt);
	SegmentTree::build(1,1,n);
	while(m--){
		static int opt,x;
		opt=read(),x=read();
		switch(opt){
			case 1:{
				a[x]=read();
				if(lson[x])
					SegmentTree::update(1,1,n,dfn[lson[x]]);
				if(rson[x])
					SegmentTree::update(1,1,n,dfn[rson[x]]);
				break;
			}
			case 2:{
				if(lson[x])
					SegmentTree::update(1,1,n,dfn[lson[x]],dfn[lson[x]]+siz[lson[x]]-1);
				if(rson[x])
					SegmentTree::update(1,1,n,dfn[rson[x]],dfn[rson[x]]+siz[rson[x]]-1);
				break;
			}
			case 3:{
				reg int tmp=x;
				static SegmentTree::Data ans;
				ans=SegmentTree::Data(-inf,inf);
				while(tmp)
					ans=ans+SegmentTree::query(1,1,n,dfn[top[tmp]],dfn[tmp]),tmp=fa[top[tmp]];
				writeln((ans.lef<=a[x]&&a[x]<=ans.rig)?"YES":"NO");
				break;
			}
		}
	}
	flush();
	return 0;
}