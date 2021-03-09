#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar()(p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
#define flush() (fwrite(wbuf,1,wp1,stdout),wp1=0)
#define putchar(c) (wp1==wp2&&(flush(),0),wbuf[wp1++]=c)
static char wbuf[1<<21];int wp1;const int wp2=1<<21;
inline int read(void){
	reg bool f=false;
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))f|=(ch=='-'),ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return f?-res:res;
}

inline void writeln(reg ll x){
	static char buf[32];
	reg int p=-1;
	if(x==0) putchar('0');
	else while(x) buf[++p]=(x%10)^'0',x/=10;
	while(~p) putchar(buf[p--]);
	putchar('\n');
	return;
}

inline ll min(reg ll a,reg ll b){
	return a<b?a:b;
}

const int MAXN=2e5+5;
const int MAXM=2e5+5;
const ll inf=0x3f3f3f3f3f3f3f3f;

int n,m,rt;
int cnt,head[MAXN],to[MAXN<<1],w[MAXN<<1],Next[MAXN<<1];
int a[MAXN];
int opt[MAXM],l[MAXM],r[MAXM];

inline void Add_Edge(reg int u,reg int v,reg int len){
	Next[++cnt]=head[u];
	to[cnt]=v,w[cnt]=len;
	head[u]=cnt;
	return;
}

namespace Subtask1{
	const int MAXN=1e3+5;
	int fa[MAXN];
	ll dep[MAXN];
	inline void dfs(reg int u,reg int father){
		fa[u]=father;
		for(reg int i=head[u];i;i=Next[i]){
			reg int v=to[i];
			if(v!=father){
				dep[v]=dep[u]+w[i];
				dfs(v,u);
			}
		}
		return;
	}
	static int tmp[MAXN];
	inline void Solve(void){
		dfs(rt,0);
		fa[rt]=rt;
		for(reg int i=1;i<=n;++i)
			tmp[i]=a[i];
		for(reg int i=1;i<=m;++i)
			switch(opt[i]){
				case 1:{
					for(reg int j=l[i];j<=r[i];++j)
						tmp[j]=fa[tmp[j]];
					break;
				}
				case 2:{
					reg ll Min=inf;
					for(reg int j=l[i];j<=r[i];++j)
						Min=min(Min,dep[tmp[j]]);
					writeln(Min);
					break;
				}
			}
		flush();
		return;
	}
}

namespace Subtask2{
	int fa[MAXN],dep[MAXN];
	inline void dfs(reg int u,reg int father){
		fa[u]=father;
		for(reg int i=head[u];i;i=Next[i]){
			reg int v=to[i];
			if(v!=father){
				dep[v]=dep[u]+w[i];
				dfs(v,u);
			}
		}
		return;
	}
	namespace SegmentTree{
		#define lson ( (k) << 1 )
		#define rson ( (k) << 1 | 1 )
		#define mid ( ( (l) + (r) ) >> 1 )
		struct Node{
			int Min,tag;
			#define Min(x) unit[(x)].Min
			#define tag(x) unit[(x)].tag
		};
		Node unit[MAXN<<2];
		inline void pushup(reg int k){
			Min(k)=min(Min(lson),Min(rson));
			return;
		}
		inline void build(reg int k,reg int l,reg int r,reg int val[]){
			tag(k)=0;
			if(l==r){
				Min(k)=val[l];
				return;
			}
			build(lson,l,mid,val),build(rson,mid+1,r,val);
			pushup(k);
			return;
		}
		inline void add(reg int k,reg int val){
			Min(k)+=val,tag(k)+=val;
			return;
		}
		inline void pushdown(reg int k){
			if(tag(k)){
				add(lson,tag(k)),add(rson,tag(k));
				tag(k)=0;
			}
			return;
		}
		inline void update(reg int k,reg int l,reg int r,reg int L,reg int R,reg int val){
			if(L<=l&&r<=R){
				add(k,val);
				return;
			}
			pushdown(k);
			if(L<=mid)
				update(lson,l,mid,L,R,val);
			if(R>mid)
				update(rson,mid+1,r,L,R,val);
			pushup(k);
			return;
		}
		inline int query(reg int k,reg int l,reg int r,reg int L,reg int R){
			if(L<=l&&r<=R)
				return Min(k);
			pushdown(k);
			if(L<=mid&&mid<R)
				return min(query(lson,l,mid,L,R),query(rson,mid+1,r,L,R));
			else if(L<=mid)
				return query(lson,l,mid,L,R);
			else
				return query(rson,mid+1,r,L,R);
		}
		#undef Min
		#undef tag
		#undef lson
		#undef rson
		#undef mid
	}
	inline void Solve(void){
		dfs(rt,0);
		static int val[MAXN];
		for(reg int i=1;i<=n;++i)
			val[i]=dep[a[i]];
		SegmentTree::build(1,1,n,val);
		for(reg int i=1;i<=m;++i)
			switch(opt[i]){
				case 1:{
					SegmentTree::update(1,1,n,l[i],r[i],-1);
					break;
				}
				case 2:{
					writeln(SegmentTree::query(1,1,n,l[i],r[i]));
					break;
				}
			}
		flush();
		return;
	}
}

namespace checkSubtask3{
	const int MAXLOG2N=18+1;
	int fa[MAXN][MAXLOG2N];
	int cnt[MAXN];
	ll dep[MAXN];
	inline void dfs(reg int u,reg int father){
		fa[u][0]=father;
		for(reg int i=1;i<MAXLOG2N;++i)
			fa[u][i]=fa[fa[u][i-1]][i-1];
		for(reg int i=head[u];i;i=Next[i]){
			reg int v=to[i];
			if(v!=father){
				cnt[v]=cnt[u]+1;
				dep[v]=dep[u]+w[i];
				dfs(v,u);
			}
		}
		return;
	}
	inline int getFa(reg int u,reg int dep){
		for(reg int i=MAXLOG2N-1;i>=0;--i)
			if((dep>>i)&1)
				u=fa[u][i];
		return u;
	}
}

namespace Subtask3{
	using namespace checkSubtask3;
	namespace SegmentTree{
		#define lson ( (k) << 1 )
		#define rson ( (k) << 1 | 1 )
		#define mid ( ( (l) + (r) ) >> 1 )
		struct Node{
			int id;
			int Maxdep;
			#define id(x) unit[(x)].id
			#define Maxdep(x) unit[(x)].Maxdep
		};
		Node unit[MAXN<<2];
		inline void pushup(reg int k){
			Maxdep(k)=max(Maxdep(lson),Maxdep(rson));
			id(k)=dep[id(lson)]<dep[id(rson)]?id(lson):id(rson);
			return;
		}
		inline void build(reg int k,reg int l,reg int r,reg int a[]){
			if(l==r){
				id(k)=a[l];
				Maxdep(k)=checkSubtask3::cnt[a[l]];
				return;
			}
			build(lson,l,mid,a),build(rson,mid+1,r,a);
			pushup(k);
			return;
		}
		inline void update(reg int k,reg int l,reg int r,reg int L,reg int R){
			if(Maxdep(k)<0)
				return;
			if(l==r){
				id(k)=fa[id(k)][0];
				--Maxdep(k);
				return;
			}
			if(L<=mid)
				update(lson,l,mid,L,R);
			if(R>mid)
				update(rson,mid+1,r,L,R);
			pushup(k);
			return;
		}
		inline ll query(reg int k,reg int l,reg int r,reg int L,reg int R){
			if(L<=l&&r<=R)
				return dep[id(k)];
			if(L<=mid&&mid<R)
				return min(query(lson,l,mid,L,R),query(rson,mid+1,r,L,R));
			else if(L<=mid)
				return query(lson,l,mid,L,R);
			else
				return query(rson,mid+1,r,L,R);
		}
		#undef id
		#undef Maxdep
		#undef lson
		#undef rson
		#undef mid
	}
	inline void Solve(void){
		SegmentTree::build(1,1,n,a);
		for(reg int i=1;i<=m;++i){
			switch(opt[i]){
				case 1:{
					SegmentTree::update(1,1,n,l[i],r[i]);
					break;
				}
				case 2:{
					writeln(SegmentTree::query(1,1,n,l[i],r[i]));
					break;
				}
			}
			if(!(i&32767))
			cerr<<i<<endl;
		}
		flush();
		return;
	}
}

namespace Subtask4{
	using namespace checkSubtask3;
	namespace SegmentTree{
		#define lson ( (k) << 1 )
		#define rson ( (k) << 1 | 1 )
		#define mid ( ( (l) + (r) ) >> 1 )
		struct Node{
			int idd,idc;
			int Maxdep;
			int tag;
			#define idd(x) unit[(x)].idd
			#define idc(x) unit[(x)].idc
			#define Maxdep(x) unit[(x)].Maxdep
			#define tag(x) unit[(x)].tag
		};
		Node unit[MAXN<<2];
		inline void pushup(reg int k){
			idd(k)=dep[idd(lson)]<dep[idd(rson)]?idd(lson):idd(rson);
			idc(k)=checkSubtask3::cnt[idc(lson)]<checkSubtask3::cnt[idc(rson)]?idc(lson):idc(rson);
			if(dep[idd(k)]>dep[idc(k)])
				idd(k)=idc(k);
			Maxdep(k)=max(Maxdep(lson),Maxdep(rson));
			return;
		}
		inline void build(reg int k,reg int l,reg int r,reg int a[]){
			tag(k)=0;
			if(l==r){
				idd(k)=idc(k)=a[l];
				Maxdep(k)=checkSubtask3::cnt[a[l]];
				return;
			}
			build(lson,l,mid,a),build(rson,mid+1,r,a);
			pushup(k);
			return;
		}
		inline void cut(reg int k,reg int val){
			idd(k)=getFa(idd(k),val);
			idc(k)=getFa(idc(k),val);
			Maxdep(k)-=val;
			tag(k)+=val;
			return;
		}
		inline void pushdown(reg int k){
			if(tag(k)){
				cut(lson,tag(k)),cut(rson,tag(k));
				tag(k)=0;
			}
			return;
		}
		inline void update(reg int k,reg int l,reg int r,reg int L,reg int R){
			if(Maxdep(k)<=0)
				return;
			if(L<=l&&r<=R){
				cut(k,1);
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
		inline ll query(reg int k,reg int l,reg int r,reg int L,reg int R){
			if(L<=l&&r<=R)
				return min(dep[idd(k)],dep[idc(k)]);
			pushdown(k);
			if(L<=mid&&mid<R)
				return min(query(lson,l,mid,L,R),query(rson,mid+1,r,L,R));
			else if(L<=mid)
				return query(lson,l,mid,L,R);
			else
				return query(rson,mid+1,r,L,R);
		}
		#undef id
		#undef Maxdep
		#undef tag
		#undef lson
		#undef rson
		#undef mid
	}
	inline void Solve(void){
		SegmentTree::build(1,1,n,a);
		for(reg int i=1;i<=m;++i)
			switch(opt[i]){
				case 1:{
					SegmentTree::update(1,1,n,l[i],r[i]);
					break;
				}
				case 2:{
					writeln(SegmentTree::query(1,1,n,l[i],r[i]));
					break;
				}
			}
		flush();
		return;
	}
}

int main(void){
	n=read(),m=read(),rt=read();
	reg bool subtask2flag=true;
	for(reg int i=1;i<n;++i){
		static int u,v,w;
		u=read(),v=read(),w=read();
		Add_Edge(u,v,w),Add_Edge(v,u,w);
		if(w!=1)
			subtask2flag=false;
	}
	for(reg int i=1;i<=n;++i)
		a[i]=read();
	for(reg int i=1;i<=m;++i)
		opt[i]=read(),l[i]=read(),r[i]=read();
	if(n<=1e3&&m<=1e3)
		Subtask1::Solve();
	else if(subtask2flag)
		Subtask2::Solve();
	else{
		checkSubtask3::dfs(rt,rt);
		reg bool subtask3flag=true;
		for(reg int i=1;i<=n;++i)
			if(checkSubtask3::cnt[i]>500)
				subtask3flag=false;
		if(subtask3flag)
			Subtask3::Solve();
		else
			Subtask4::Solve();
	}
	return 0;
}