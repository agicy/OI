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

const int MAXN=3e3+5;

int n,m;
bool G[MAXN][MAXN];
bool del[MAXN];

int main(void){
	n=read(),m=read();
	for(reg int i=1;i<=m;++i){
		static int a,b;
		a=read(),b=read();
		G[a][b]=G[b][a]=true;
	}
	for(reg int i=1;i<=n;++i)
		if(!del[i])
			for(reg int j=i+1;j<=n;++j)
				if(!G[i][j]&&!del[j]){
					del[i]=del[j]=true;
					break;
				}
	reg int tot=0;
	static int ans[MAXN];
	for(reg int i=1;i<=n;++i)
		if(!del[i])
			ans[++tot]=i;
	for(reg int i=1;i*3<=n;++i)
		printf("%d%c",ans[i],i*3==n?'\n':' ');
	return 0;
}