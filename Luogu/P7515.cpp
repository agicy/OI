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
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return res;
}

inline void write(reg int x){
	static char buf[32];
	reg int p=-1;
	if(x==0) putchar('0');
	else while(x) buf[++p]=(x%10)^'0',x/=10;
	while(~p) putchar(buf[p--]);
	return;
}

const int MAXN=300+5;
const int MAXM=300+5;
const int LIM=1e6;
const ll inf=0x3f3f3f3f3f3f3f3f;

struct Edge{
	int v,w;
	inline Edge(reg int v=0,reg int w=0):v(v),w(w){
		return;
	}
};

int n,m;
int b[MAXN][MAXM];
int a[MAXN][MAXM];
vector<Edge> G[MAXN+MAXM];
bool inque[MAXN+MAXM];
int in[MAXN+MAXM];
ll dis[MAXN+MAXM];

int main(void){
	reg int t=read();
	while(t--){
		n=read(),m=read();
		for(reg int i=1;i<n;++i)
			for(reg int j=1;j<m;++j)
				b[i][j]=read();
		for(reg int i=2;i<=n;++i)
			for(reg int j=2;j<=m;++j)
				a[i][j]=b[i-1][j-1]-a[i-1][j-1]-a[i-1][j]-a[i][j-1];
		for(reg int i=1;i<=n+m;++i)
			G[i].clear();
		for(reg int i=1;i<=n;++i)
			for(reg int j=1;j<=m;++j){
				reg int Max=LIM-a[i][j],Min=-a[i][j];
				if((i+j)&1)
					G[j+n].push_back(Edge(i,-Min)),G[i].push_back(Edge(j+n,Max));
				else
					G[j+n].push_back(Edge(i,Max)),G[i].push_back(Edge(j+n,-Min));
			}
		fill(inque+1,inque+n+m+1,false);
		fill(in+1,in+n+m+1,0);
		fill(dis+1,dis+n+m+1,inf);
		deque<int> Q;
		dis[1]=0,Q.push_back(1);
		reg bool flag=true;
		while(!Q.empty()&&flag){
			reg int u=Q.front();
			Q.pop_front();
			inque[u]=false;
			for(Edge e:G[u]){
				if(dis[e.v]>dis[u]+e.w){
					dis[e.v]=dis[u]+e.w;
					if(!inque[e.v]){
						inque[e.v]=true;
						if(++in[e.v]>=n+m){
							flag=false;
							break;
						}
						if(!Q.empty()&&dis[e.v]<=dis[Q.front()])
							Q.push_front(e.v);
						else
							Q.push_back(e.v);
					}
				}
			}
		}
		if(!flag)
			putchar('N'),putchar('O'),putchar('\n');
		else{
			putchar('Y'),putchar('E'),putchar('S'),putchar('\n');
			for(reg int i=1;i<=n;++i)
				for(reg int j=1;j<=m;++j){
					if((i+j)&1)
						write(a[i][j]-dis[i]+dis[j+n]);
					else
						write(a[i][j]+dis[i]-dis[j+n]);
					putchar(j==m?'\n':' ');
				}
		}
	}
	flush();
	return 0;
}