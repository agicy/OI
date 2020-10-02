#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(ch<'0'||'9'<ch)ch=getchar();
	while('0'<=ch&&ch<='9')res=10*res+ch-'0',ch=getchar();
	return res;
}

const int MAXN=500+5;
const int MAXM=500+5;
const int inf=0x3f3f3f3f;

struct Node{
	int l,r;
	inline Node(reg int l=0,reg int r=0):l(l),r(r){
		return;
	}
	inline bool operator<(const Node& a)const{
		return l==a.l?r<a.r:l<a.l;
	}
};

int n,m;
int h[MAXN][MAXM];
bool vis[MAXN][MAXM];
Node L[MAXM];

inline bool check(reg int x,reg int y){
	return 1<=x&&x<=n&&1<=y&&y<=m;
}

queue<pair<int,int>/**/> Q;

inline void bfs(int sx,int sy){
	memset(vis,false,sizeof(vis));
	while(!Q.empty())Q.pop();
	vis[sx][sy]=true,Q.push(make_pair(sx,sy));
	while(!Q.empty()){
		static pair<int,int> p;
		p=Q.front();
		Q.pop();
		reg int x=p.first,y=p.second;
		const int dx[]={-1,0,0,1};
		const int dy[]={0,-1,1,0};
		for(reg int i=0;i<4;++i){
			int fx=x+dx[i],fy=y+dy[i];
			if(check(fx,fy)&&h[x][y]<h[fx][fy]&&!vis[fx][fy]){
				vis[fx][fy]=true;
				Q.push(make_pair(fx,fy));
				if(fx==1)
					L[sy]=Node(min(fy,L[sy].l),max(fy,L[sy].r));
			}
		}
	}
	return;
}

int main(void){
	n=read(),m=read();
	for(reg int i=1;i<=n;++i)
		for(reg int j=1;j<=m;++j)
			h[i][j]=read();
	reg int tot=0;
	for(reg int i=1;i<=m;++i){
		L[i].l=inf;
		bfs(n,i);
		if(L[i].l==inf)
			++tot;
	}
	if(tot)
		if(n!=1)
			printf("0\n%d\n",tot);
		else
			printf("1\n%d\n",tot);
	else{
		reg int ans=0;
		sort(L+1,L+m+1);
		reg int pos=0;
		for(reg int i=1;i<=m;++i){
			if(L[i].l<=pos&&pos<=L[i].r)
				continue;
			++ans;
			pos=L[i].r;
		}
		printf("1\n%d\n",ans);
	}
	return 0;
}