#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
typedef unsigned long long ull;
#define MOD 10000
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

const int MAXN=1000+5;
const int MAXK=1000+5;

int n,k,f[MAXN][MAXK];

int main(void){
	n=read(),k=read();
	f[1][0]=1;
	for(reg int i=2;i<=n;++i)
		for(reg int j=0,sum=0;j<=k;++j){
			sum=(sum+f[i-1][j])%MOD;
			f[i][j]=sum;
			if(j>=i-1)
				sum=(sum-f[i-1][j-i+1]+MOD)%MOD;
		}
	printf("%d\n",f[n][k]);
	return 0;
}
