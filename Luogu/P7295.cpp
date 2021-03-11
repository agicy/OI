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
	while(!isalpha(*s))*s=getchar();
	while(isalpha(*s))*(++s)=getchar();
	*s='\0';
	return;
}

const int MAXN=1e3+5;
const int MAXM=1e3+5;

int n,m,q;
char M[MAXN][MAXM];
int sumCntE[MAXN][MAXM];
int sumCntF[MAXN][MAXM];

struct Node{
	int x,y;
	inline Node(reg int x=0,reg int y=0):x(x),y(y){
		return;
	}
};

bool vis[MAXN][MAXM];
int id[MAXN][MAXM];
Node pos[MAXN*MAXM];

inline Node bfs(const Node& s,reg int Id){
	reg int _head=0,_tail=0;
	static Node Q[MAXN*MAXM];
	vis[s.x][s.y]=true,id[s.x][s.y]=Id,Q[_tail++]=s;
	while(_head<_tail){
		static Node p;
		p=Q[_head++];
		reg int x=p.x,y=p.y;
		const int dx[]={-1,0,0,1};
		const int dy[]={0,-1,1,0};
		for(reg int i=0;i<4;++i){
			reg int fx=x+dx[i],fy=y+dy[i];
			if(1<=fx&&fx<=n&&1<=fy&&fy<=m&&!vis[fx][fy])
				vis[fx][fy]=true,id[fx][fy]=Id,Q[_tail++]=Node(fx,fy);
		}
	}
	return s;
}

int main(void){
	n=read(),m=read(),q=read();
	for(reg int i=1;i<=n;++i)
		read(M[i]+1);
	reg int tot=0;
	for(reg int i=1;i<=n;++i)
		for(reg int j=1;j<=m;++j)
			if(!vis[i][j]){
				++tot;
				pos[tot]=bfs(Node(i,j),tot);
			}
	for(reg int i=1;i<=n;++i)
		for(reg int j=1;j<=m;++j){
			sumCntE[i][j]=sumCntE[i-1][j]+sumCntE[i][j-1]-sumCntE[i-1][j-1]+(M[i][j]==M[i-1][j])+(M[i][j]==M[i][j-1]);
			sumCntF[i][j]+=sumCntF[i-1][j]+sumCntF[i][j-1]-sumCntF[i-1][j-1];
		}
	while(q--){
		static int x1,y1,x2,y2;
		x1=read(),y1=read(),x2=read(),y2=read();
		reg int V=(y1-x1+1)*(x2-y2+1);
		reg int E=(sumCntE[y1][y2]+sumCntE[x1][x2])-(sumCntE[y1][x2]+sumCntE[x1][y2]);
		reg int F=(sumCntF[y1][y2]+sumCntF[x1-1][x2-1])-(sumCntF[y1][x2-1]+sumCntF[x1-1][y2]);
		static bool vis[MAXN*MAXM];
		if(x2>1)
			for(reg int i=x1;i<=y1;++i){
				Node p=pos[id[i][x2-1]];
				if(x1<=p.x&&p.x<=y1&&x2<=p.y&&p.y<=y2&&!vis[id[i][x2-1]])
					vis[id[i][x2-1]]=true,--F;
			}
		if(y2<m)
			for(reg int i=x1;i<=y1;++i){
				Node p=pos[id[i][y2+1]];
				if(x1<=p.x&&p.x<=y1&&x2<=p.y&&p.y<=y2&&!vis[id[i][y2+1]])
					vis[id[i][y2+1]]=true,--F;
			}
		if(x1>1)
			for(reg int i=x2;i<=y2;++i){
				Node p=pos[id[x1-1][i]];
				if(x1<=p.x&&p.x<=y1&&x2<=p.y&&p.y<=y2&&!vis[id[x1-1][i]])
					vis[id[x1-1][i]]=true,--F;
			}
		if(y1<n)
			for(reg int i=x2;i<=y2;++i){
				Node p=pos[id[y1+1][i]];
				if(x1<=p.x&&p.x<=y1&&x2<=p.y&&p.y<=y2&&!vis[id[y1+1][i]])
					vis[id[y1+1][i]]=true,--F;
			}
		printf("%d\n",V+E-F);
	}
	return 0;
}