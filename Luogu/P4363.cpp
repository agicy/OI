#include<bits/stdc++.h>
using namespace std;
#define reg register
#define INF 0X3F3F3F3F
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg bool f=false;
	reg char ch=getchar();
	reg int res=0;
	while(ch<'0'||'9'<ch)f|=(ch=='-'),ch=getchar();
	while('0'<=ch&&ch<='9')res=10*res+ch-'0',ch=getchar();
	return f?-res:res;
}

const int MAXN=10;

int n,m;
int a[MAXN][MAXN],b[MAXN][MAXN];
int f[1<<(MAXN<<1)];

inline int DFS(reg int S,reg bool flag){
	if(f[S]!=-1)
		return f[S];
	f[S]=flag?-INF:INF;
	reg int x=n,y=0;
	for(reg int i=0;i<n+m-1;++i){
		if((S>>i)&1)
			--x;
		else
			++y;
		if(((S>>i)&3)!=1)
			continue;
		reg int to=(S^(3<<i));
		if(flag)
			f[S]=max(f[S],DFS(to,false)+a[x][y]);
		else
			f[S]=min(f[S],DFS(to,true)-b[x][y]);
	}
	return f[S];

}

int main(void){
	n=read(),m=read();
	for(reg int i=0;i<n;++i)
		for(reg int j=0;j<m;++j)
			a[i][j]=read();
	for(reg int i=0;i<n;++i)
		for(reg int j=0;j<m;++j)
			b[i][j]=read();
	memset(f,-1,sizeof(f));
	f[((1<<n)-1)<<m]=0;
	printf("%d\n",DFS((1<<n)-1,true));
	return 0;
}
