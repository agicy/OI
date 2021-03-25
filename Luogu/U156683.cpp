#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
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

const int MAXN=1e3+5;
const int MAXM=1e3+5;

int n,m;
char dis[MAXN][MAXM];
queue<pair<int,int>/**/> Q;

int main(void){
	n=read(),m=read();
	for(reg int i=1;i<=n;++i)
		for(reg int j=1;j<=m;++j){
			static char ch;
			do
				ch=getchar();
			while(ch!='B'&&ch!='.');
			if(ch=='.')
				dis[i][j]=15,Q.push(make_pair(i,j));
		}
	while(!Q.empty()){
		static pair<int,int> p;
		p=Q.front();
		Q.pop();
		reg int x=p.first,y=p.second;
		const int dx[]={-1,0,0,1};
		const int dy[]={0,-1,1,0};
		if(dis[x][y]>8)
			for(reg int i=0;i<4;++i){
				int fx=x+dx[i],fy=y+dy[i];
				if(1<=fx&&fx<=n&&1<=fy&&fy<=m&&!dis[fx][fy]){
					dis[fx][fy]=dis[x][y]-1;
					Q.push(make_pair(fx,fy));
				}
			}
	}
	for(reg int i=1;i<=n;++i,putchar('\n'))
		for(reg int j=1;j<=m;++j)
			if(dis[i][j])
				putchar('O');
			else
				putchar('X');
	flush();
	return 0;
}