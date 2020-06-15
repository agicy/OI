#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define MOD 10007
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(ch<'0'||'9'<ch)ch=getchar();
	while('0'<=ch&&ch<='9')res=10*res+ch-'0',ch=getchar();
	return res;
}

const int MAXN=250+5;

int n,m;
int G[MAXN][MAXN];

inline int pow(reg int x,reg int exp,reg int mod){
	reg int res=1;
	while(exp){
		if(exp&1)
			res=res*x%mod;
		x=x*x%mod;
		exp>>=1;
	}
	return res;
}

inline int inv(reg int x,reg int mod){
	return pow(x,mod-2,mod);
}

inline int Gauss(reg int n){
	reg int p=1;
	for(reg int i=1;i<n;++i){
		reg int Max=i;
		for(reg int j=i+1;j<=n;++j)
			if(G[Max][i]<G[j][i])
				Max=j;
		if(Max!=i){
			swap(G[i],G[Max]);
			p*=-1;
		}
		reg int I=inv(G[i][i],MOD);
		for(reg int j=i+1;j<=n;++j){
			reg int t=G[j][i]*I%MOD;
			for(reg int k=i;k<=n;++k)
				G[j][k]=(G[j][k]-t*G[i][k]%MOD+MOD)%MOD;
		}
	}
	if(p<0)
		p+=MOD;
	for(reg int i=1;i<=n;++i)
		p=p*G[i][i]%MOD;
	return p;
}

int main(void){
	n=read(),m=read();
	for(reg int i=1;i<=m;++i){
		static int a,b;
		a=read(),b=read();
		--G[b-1][a-1],++G[a-1][a-1];
	}
	for(reg int i=0;i<n;++i)
		for(reg int j=0;j<n;++j)
			G[i][j]=(G[i][j]+MOD)%MOD;
	printf("%d\n",Gauss(n-1));
	return 0;
}