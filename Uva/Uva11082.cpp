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
	reg bool f=false;
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))f|=(ch=='-'),ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return f?-res:res;
}

inline void writeln(reg int x){
	static char buf[32];
	reg int p=-1;
	if(x<0) x=-x,putchar('-');
	if(!x) putchar('0');
	else while(x) buf[++p]=(x%10)^'0',x/=10;
	while(~p) putchar(buf[p--]);
	putchar('\n');
	return;
}

const int MAXR=20+5;
const int MAXC=20+5;
const int MAXV=MAXR*MAXC;
const int MAXE=(MAXR*MAXC+MAXR+MAXC)*2;
const int inf=0x3f3f3f3f;

int cnt=1,head[MAXV],to[MAXE],w[MAXE],Next[MAXE];

inline void Add_Edge(reg int u,reg int v,reg int len){
	Next[++cnt]=head[u];
	to[cnt]=v,w[cnt]=len;
	head[u]=cnt;
	return;
}

inline int Add_Tube(reg int u,reg int v,reg int len){
	Add_Edge(u,v,len);
	Add_Edge(v,u,0);
	return cnt;
}

int dep[MAXV];
int cur[MAXV];
int Q[MAXV];

inline bool bfs(reg int s,reg int t){
	reg int _head=0,_tail=0;
	fill(dep+s,dep+t+1,-1);
	dep[s]=0,Q[_tail++]=s;
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
	while(bfs(s,t))
		res+=dfs(s,t,inf);
	return res;
}

int r,c;
int row[MAXR],col[MAXC];
int ans[MAXR][MAXC];

int main(void){
	reg int t=read();
	reg int Case=0;
	while(t--){
		if(t)
			putchar('\n');
		r=read(),c=read();
		for(reg int i=1;i<=r;++i)
			row[i]=read();
		for(reg int i=1;i<=c;++i)
			col[i]=read();
		for(reg int i=r;i>=1;--i)
			row[i]-=row[i-1];
		for(reg int i=c;i>=1;--i)
			col[i]-=col[i-1];
		reg int s=0,t=r+c+1;
		cnt=1,fill(head+s,head+t+1,0);
		for(reg int i=1;i<=r;++i)
			for(reg int j=1;j<=c;++j)
				ans[i][j]=Add_Tube(i,j+r,19);
		for(reg int i=1;i<=r;++i)
			Add_Tube(s,i,row[i]-c);
		for(reg int i=1;i<=c;++i)
			Add_Tube(i+r,t,col[i]-r);
		dinic(s,t);
		printf("Matrix %d\n",++Case);
		for(reg int i=1;i<=r;++i)
			for(reg int j=1;j<=c;++j)
				printf("%d%c",w[ans[i][j]]+1,j==c?'\n':' ');
	}
	return 0;
}