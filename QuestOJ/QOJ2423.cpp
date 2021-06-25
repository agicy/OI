#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
static char buf[1<<21],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch)) ch=getchar();
	while(isdigit(ch)) res=10*res+(ch^'0'),ch=getchar();
	return res;
}

inline void Err(void){
	puts("-1 -1"),exit(0);
	return;
}

inline int min(reg int a,reg int b){
	return a<b?a:b;
}

const int MAXN=200+5;
const int MAXM=200+5;

int n,m,k;
int a[MAXN][MAXM];
int b[MAXN][MAXM];
int q;
bool vis[MAXN][MAXM];

int main(void){
	n=read(),m=read(),k=read();
	for(reg int i=1;i<=n;++i)
		for(reg int j=1;j<=m;++j)
			a[i][j]=read();
	for(reg int i=1;i<=n;++i)
		for(reg int j=1;j<=m;++j)
			b[i][j]=read();
	q=read();
	reg int ans1=k,ans2=0;
	for(reg int i=1;i<=q;++i){
		static int x,y;
		x=read(),y=read();
		if(vis[x][y]||!b[x][y])
			Err();
		vis[x][y]=true;
		if(a[x][y]>0){
			ans1+=a[x][y];
			ans1=min(ans1,k);
		}
		else{
			if(ans1<10)
				Err();
			ans1-=10,ans2+=10;
		}
		const int dx[]={-1,-1,-1,0,0,1,1,1};
		const int dy[]={-1,0,1,-1,1,-1,0,1};
		for(reg int j=0;j<8;++j){
			reg int fx=x+dx[j],fy=y+dy[j];
			if(1<=fx&&fx<=n&&1<=fy&&fy<=m)
				b[fx][fy]=true;
		}
	}
	printf("%d %d\n",ans1,ans2);
	return 0;
}