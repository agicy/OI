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
const int MAXM=2e5+5;

inline int max(reg int a,reg int b){
	return a>b?a:b;
}

int n,m;
int a[MAXM],b[MAXM],v[MAXM];
int cnt,head[MAXN],to[MAXN<<1],Next[MAXN<<1];

inline void Add_Edge(reg int u,reg int v){
	Next[++cnt]=head[u];
	to[cnt]=v;
	head[u]=cnt;
	return;
}

int fa[MAXN],dep[MAXN];
int siz[MAXN],son[MAXN];
int tim,lef[MAXN],rig[MAXN];

inline void dfs1(reg int u,reg int father){
	siz[u]=1;
	fa[u]=father;
	dep[u]=dep[father]+1;
	lef[u]=++tim;
	for(reg int i=head[u];i;i=Next[i]){
		reg int v=to[i];
		if(v!=father){
			dfs1(v,u);
			siz[u]+=siz[v];
			if(siz[son[u]]<siz[v])
				son[u]=v;
		}
	}
	rig[u]=tim;
	return;
}

int topf,top[MAXN];

inline void dfs2(reg int u,reg int father,reg int topf){
	top[u]=topf;
	if(!son[u])
		return;
	dfs2(son[u],u,topf);
	for(reg int i=head[u];i;i=Next[i]){
		reg int v=to[i];
		if(v!=father&&v!=son[u])
			dfs2(v,u,v);
	}
	return;
}

inline int LCA(int x,int y){
	while(top[x]!=top[y]){
		if(dep[top[x]]>dep[top[y]])
			swap(x,y);
		y=fa[top[y]];
	}
	return dep[x]<dep[y]?x:y;
}

namespace BIT{
	inline int lowbit(reg int x){
		return x&(-x);
	}
	int n,unit[MAXN];
	inline void Init(reg int s){
		n=s;
		return;
	}
	inline void update(reg int id,reg int val){
		for(reg int i=id;i<=n;i+=lowbit(i))
			unit[i]+=val;
		return;
	}
	inline int query(reg int id){
		reg int res=0;
		for(reg int i=id;i;i^=lowbit(i))
			res+=unit[i];
		return res;
	}
	inline int query(reg int l,reg int r){
		return query(r)-query(l-1);
	}
}

inline void update(reg int x,reg int y,reg int val){
	reg int lca=LCA(x,y);
	BIT::update(lef[x],val),BIT::update(lef[y],val);
	BIT::update(lef[lca],-val);
	if(fa[lca]) BIT::update(lef[fa[lca]],-val);
	return;
}

struct querys{
	int id,opt,x;
};

int ans[MAXM];
querys q[MAXM];

inline void solve(reg int l,reg int r,reg int L,reg int R){
	if(l==r){
		for(reg int i=L;i<=R;++i)
			if(q[i].opt==2)
				ans[q[i].id]=l;
		return;
	}
	reg int mid=(l+r)>>1;
	reg int sum=0,cntl=0,cntr=0;
	static querys ql[MAXM],qr[MAXM];
	for(reg int i=L;i<=R;++i)
		switch(q[i].opt){
			case 0:{
				if(v[q[i].x]<=mid)
					ql[++cntl]=q[i];
				else{
					++sum;
					update(a[q[i].x],b[q[i].x],1);
					qr[++cntr]=q[i];
				}
				break;
			}
			case 1:{
				if(v[q[i].x]<=mid)
					ql[++cntl]=q[i];
				else{
					--sum;
					update(a[q[i].x],b[q[i].x],-1);
					qr[++cntr]=q[i];
				}
				break;
			}
			case 2:{
				if(BIT::query(lef[q[i].x],rig[q[i].x])==sum)
					ql[++cntl]=q[i];
				else
					qr[++cntr]=q[i];
				break;
			}
		}
	for(reg int i=1;i<=cntr;++i)
		if(qr[i].opt!=2)
			update(a[qr[i].x],b[qr[i].x],qr[i].opt?1:-1);
	for(reg int i=1;i<=cntl;++i)
		q[L+i-1]=ql[i];
	for(reg int i=1;i<=cntr;++i)
		q[L+cntl+i-1]=qr[i];
	if(cntl) solve(l,mid,L,L+cntl-1);
	if(cntr) solve(mid+1,r,L+cntl,R);
	return;
}

int main(void){
	n=read(),m=read();
	for(reg int i=1;i<n;++i){
		static int u,v;
		u=read(),v=read();
		Add_Edge(u,v),Add_Edge(v,u);
	}
	dfs1(1,0),dfs2(1,0,1);
	BIT::Init(n);
	reg int Max=0,tot=0;
	for(reg int i=1;i<=m;++i)
		switch(q[i].opt=read()){
			case 0:{
				a[i]=read(),b[i]=read(),v[i]=read();
				q[i].x=i;
				Max=max(Max,v[i]);
				break;
			}
			case 1:{
				q[i].x=read();
				break;
			}
			case 2:{
				q[i].id=++tot;
				q[i].x=read();
				break;
			}
		}
	solve(-1,Max,1,m);
	for(reg int i=1;i<=tot;++i)
		writeln(ans[i]);
	flush();
	return 0;
}