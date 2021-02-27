#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar()(p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return res;
}

const int MAXN=1e5+5;
const int MAXM=1e5+5;
const int inf=0x3f3f3f3f;

int n,m;
int S,T;

int cnt,head[MAXN],to[MAXM<<1],w[MAXM<<1],Next[MAXM<<1];

inline void Add_Edge(reg int u,reg int v,reg int len){
	Next[++cnt]=head[u];
	to[cnt]=v,w[cnt]=len;
	head[u]=cnt;
	return;
}

bool vis[MAXN];
int pre[MAXN],dep[MAXN],dig[MAXN];
int Q[MAXN];

inline void bfs(void){
	reg int _head,_tail;
	memset(pre,-1,sizeof(pre));
	for(reg int i=0;i<n;++i)
		dep[i]=-1;
	_head=0,_tail=0;
	vis[T]=true,Q[_tail++]=T;
	while(_head<_tail){
		reg int u=Q[_head++];
		for(reg int i=head[u];i;i=Next[i]){
			reg int v=to[i];
			if(!w[i]&&!vis[v]){
				vis[v]=true;
				pre[v]=u;
				Q[_tail++]=v;
			}
		}
	}
	_head=0,_tail=0;
	dep[S]=0,Q[_tail++]=S;
	reg int sum=0;
	while(_head<_tail){
		reg int u=Q[_head++];
		if(sum&&dep[u]==sum)
			continue;
		for(reg int i=head[u];i;i=Next[i]){
			reg int v=to[i];
			if(dep[v]==-1){
				dep[v]=dep[u]+1;
				Q[_tail++]=v;
				if(!sum&&vis[v])
					sum=dep[v];
			}
		}
	}
	return;
}

inline void solve(void){
	memset(dig,-1,sizeof(dig));
	reg int _head=0,_tail=0;
	for(reg int i=0;i<n;++i)
		if(vis[i]&&dep[i]!=-1)
			Q[_tail++]=i;
	reg int las=0,Min=inf;
	while(_head<_tail){
		reg int u=Q[_head++];
		if(dep[u]==dep[S])
			return;
		for(reg int i=head[u];i;i=Next[i]){
			reg int v=to[i];
			if(dep[v]==dep[u]-1)
				Min=min(Min,w[i]);
		}
		if(_head>=_tail){
			for(reg int i=las;i<_tail;++i){
				reg int u=Q[i];
				for(reg int i=head[u];i;i=Next[i]){
					reg int v=to[i];
					if(dep[v]==dep[u]-1&&Min==w[i])
						Q[_tail++]=v,pre[v]=u,dig[v]=Min;
				}
			}
			las=_head,Min=inf;
		}
	}
	return;
}

int top,p[MAXN];
int ans,Ans[MAXN];

inline void print(reg int u){
	p[++top]=u;
	if(~pre[u]) print(pre[u]);
	if(~dig[u]) Ans[++ans]=dig[u];
	return;
}

int main(void){
	n=read(),m=read();
	for(reg int i=1;i<=m;++i){
		static int x,y,c;
		x=read(),y=read(),c=read();
		Add_Edge(x,y,c),Add_Edge(y,x,c);
	}
	S=0,T=n-1;
	bfs(),solve();
	print(S);
	if(!ans)
		puts("0");
	else{
		for(reg int i=1;i<=ans;++i)
			printf("%d",Ans[i]);
		puts("");
	}
	printf("%d\n",top);
	for(reg int i=1;i<=top;++i)
		printf("%d%c",p[i],i==top?'\n':' ');
	return 0;
}