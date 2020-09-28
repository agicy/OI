#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(ch<'0'||'9'<ch)ch=getchar();
	while('0'<=ch&&ch<='9')res=10*res+ch-'0',ch=getchar();
	return res;
}

inline void cMin(reg int &a,reg int b){
	if(a>b)
		a=b;
	return;
}

const int MAXN=1e5+5;
const int MAXM=20;

int n,m;
int a[MAXN];
int sum[MAXN][MAXM];
int f[1<<MAXM];
int T[MAXM];

int main(void){
	n=read(),m=read();
	for(reg int i=1;i<=n;++i){
		a[i]=read()-1;
		for(reg int j=0;j<m;++j)
			sum[i][j]=sum[i-1][j];
		++T[a[i]],++sum[i][a[i]];
	}
	reg int U=(1<<m)-1;
	memset(f,0x3f,sizeof(f));
	f[0]=0;
	for(reg int S=0;S<=U;++S){
		reg int s=0;
		for(reg int i=0;i<m;++i)
			if((S>>i)&1)
				s+=T[i];
		for(reg int i=0;i<m;++i)
			if(!((S>>i)&1))
				cMin(f[S^(1<<i)],f[S]+T[i]-sum[s+T[i]][i]+sum[s][i]);
	}
	printf("%d\n",f[U]);
	return 0;
}