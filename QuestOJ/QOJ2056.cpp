#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg bool f=false;
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))f|=(ch=='-'),ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return f?-res:res;
}

const int MAXN=60+5;
const int mod=1e9+7;

inline int add(reg int a,reg int b){
	a+=b;
	return a>=mod?a-mod:a;
}

inline int fpow(reg int x,reg int exp){
	reg int res=1;
	while(exp){
		if(exp&1)
			res=1ll*res*x%mod;
		x=1ll*x*x%mod;
		exp>>=1;
	}
	return res;
}

int n;
int a[MAXN];
int f[MAXN][MAXN][MAXN][MAXN];

inline bool check(reg int j,reg int i,reg int k){
	return a[k]-a[i]>=a[i]-a[j];
}

int main(void){
	n=read();
	for(reg int i=1;i<=n;++i)
		a[i]=read();
	sort(a+1,a+n+1);
	reg int cnt=0;
	for(reg int i=1;i<=n;++i)
		if(a[i]==a[1])
			++cnt;
	f[2][1][1][2]=1;
	for(reg int i=2;i<n;++i)
		for(reg int j=1;j<=i;++j)
			for(reg int k=1;k<=i;++k)
				for(reg int l=1;l<=i;++l)
					if(f[i][j][k][l]){
						if(check(j,i,i+1))
							f[i+1][i][k][l]=add(f[i+1][i][k][l],f[i][j][k][l]);
						if(check(l,k,i+1))
							f[i+1][k][i][j]=add(f[i+1][k][i][j],f[i][j][k][l]);
					}
	reg int ans=0;
	for(reg int i=1;i<=n;++i)
		for(reg int j=1;j<=n;++j)
			for(reg int k=1;k<=n;++k)
				ans=add(ans,f[n][i][j][k]);
	
	if(cnt==1)
		printf("%d\n",add(ans,ans));
	else{
		reg int fac=1;
		for(reg int i=1;i<=cnt;++i)
			fac=1ll*fac*i%mod;
		ans=1ll*ans*fpow(fpow(2,cnt-2),mod-2)%mod*fac%mod;
		printf("%d\n",ans);
	}
	return 0;
}