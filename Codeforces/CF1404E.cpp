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

inline void read(reg char *s){
	*s=getchar();
	while(*s!='#'&&*s!='.')*s=getchar();
	while(*s=='#'||*s=='.')*(++s)=getchar();
	*s='\0';
	return;
}

const int MAXN=200+5;
const int MAXM=200+5;
const int MAXV=MAXN*MAXM*2;
const int MAXE=(MAXN*MAXM*12)*2;
const int inf=0x3f3f3f3f;

int cnt=1,head[MAXV],to[MAXE],w[MAXE],Next[MAXE];

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
	reg int _head=0,_tail=0;
	memset(dep,-1,sizeof(dep));
	dep[s]=1,Q[_tail++]=s;
	while(_head<_tail){
		reg int u=Q[_head++];
		for(reg int i=head[u];i;i=Next[i]){
			int v=to[i];
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

int n,m;
char M[MAXN][MAXM];
bool vis[MAXN*MAXM*2];

int main(void){
	n=read(),m=read();
	for(reg int i=1;i<=n;++i)
		read(M[i]+1);
	reg int s=0,t=n*m*2+1;
	reg int sum=0,cnt=0;
	for(reg int i=1;i<=n;++i)
		for(reg int j=1;j<=m;++j)
			if(M[i][j]=='#'){
				++sum;
				reg int up=(i-1)*m+j,rg=up+n*m;
				reg int dn=i*m+j,le=rg-1;
				if(M[i-1][j]=='#'&&!vis[up])
					++cnt,vis[up]=true,Add_Tube(s,up,1),Add_Tube(up,s,0);
				if(M[i][j-1]=='#'&&!vis[le])
					++cnt,vis[le]=true,Add_Tube(le,t,1),Add_Tube(t,le,0);
				if(M[i-1][j]=='#'){
					if(M[i][j+1]=='#')
						Add_Tube(up,rg,1),Add_Tube(rg,up,0);
					if(M[i][j-1]=='#')
						Add_Tube(up,le,1),Add_Tube(le,up,0);
				}
				if(M[i+1][j]=='#'){
					if(M[i][j+1]=='#')
						Add_Tube(dn,rg,1),Add_Tube(rg,dn,0);
					if(M[i][j-1]=='#')
						Add_Tube(dn,le,1),Add_Tube(le,dn,0);
				}
			}
	printf("%d\n",sum-(cnt-dinic(s,t)));
	return 0;
}