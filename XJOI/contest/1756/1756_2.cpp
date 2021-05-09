#pragma GCC optimize("Ofast")
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

inline void writeln(reg ll x){
	static char buf[32];
	reg int p=-1;
	if(x<0) x=-x,putchar('-');
	if(!x) putchar('0');
	else while(x) buf[++p]=(x%10)^'0',x/=10;
	while(~p) putchar(buf[p--]);
	putchar('\n');
	return;
}

inline void writeln(const char* s){
	while(*s) putchar(*(s++));
	putchar('\n');
	return;
}

const int MAXN=100+5;
const int MAXM=500+5;
const int MAXX=100+5;
const int MAXF=5*100*100*100+100*100*100+100*100+100*100;
const int MAXV=MAXN*2*MAXX;
const int MAXE=(MAXM*MAXX*2*2+MAXN*2+MAXN*MAXX*2)*2;
const int C=MAXF;
const int inf=(C+MAXF)*MAXN;

struct Interval{
	int a,b,c,d,l,r;
};

int n,m;
int id[MAXN][MAXX*2];
Interval a[MAXN];

inline int getVal(reg int id,reg int x){
	return ((a[id].a*x+a[id].b)*x+a[id].c)*x+a[id].d;
}

int cnt=1,head[MAXV],to[MAXE],Next[MAXE];
ll w[MAXE];

inline void Add_Tube(reg int u,reg int v,reg ll len){
	Next[++cnt]=head[u];
	to[cnt]=v,w[cnt]=len;
	head[u]=cnt;

	Next[++cnt]=head[v];
	to[cnt]=u,w[cnt]=0;
	head[v]=cnt;
	return;
}

int dep[MAXV];
int Q[MAXV];
int cur[MAXV];

inline bool bfs(reg int s,reg int t){
	fill(dep,dep+t+1,-1);
	reg int _head=0,_tail=0;
	dep[s]=1,Q[_tail++]=s;
	while(_head<_tail){
		reg int u=Q[_head++];
		cur[u]=head[u];
		for(reg int i=head[u];i;i=Next[i]){
			reg int v=to[i];
			if(dep[v]==-1&&w[i]){
				dep[v]=dep[u]+1;
				Q[_tail++]=v;
			}
		}
	}
	return dep[t]!=-1;
}

inline ll dfs(reg int u,reg int t,reg ll lim){
	if(u==t)
		return lim;
	reg ll flow=0;
	for(reg int &i=cur[u];i;i=Next[i]){
		reg int v=to[i];
		if(dep[v]==dep[u]+1&&w[i]){
			reg ll f=dfs(v,t,min(lim-flow,w[i]));
			if(f){
				flow+=f;
				w[i]-=f,w[i^1]+=f;
				if(flow==lim)
					break;
			}
		}
	}
	return flow;
}

inline ll dinic(reg int s,reg int t){
	reg ll res=0;
	while(bfs(s,t)){
		while(true){
			reg ll tmp=dfs(s,t,0x3f3f3f3f);
			if(!tmp)
				break;
			res+=tmp;
		}
	}
	return res;
}

signed main(void){
	reg int t=read();
	while(t--){
		n=read(),m=read();
		reg int sum=0;
		for(reg int i=1;i<=n;++i){
			a[i].a=read(),a[i].b=read(),a[i].c=read(),a[i].d=read(),a[i].l=read(),a[i].r=read();
			sum+=a[i].r-a[i].l+1;
		}
		reg int tot=0,s=0,t=sum+1;
		for(reg int i=1;i<=n;++i){
			Add_Tube(s,tot+1,inf);
			for(reg int j=a[i].l;j<a[i].r;++j){
				id[i][j-a[i].l]=++tot;
				Add_Tube(tot,tot+1,-getVal(i,j)+C);
			}
			id[i][a[i].r-a[i].l]=++tot;
			Add_Tube(tot,t,-getVal(i,a[i].r)+C);
		}
		for(reg int i=1;i<=m;++i){
			static int u,v,d;
			u=read(),v=read(),d=read();
			for(reg int j=a[u].l;j<=a[u].r;++j)
				if(j-d>a[v].l){
					if(j-d>a[v].r)
						Add_Tube(id[u][j-a[u].l],t,inf);
					else
						Add_Tube(id[u][j-a[u].l],id[v][j-a[v].l-d],inf);
				}
		}
		reg ll res=dinic(s,t)-n*C;
		if(res>=n*C)
			writeln("mei ji ge");
		else
			writeln(-res);
		cnt=1,fill(head+s,head+t+1,0);
	}
	flush();
	return 0;
}