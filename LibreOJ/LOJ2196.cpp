#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return res;
}

inline int max(reg int a,reg int b){
	return a>b?a:b;
}

inline int min(reg int a,reg int b){
	return a<b?a:b;
}

const int MAXN=700+5;
const int MAXV=MAXN*2;
const int MAXE=(MAXN*MAXN/2+MAXN*2)*2;
const int inf=0x3f3f3f3f;

int n;
int a[MAXN],b[MAXN],c[MAXN];
int cnt,head[MAXV],to[MAXE],w[MAXE],Next[MAXE];
int f[MAXN];

inline void Add_Edge(reg int u,reg int v,reg int len){
	Next[++cnt]=head[u];
	to[cnt]=v,w[cnt]=len;
	head[u]=cnt;
	return;
}

inline void Add_Tube(reg int u,reg int v,reg int len){
	Add_Edge(u,v,len);
	Add_Edge(v,u,0);
	return;
}

int dep[MAXV];
int Q[MAXV];

inline bool bfs(reg int s,reg int t){
	memset(dep,-1,sizeof(dep));
	reg int _head=0,_tail=0;
	dep[s]=1,Q[_tail++]=s;
	while(_head<_tail){
		reg int u=Q[_head++];
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

int cur[MAXV];

inline int dfs(reg int u,reg int t,reg int lim){
	if(u==t)
		return lim;
	reg int flow=0;
	for(reg int &i=cur[u];i;i=Next[i]){
		reg int v=to[i];
		if(dep[v]==dep[u]+1&&w[i]){
			reg int f=dfs(v,t,min(lim-flow,w[i]));
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

inline int dinic(reg int s,reg int t){
	reg int res=0;
	while(bfs(s,t)){
		memcpy(cur,head,sizeof(head));
		res+=dfs(s,t,inf);
	}
	return res;
}

int e[MAXN];

inline bool check(reg int p){
	return !(w[e[p]]||bfs(p,p+n));
}

inline bool cmp(reg int a,reg int b){
	return c[a]<c[b]||(c[a]==c[b]&&a<b);
}

int main(void){
	reg int T=read();
	while(T--){
		n=read();
		for(reg int i=1;i<=n;++i)
			a[i]=read();
		for(reg int i=1;i<=n;++i)
			b[i]=read();
		for(reg int i=1;i<=n;++i)
			c[i]=read();
		reg int s=0,t=2*n+1;
		cnt=1,fill(head+s,head+t+1,-1);
		reg int Max=1;
		for(reg int i=1;i<=n;++i){
			f[i]=1;
			for(reg int j=1;j<i;++j)
				if(a[j]<a[i])
					f[i]=max(f[i],f[j]+1);
			Max=max(Max,f[i]);
		}
		for(reg int i=1;i<=n;++i){
			if(f[i]==1)
				Add_Tube(s,i,inf);
			if(f[i]==Max)
				Add_Tube(i+n,t,inf);
			for(reg int j=1;j<i;++j)
				if(a[j]<a[i]&&f[i]==f[j]+1)
					Add_Tube(j+n,i,inf);
			e[i]=cnt+1;
			Add_Tube(i,i+n,b[i]);
		}
		reg int ans1=dinic(s,t),ans2=0;
		static int id[MAXN];
		for(reg int i=1;i<=n;++i)
			id[i]=i;
		sort(id+1,id+n+1,cmp);
		static int ans[MAXN];
		for(reg int i=1;i<=n;++i)
			if(check(id[i])){
				ans[++ans2]=id[i];
				dinic(t,id[i]+n);
				dinic(id[i],s);
				w[e[id[i]]]=w[e[id[i]]^1]=0;
			}
		printf("%d %d\n",ans1,ans2);
		sort(ans+1,ans+ans2+1);
		for(reg int i=1;i<=ans2;++i)
			printf("%d%c",ans[i],i==ans2?'\n':' ');
	}
	return 0;
}