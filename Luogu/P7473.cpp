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
	while(!isdigit(ch)) ch=getchar();
	while(isdigit(ch)) res=10*res+(ch^'0'),ch=getchar();
	return res;
}

inline void writeln(reg int x){
	static char buf[32];
	reg int p=-1;
	if(x<0) x=-x,putchar('-');
	if(x==0) putchar('0');
	else while(x) buf[++p]=(x%10)^'0',x/=10;
	while(~p) putchar(buf[p--]);
	putchar('\n');
	return;
}

inline int min(reg int a,reg int b){
	return a<b?a:b;
}

const int inf=0x3f3f3f3f;
const int MAXN=250+5;
const int MAXM=250+5;
const int MAXS=4*(MAXN+MAXM);

struct Node{
	int x,y;
	inline Node(reg int x=0,reg int y=0):x(x),y(y){
		return;
	}
};

int n,m,q;
bool M[MAXN][MAXN];
int id[MAXN][MAXN];
int S[MAXN][MAXN][4];
vector<int> G[MAXS][4];
int dis[MAXS][MAXS];
Node Q[MAXS*MAXS];

inline bool check(reg int i,reg int j){
	if(M[i-1][j]||M[i+1][j]||M[i][j-1]||M[i][j+1])
		return true;
	else
		return false;
}

inline int getAns(reg int a,reg int b,reg int c,reg int d){
	return min(min(dis[S[a][b][0]][S[c][d][0]],dis[S[a][b][1]][S[c][d][1]]),min(dis[S[a][b][2]][S[c][d][2]],dis[S[a][b][3]][S[c][d][3]]));
}

int main(void){
	n=read(),m=read(),q=read();
	for(reg int i=1;i<=m;++i){
		static int x,y;
		x=read(),y=read();
		M[x][y]=true;
	}
	for(reg int i=1;i<=n;++i)
		M[0][i]=M[n+1][i]=M[i][0]=M[i][n+1]=true;
	reg int tot=0;
	for(reg int i=1;i<=n;++i)
		for(reg int j=1;j<=n;++j)
			if(!M[i][j]&&check(i,j))
				id[i][j]=++tot;
	for(reg int i=1;i<=n;++i)
		for(reg int j=1;j<=n;++j){
			if(M[i][j-1])
				S[i][j][0]=id[i][j];
			else
				S[i][j][0]=S[i][j-1][0];
			if(M[i-1][j])
				S[i][j][1]=id[i][j];
			else
				S[i][j][1]=S[i-1][j][1];
		}
	for(reg int i=n;i>=1;--i)
		for(reg int j=n;j>=1;--j){
			if(M[i][j+1])
				S[i][j][2]=id[i][j];
			else
				S[i][j][2]=S[i][j+1][2];
			if(M[i+1][j])
				S[i][j][3]=id[i][j];
			else
				S[i][j][3]=S[i+1][j][3];
		}
	for(reg int i=1;i<=n;++i)
		for(reg int j=1;j<=n;++j)
			if(id[i][j])
				for(reg int k=0;k<4;++k)
					G[S[i][j][k]][k].push_back(id[i][j]);
	memset(dis,0x3f,sizeof(dis));
	reg int _head=0,_tail=0;
	for(reg int i=1;i<=tot;++i)
		dis[i][i]=1,Q[_tail++]=Node(i,i);
	while(_head<_tail){
		static Node s;
		s=Q[_head++];
		reg int x=s.x,y=s.y;
		for(reg int k=0;k<4;++k)
			for(int fx:G[x][k])
				for(int fy:G[y][k])
					if(dis[fx][fy]==inf){
						dis[fx][fy]=dis[x][y]+1;
						Q[_tail++]=Node(fx,fy);
					}
	}
	while(q--){
		static int a,b,c,d;
		a=read(),b=read(),c=read(),d=read();
		if(a==c&&b==d)
			writeln(0);
		else{
			reg int ans=getAns(a,b,c,d);
			if(ans>=inf)
				writeln(-1);
			else
				writeln(ans);
		}
	}
	flush();
	return 0;
}