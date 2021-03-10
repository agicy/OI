#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define int ll
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
const int MAXLOG2N=18+1;
const int MAXM=2e5+5;
const int MAXCNT=2e5+5;
const ll inf=0x3f3f3f3f3f3f3f3f;

int n,m,rt;
int cnt,head[MAXN],to[MAXN<<1],w[MAXN<<1],Next[MAXN<<1];
int a[MAXN];

inline void Add_Edge(reg int u,reg int v,reg int len){
	Next[++cnt]=head[u];
	to[cnt]=v,w[cnt]=len;
	head[u]=cnt;
	return;
}

int fa[MAXN][MAXLOG2N];
int dep[MAXN];
ll dis[MAXN];
int Q[MAXN];

inline void bfs(reg int s){
	reg int _head=0,_tail=0;
	fa[s][0]=s,dep[s]=1,dis[s]=0,Q[_tail++]=s;
	while(_head<_tail){
		reg int u=Q[_head++];
		for(reg int i=1;i<MAXLOG2N;++i)
			fa[u][i]=fa[fa[u][i-1]][i-1];
		for(reg int i=head[u];i;i=Next[i]){
			reg int v=to[i];
			if(!dep[v]){
				fa[v][0]=u;
				dep[v]=dep[u]+1;
				dis[v]=dis[u]+w[i];
				Q[_tail++]=v;
			}
		}
	}
	return;
}

inline int getFa(reg int u,reg int delta){
	assert(1<=u&&u<=n);
	if(!delta)
		return u;
	else if(dep[u]-1<=delta)
		return rt;
	else{
		reg int x=u,tmp=delta;
		while(delta--)
			u=fa[u][0];
		assert(u!=rt);
		assert(dep[x]-dep[u]==tmp);
		return u;
		/*
		for(reg int i=MAXLOG2N-1;i>=0;--i)
			if((delta>>i)&1)
				u=fa[u][i];
		return u;*/
	}
}

int B;
int id[MAXN];
int lef[MAXCNT],rig[MAXCNT];
int MinId[MAXCNT],delta[MAXCNT];

inline void build(reg int id){
	if(delta[id]){
		for(reg int i=lef[id];i<=rig[id];++i){
			a[i]=getFa(a[i],delta[id]);
			assert(1<=a[i]&&a[i]<=n);
		}
		delta[id]=0;
	}
	assert(delta[id]==0);
	MinId[id]=0;
	for(reg int i=lef[id];i<=rig[id];++i)
		if(dis[MinId[id]]>dis[a[i]])
			MinId[id]=a[i];
	return;
}

inline void update(reg int id,reg int l,reg int r){
	assert(l<=r);
	assert(lef[id]<=l);
	assert(r<=rig[id]);
	if(l==lef[id]&&rig[id]==r)
		++delta[id];
	else{
		build(id);
		for(reg int i=l;i<=r;++i)
			a[i]=getFa(a[i],1);
		build(id);
	}
	return;
}

inline ll query(reg int id,reg int l,reg int r){
	assert(l<=r);
	assert(lef[id]<=l);
	assert(r<=rig[id]);
	if(l==lef[id]&&rig[id]==r)
		return dis[getFa(MinId[id],delta[id])];
	else{
		build(id);
		reg ll res=inf;
		for(reg int i=l;i<=r;++i)
			res=min(res,dis[a[i]]);
		return res;
	}
}

signed main(void){
	n=read(),m=read(),rt=read();
	B=sqrt(n);
	for(reg int i=1;i<n;++i){
		static int u,v,w;
		u=read(),v=read(),w=read();
		Add_Edge(u,v,w),Add_Edge(v,u,w);
	}
	bfs(rt);
	dis[0]=inf;
	for(reg int i=1;i<=n;++i)
		a[i]=read();
	reg int Cnt=(n+B-1)/B;
	for(reg int i=1;i<=Cnt;++i){
		lef[i]=(i-1)*B+1,rig[i]=min(i*B,n);
		for(reg int j=lef[i];j<=rig[i];++j)
			id[j]=i;
		delta[i]=0;
		build(i);
	}
	for(reg int i=1;i<=n;++i)
		assert(1<=id[i]&&id[i]<=Cnt);
	assert(lef[1]==1);assert(rig[Cnt]==n);
	for(reg int i=2;i<=Cnt;++i)
		assert(lef[i]==rig[i-1]+1);
	reg int cnt1=0,cnt2=0;
	for(reg int i=1;i<=m;++i){
		static int opt,l,r;
		opt=read(),l=read(),r=read();
		assert(l<=r);
		switch(opt){
			case 1:{
				reg int lefId=id[l],rigId=id[r];
				for(reg int j=lefId;j<=rigId;++j)
					update(j,max(lef[j],l),min(rig[j],r));
				/*
				for(reg int j=l;j<=r;++j)
					a[j]=getFa(a[j],1);*/
				++cnt1;
				break;
			}
			case 2:{
				reg ll ans=inf;
				reg int lefId=id[l],rigId=id[r];
				for(reg int j=lefId;j<=rigId;++j)
					ans=min(ans,query(j,max(lef[j],l),min(rig[j],r)));/*
				for(reg int j=l;j<=r;++j)
					ans=min(ans,dis[a[j]]);*/
				printf("%lld\n",ans);
				writeln(ans);
				++cnt2;
				break;
			}
		}
		printf("opt=%lld l=%lld r=%lld cnt1=%lld cnt2=%lld\n",opt,l,r,cnt1,cnt2);
		if(i==500)
			flush(),exit(0);
	}
	flush();
	return 0;
}