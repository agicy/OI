#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
typedef unsigned long long ull;
#define INF 0X3F3F3F3F
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg bool f=false;
	reg char ch=getchar();
	reg int res=0;
	while(ch<'0'||'9'<ch){
		if(ch==EOF)
			return EOF;
		f|=(ch=='-'),ch=getchar();
	}
	while('0'<=ch&&ch<='9')res=10*res+ch-'0',ch=getchar();
	return f?-res:res;
}

const int MAXM=200+5;
const int MAXP=1000+5;

inline void Read(void);
inline void Work(void);

int main(void){
	Read();
	Work();
	return 0;
}

int m;
int w[MAXM][MAXM];
int cnt,p[MAXP];

inline void Read(void){
	m=read();
	for(reg int i=1;i<=m;++i)
		for(reg int j=1;j<=m;++j)
			w[i][j]=read();
	do
		p[++cnt]=read();
	while(p[cnt]!=EOF);
	--cnt;
	return;
}

int f[2][MAXM][MAXM];

inline void Work(void){
	for(reg int i=1;i<=m;++i)
		for(reg int j=1;j<=m;++j)
			f[0][i][j]=INF;
	reg int last=0,now=1;
	f[last][1][2]=0;
	p[0]=3;
	for(reg int i=1;i<=cnt;++i){
		for(reg int j=1;j<=m;++j)
			for(reg int k=1;k<=m;++k)
				f[now][j][k]=INF;
		for(reg int j=1;j<=m;++j)
			for(reg int k=1;k<=m;++k)
				if(f[last][j][k]!=INF&&j!=k&&j!=p[i-1]&&k!=p[i-1]){
					if(j!=p[i]&&k!=p[i])
						f[now][j][k]=min(f[now][j][k],f[last][j][k]+w[p[i-1]][p[i]]);
					if(k!=p[i])
						f[now][p[i-1]][k]=min(f[now][p[i-1]][k],f[last][j][k]+w[j][p[i]]);
					if(j!=p[i])
						f[now][j][p[i-1]]=min(f[now][j][p[i-1]],f[last][j][k]+w[k][p[i]]);
				}
		now^=1,last^=1;
	}
	reg int ans=INF;
	for(reg int i=1;i<=m;++i)
		for(reg int j=1;j<=m;++j)
			ans=min((int)ans,f[last][i][j]);
	printf("%d\n",ans);
	return;
}
