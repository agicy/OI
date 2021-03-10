#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
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

inline ll readll(void){
	reg bool f=false;
	reg char ch=getchar();
	reg ll res=0;
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

const int MAXN=5e5+5;
const int MAXM=5e5+5;
const ll inf=0x3f3f3f3f3f3f3f3f;

struct querys{
	int id,s,x0;
	inline bool operator<(const querys& a)const{
		return x0<a.x0;
	}
};

int n,m;
int cnt,head[MAXN],to[MAXN],Next[MAXN];
int tag[MAXN];
int tim,dfn[MAXN];
int x[MAXN];
ll c[MAXN];
ll ans[MAXM];
querys q[MAXM];

inline void Add_Edge(reg int u,reg int v){
	Next[++cnt]=head[u];
	to[cnt]=v;
	head[u]=cnt;
	return;
}

inline bool cmp(reg int a,reg int b){
	return x[a]<x[b];
}

vector<int> ins[MAXN],out[MAXN];

inline void dfs(reg int u){
	dfn[u]=++tim;
	if(tag[u]>0)
		ins[tag[u]].push_back(tim);
	else
		out[abs(tag[u])].push_back(tim-1);
	for(reg int i=head[u];i;i=Next[i]){
		reg int v=to[i];
		dfs(v);
	}
	if(tag[u]>0)
		out[tag[u]].push_back(tim);
	else
		ins[abs(tag[u])].push_back(tim+1);
	return;
}

inline double getX(reg int id){
	return x[id];
}

inline double getY(reg int id){
	return 1.0*x[id]*x[id]+c[id];
}

inline double slope(reg int x,reg int y){
	return (getY(x)-getY(y))/(getX(x)-getX(y));
}

namespace SegmentTree{
	#define lson ( (k) << 1 )
	#define rson ( (k) << 1 | 1 )
	#define mid ( ( (l) + (r) ) >> 1 )
	struct Node{
		vector<int> V;
		#define V(x) unit[(x)].V
	};
	Node unit[MAXN<<2];
	inline void update(reg int k,reg int l,reg int r,reg int L,reg int R,reg int id){
		if(L<=l&&r<=R){
			if(!V(k).empty()&&x[V(k).back()]==x[id]){
				if(c[V(k).back()]<=c[id])
					return;
				V(k).pop_back();
			}
			while(V(k).size()>1&&slope(V(k).back(),id)<slope(V(k).back(),V(k)[V(k).size()-2]))
				V(k).pop_back();
			V(k).push_back(id);
			return;
		}
		if(L<=mid)
			update(lson,l,mid,L,R,id);
		if(R>mid)
			update(rson,mid+1,r,L,R,id);
		return;
	}
	inline ll query(reg int k,reg int l,reg int r,reg int pos,reg int x0,reg ll Min){
		while(V(k).size()>1&&slope(V(k).front(),V(k)[1])<=2.0*x0)
			V(k).erase(V(k).begin());
		if(!V(k).empty())
			Min=min(Min,1ll*(x0-x[V(k).front()])*(x0-x[V(k).front()])+c[V(k).front()]);
		if(l==r)
			return Min;
		if(pos<=mid)
			return query(lson,l,mid,pos,x0,Min);
		else
			return query(rson,mid+1,r,pos,x0,Min);
	}
}

int main(void){
	n=read(),m=read(),c[0]=readll();
	for(reg int i=1;i<n;++i){
		static int opt,fr,id;
		opt=read();
		switch(opt){
			case 0:{
				fr=read(),id=read();
				x[id]=read(),read(),read(),c[id]=readll();
				tag[i]=id;
				Add_Edge(fr,i);
				break;
			}
			case 1:{
				fr=read(),id=read();
				tag[i]=-id;
				Add_Edge(fr,i);
				break;
			}
		}
	}
	dfs(0);
	static int a[MAXN];
	for(reg int i=1;i<=n;++i)
		a[i]=i;
	sort(a+1,a+n+1,cmp);
	SegmentTree::update(1,1,n,1,n,0);
	for(reg int i=1;i<=n;++i){
		reg int id=a[i];
		for(reg int j=0,siz=ins[id].size();j<siz;++j){
			reg int L=ins[id][j],R=out[id][j];
			if(L<=R)
				SegmentTree::update(1,1,n,L,R,id);
		}
	}
	for(reg int i=1;i<=m;++i)
		q[i].id=i,q[i].s=read(),q[i].x0=read();
	sort(q+1,q+m+1);
	for(reg int i=1;i<=m;++i)
		ans[q[i].id]=SegmentTree::query(1,1,n,dfn[q[i].s],q[i].x0,inf);
	for(reg int i=1;i<=m;++i)
		writeln(ans[i]);
	flush();
	return 0;
}