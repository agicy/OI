#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return res;
}

const int p=1e9+7;

inline int fpow(reg int x,reg int exp){
	reg int res=1;
	while(exp){
		if(exp&1)
			res=1ll*res*x%p;
		x=1ll*x*x%p;
		exp>>=1;
	}
	return res;
}

const int MAXN=400+5;

int n,m;
int f[MAXN<<1][MAXN<<1];

int main(void){
	n=read();
	m=(n<<1);
	for(reg int i=1;i<=n;++i){
		for(reg int j=1;j<=n;++j)
			f[i][j]=read();
		f[i][n+i]=1;
	}
	for(reg int i=1;i<=n;++i){
		for(reg int j=i;j<=n;++j)
			if(f[j][i]){
				for(reg int k=1;k<=m;++k)
					swap(f[i][k],f[j][k]);
				break;
			}
		if(!f[i][i]){
			puts("No Solution");
			return 0;
		}
		reg int r=fpow(f[i][i],p-2);
		for(reg int j=i;j<=m;++j)
			f[i][j]=1ll*f[i][j]*r%p;
		for(reg int j=1;j<=n;++j)
			if(i!=j){
				reg int r=f[j][i];
				for(reg int k=i;k<=m;++k)
					f[j][k]=(f[j][k]-1ll*r*f[i][k]%p+p)%p;
			}
	}
	for(reg int i=1;i<=n;++i)
		for(reg int j=n+1;j<=m;++j)
			printf("%d%c",f[i][j],j==m?'\n':' ');
	return 0;
}