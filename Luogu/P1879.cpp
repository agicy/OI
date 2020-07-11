#include<bits/stdc++.h>
using namespace std;
#define reg register
#define MOD 100000000
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

const int MAXN=12+1;
const int MAXM=12+1;

int m,n;
int a[MAXM][MAXN];
int Max[MAXM];
int S[1<<MAXN];
int f[MAXM][1<<MAXN];

int main(void){
	m=read(),n=read();
	for(reg int i=1;i<=m;++i)
		for(reg int j=1;j<=n;++j)
			a[i][j]=read();
	for(reg int i=1;i<=m;++i)
		for(reg int j=1;j<=n;++j)
			Max[i]=(Max[i]<<1)+a[i][j];
	for(reg int i=0;i<(1<<n);++i)
		S[i]=((i&(i<<1))==0)&&((i&(i>>1))==0);
	f[0][0]=1;
	for(reg int i=1;i<=m;++i)
		for(reg int j=0;j<(1<<n);++j)
			if(S[j]&&((j&Max[i])==j))
				for(reg int k=0;k<(1<<n);++k)
					if((k&j)==0)
						f[i][j]=(f[i][j]+f[i-1][k])%MOD;
	reg int ans=0;
	for(reg int i=0;i<(1<<n);++i)
		ans=(ans+f[m][i])%MOD;
	printf("%d\n",ans);
	return 0;
}
