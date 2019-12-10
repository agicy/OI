#include<cstdio>
#define reg register
typedef long long ll;
#define MOD 1000000007ll
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
const int MAXA=1024+5;

int n;
int a[MAXN];
ll pre_xor[MAXN][MAXA];
ll las_sum[MAXN][MAXA];

int main(void){
	reg int i,j;
	reg ll ans=0;
	n=read();
	for(i=1;i<=n;++i)
		a[i]=read();
	for(i=1;i<=n;++i){
		pre_xor[i][a[i]]=1;
		for(j=0;j<=1024;++j)
			pre_xor[i][j]=(pre_xor[i][j]+pre_xor[i-1][j^a[i]])%MOD;
		for(j=0;j<=1024;++j)
			pre_xor[i][j]=(pre_xor[i][j]+pre_xor[i-1][j])%MOD;
	}
	for(i=n;i>=1;--i){
		las_sum[i][a[i]]=1;
		for(j=0;j<=1024;++j)
			las_sum[i][j&a[i]]=(las_sum[i][j&a[i]]+las_sum[i+1][j])%MOD;
		for(j=0;j<=1024;++j)
			las_sum[i][j]=(las_sum[i][j]+las_sum[i+1][j])%MOD;
	}
	for(i=2;i<=n;++i)
		for(j=0;j<=1024;++j)
			ans=(ans+pre_xor[i-1][j]*(las_sum[i][j]-las_sum[i+1][j])%MOD)%MOD;
	printf("%lld\n",ans);
	return 0;
}
