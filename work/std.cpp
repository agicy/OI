#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
static char buf[1<<21],*p1=buf,*p2=buf;
inline int read(void){
	reg bool f=false;
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))f|=(ch=='-'),ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return f?-res:res;
}

const int MAXN=2e3+5;
const int MAXM=2e3+5;

int n,m;
int a[MAXN],b[MAXM];
int M[MAXN][MAXM];

struct Node{
	int x,y;
	inline Node(reg int x=0,reg int y=0):x(x),y(y){
		return;
	}
};

bool vis[MAXN][MAXM];

inline bool bfs(reg int s,reg int t){
	reg int _head=0,_tail=0;
	for(reg int i=1;i<=n;++i)
		for(reg int j=1;j<=m;++j)
			vis[i][j]=false;
	static Node Q[MAXN*MAXM];
	if(M[s][1]<0)
		return false;
	vis[s][1]=true,Q[_tail++]=Node(s,1);
	while(_head<_tail){
		static Node s;
		s=Q[_head++];
		reg int x=s.x,y=s.y;
		if(x==t&&y==m)
			return true;
		const int dx[]={0,1};
		const int dy[]={1,0};
		for(reg int i=0;i<2;++i){
			reg int fx=x+dx[i],fy=y+dy[i];
			if(1<=fx&&fx<=n&&1<=fy&&fy<=m&&M[fx][fy]>=0&&!vis[fx][fy]){
				vis[fx][fy]=true;
				Q[_tail++]=Node(fx,fy);
			}
		}
	}
	return false;
}

int main(void){
	n=read(),m=read();
	for(reg int i=1;i<=n;++i)
		a[i]=read();
	for(reg int j=1;j<=m;++j)
		b[j]=read();
	for(reg int i=1;i<=n;++i)
		for(reg int j=1;j<=m;++j)
			M[i][j]=a[i]+b[j];
	reg int ans=0;
	for(reg int S=1;S<=n;++S)
		for(reg int T=S;T<=n;++T)
			if(bfs(S,T))
				++ans;
	printf("%d\n",ans);
	fprintf(stderr,"%.3lf s\n",1.0*clock()/CLOCKS_PER_SEC);
	return 0;
}