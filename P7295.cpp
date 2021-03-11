#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar()(p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
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

inline void read(reg char *s){
	*s=getchar();
	while(!isalpha(*s))*s=getchar();
	while(isalpha(*s))*(++s)=getchar();
	*s='\0';
	return;
}

inline void writeln(reg int x){
	static char buf[32];
	reg int p=-1;
	if(x==0) putchar('0');
	else while(x) buf[++p]=(x%10)^'0',x/=10;
	while(~p) putchar(buf[p--]);
	putchar('\n');
	return;
}

const int MAXN=1000+10;

int n,m,q;
char M[MAXN][MAXN];
int sumCntE[2][MAXN][MAXN],sumF[MAXN][MAXN];
int id[MAXN][MAXN],tot;
pair<int,int> pos[MAXN*MAXN];
int vis[MAXN*MAXN];

inline bool check(reg int x1,reg int y1,reg int x2,reg int y2){
	if(x1==x2)
		return M[x1][max(y1,y2)]!=M[x1+1][max(y1,y2)];
	else
		return M[max(x1,x2)][y1]!=M[max(x1,x2)][y1+1];
}

inline void bfs(reg int sx,reg int sy){
	queue<pair<int,int>/**/> Q;
	id[sx][sy]=++tot,++sumF[sx][sy],pos[tot]=make_pair(sx,sy),Q.push(make_pair(sx,sy));
	reg bool flag=false;
	while(!Q.empty()){
		reg int x=Q.front().first,y=Q.front().second;
		Q.pop();
		const int dx[4]={-1,0,0,1};
		const int dy[4]={0,-1,1,0};
		for(reg int i=0;i<4;++i){
			reg int fx=x+dx[i],fy=y+dy[i];
			if(check(x,y,fx,fy)){
				if(fx<1||fx>n||fy<1||fy>m)
					flag=true;
				else if(!id[fx][fy])
					id[fx][fy]=tot,Q.push(make_pair(fx,fy));
			}
		}
	}
	if(flag)
		--sumF[sx][sy],pos[tot]=make_pair(0,0);
	return;
}

inline bool in(reg int p,reg int x1,reg int y1,reg int x2,reg int y2){
	return x1<=pos[p].first&&pos[p].first<=x2&&y1<=pos[p].second&&pos[p].second<=y2;
}

inline int getSum(reg int sum[][MAXN],reg int x1,reg int y1,reg int x2,reg int y2){
	return sum[x2][y2]-sum[x1-1][y2]-sum[x2][y1-1]+sum[x1-1][y1-1];
}

int main(void){
	n=read(),m=read(),q=read();
	for(int i=1;i<=n;++i)
		read(M[i]+1);
	for(int i=1;i<=n;++i)
		for(int j=1;j<=m;++j){
			if(i<n&&M[i][j]==M[i+1][j])
				sumCntE[0][i][j]=1;
			if(j<m&&M[i][j]==M[i][j+1])
				sumCntE[1][i][j]=1;
		}
	for(reg int i=1;i<=n;++i)
		for(reg int j=1;j<=m;++j)
			for(reg int k=0;k<2;++k)
				sumCntE[k][i][j]+=sumCntE[k][i-1][j]+sumCntE[k][i][j-1]-sumCntE[k][i-1][j-1];
	for(reg int i=1;i<=n;++i)
		for(reg int j=1;j<=m;++j)
			if(!id[i][j])
				bfs(i,j);
	for(reg int i=1;i<=n;++i)
		for(reg int j=1;j<=m;++j)
			sumF[i][j]+=sumF[i-1][j]+sumF[i][j-1]-sumF[i-1][j-1];
	while(q--){
		int x1=read(),y1=read(),x2=read(),y2=read();
		reg int V=(x2-x1+1)*(y2-y1+1);
		reg int E=getSum(sumCntE[0],x1,y1,x2-1,y2)+getSum(sumCntE[1],x1,y1,x2,y2-1);
		reg int F=getSum(sumF,x1,y1,x2-1,y2-1);
		for(reg int i=x1;i<=x2;++i)
			if(!vis[id[i][y1-1]]&&in(id[i][y1-1],x1,y1,x2-1,y2-1))
				vis[id[i][y1-1]]=true,--F;
		for(reg int i=x1;i<=x2;++i)
			if(!vis[id[i][y2]]&&in(id[i][y2],x1,y1,x2-1,y2-1))
				vis[id[i][y2]]=true,--F;
		for(reg int i=y1;i<=y2;++i)
			if(!vis[id[x1-1][i]]&&in(id[x1-1][i],x1,y1,x2-1,y2-1))
				vis[id[x1-1][i]]=true,--F;
		for(reg int i=y1;i<= y2;++i)
			if(!vis[id[x2][i]]&&in(id[x2][i],x1,y1,x2-1,y2-1))
				vis[id[x2][i]]=true,--F;
		writeln(V-E+F);
		for(reg int i=x1;i<=x2;++i)
			vis[id[i][y1-1]]=vis[id[i][y2]]=false;
		for(reg int i=y1;i<=y2;++i)
			vis[id[x1-1][i]]=vis[id[x2][i]]=false;
	}
	flush();
	return 0;
}