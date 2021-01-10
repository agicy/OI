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

const int MAXN=2e5+5;

int n;
int x[MAXN],y[MAXN];
int sumc[MAXN],sumr[MAXN];

namespace Subtask1{
	const int MAXN=20+5;
	int cntc[MAXN],cntr[MAXN];
	inline void Solve(void){
		reg int U=(1<<n)-1;
		for(reg int i=0;i<=U;++i){
			memset(cntc,0,sizeof(cntc));
			memset(cntr,0,sizeof(cntr));
			for(reg int j=1;j<=n;++j){
				if((i>>(j-1))&1){
					++cntc[x[j]],++cntr[y[j]];
				}
			}
			reg bool f=true;
			for(reg int i=1;i<=n;++i)
				if(sumc[i]&1)
					f&=(sumc[i]/2==cntc[i]||sumc[i]/2+1==cntc[i]);
				else
					f&=(sumc[i]/2==cntc[i]);
			for(reg int i=1;i<=n;++i)
				if(sumr[i]&1)
					f&=(sumr[i]/2==cntr[i]||sumr[i]/2+1==cntr[i]);
				else
					f&=(sumr[i]/2==cntr[i]);
			if(f){
				puts("Yes");
				for(reg int j=1;j<=n;++j)
					if((i>>(j-1))&1)
						putchar('b');
					else
						putchar('w');
				putchar('\n');
				return;
			}
		}
		puts("No");
		return;
	}
}

namespace Subtask2{
	const int MAXV=2*MAXN;
	const int MAXE=2*(MAXN*2+MAXN);
	const int inf=0x3f3f3f3f;
	int cnt=1,head[MAXV],to[MAXE],w[MAXE],Next[MAXE];
	inline void Add_Edge(reg int u,reg int v,reg int len){
		Next[++cnt]=head[u];
		to[cnt]=v;
		w[cnt]=len;
		head[u]=cnt;
		return;
	}
	inline int Add_Tube(reg int u,reg int v,reg int len){
		Add_Edge(u,v,len);
		Add_Edge(v,u,0);
		return cnt-1;
	}
	int dep[MAXV];
	int Q[MAXV];
	inline bool bfs(reg int s,reg int t){
		reg int head_=0,tail_=0;
		memset(dep,-1,sizeof(dep));
		dep[s]=1,Q[tail_++]=s;
		while(head_<tail_){
			reg int u=Q[head_++];
			for(reg int i=head[u];i;i=Next[i]){
				reg int v=to[i];
				if(dep[v]==-1&&w[i]){
					dep[v]=dep[u]+1;
					Q[tail_++]=v;
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
	int id[MAXN];
	inline void Solve(void){
		reg int s=0,t=2*n+1;
		for(reg int i=1;i<=n;++i){
			Add_Tube(s,i,sumc[i]>>1);
			Add_Tube(i+n,t,sumr[i]>>1);
			id[i]=Add_Tube(x[i],y[i]+n,1);
		}
		reg int flow=dinic(s,t);
		if(flow==n/2){
			puts("Yes");
			for(reg int i=1;i<=n;++i)
				if(!w[id[i]])
					putchar('w');
				else
					putchar('b');
			putchar('\n');
		}
		else
			puts("No");
		return;
	}
}

namespace Subtask3{
	const int MAXV=MAXN*2;
	const int MAXE=2*(9*MAXN+1);
	const int inf=0x3f3f3f3f;
	namespace Network{
		int cnt=1,head[MAXV],to[MAXE],w[MAXE],Next[MAXE];
		inline void Add_Edge(reg int u,reg int v,reg int len){
			Next[++cnt]=head[u];
			to[cnt]=v;
			w[cnt]=len;
			head[u]=cnt;
			return;
		}
		inline int Add_Tube(reg int u,reg int v,reg int len){
			Add_Edge(u,v,len);
			Add_Edge(v,u,0);
			return cnt-1;
		}
		int dep[MAXV];
		int Q[MAXV];
		inline bool bfs(reg int s,reg int t){
			reg int head_=0,tail_=0;
			memset(dep,-1,sizeof(dep));
			dep[s]=1,Q[tail_++]=s;
			while(head_<tail_){
				reg int u=Q[head_++];
				for(reg int i=head[u];i;i=Next[i]){
					reg int v=to[i];
					if(dep[v]==-1&&w[i]){
						dep[v]=dep[u]+1;
						Q[tail_++]=v;
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
	}
	int id[MAXN];
	inline void Solve(void){
		reg int s=0,t=2*n+1;
		reg int superS=2*n+2,superT=2*n+3;
		Network::Add_Tube(t,s,inf);
		reg int sum=0;
		for(reg int i=1;i<=n;++i){
			if(true){
				reg int l=sumc[i]/2,r=(sumc[i]+1)/2;
				sum+=l;
				Network::Add_Tube(superS,i,l);
				Network::Add_Tube(s,superT,l);
				Network::Add_Tube(s,i,r-l);
			}
			if(true){
				reg int l=sumr[i]/2,r=(sumr[i]+1)/2;
				sum+=l;
				Network::Add_Tube(superS,t,l);
				Network::Add_Tube(i+n,superT,l);
				Network::Add_Tube(i+n,t,r-l);
			}
			if(true){
				reg int l=0,r=1;
				sum+=l;
				Network::Add_Tube(superS,y[i]+n,l);
				Network::Add_Tube(x[i],superT,l);
				id[i]=Network::Add_Tube(x[i],y[i]+n,r-l);
			}
		}
		reg int flow=Network::dinic(superS,superT);
		if(flow!=sum){
			puts("No");
			return;
		}
		puts("Yes");
		for(reg int i=1;i<=n;++i)
			if(!Network::w[id[i]])
				putchar('b');
			else
				putchar('w');
		putchar('\n');
		return;
	}
}

int main(void){
	n=read();
	for(reg int i=1;i<=n;++i){
		x[i]=read(),y[i]=read();
		++sumc[x[i]],++sumr[y[i]];
	}
	reg bool subtask2Flag=true;
	for(reg int i=1;i<=n;++i)
		if((sumr[i]&1)|(sumc[i]&1)){
			subtask2Flag=false;
			break;
		}
	if(n<=20)
		Subtask1::Solve();
	else if(subtask2Flag)
		Subtask2::Solve();
	else
		Subtask3::Solve();
	return 0;
}