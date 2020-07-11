#include<bits/stdc++.h>
using namespace std;
#define reg register
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

const int MAXN=2000+5;
const int MAXM=2000+5;

inline void Read(void);
inline void Work(void);

int main(void){
	Read();
	Work();
	return 0;
}

int n,m;
int a[MAXN],b[MAXM];

inline void Read(void){
	n=read(),m=read();
	for(reg int i=1;i<=n;++i)
		a[i]=read()-1;
	for(reg int i=1;i<=m;++i)
		b[i]=read()-1;
	return;
}

int f[MAXN][MAXM];

inline void Work(void){
	memset(f,0X3F,sizeof(f));
	f[0][0]=0;
	for(reg int i=1;i<=n;++i)
		for(reg int j=1;j<=m;++j)
			f[i][j]=min(f[i-1][j-1],min(f[i-1][j],f[i][j-1]))+a[i]*b[j];
	printf("%d\n",f[n][m]);
	return;
}
