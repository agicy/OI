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

const int MAXN=2e3+5;

int n,k;
int l[MAXN],r[MAXN],a[MAXN];
int dp[MAXN];

int main() {
	n=read(),k=read();
	for(reg int i=1;i<=n;++i)
		l[i]=read(),r[i]=read(),a[i]=read();
	for(reg int i=n;i>=1;--i){
		reg int tmp=a[i];
		if(r[i]==l[i+1]&&i!=n)
			tmp+=dp[i+1];
		if(tmp>1ll*(r[i]-l[i]+1)*k){
			puts("-1");
			return 0;
		}
		dp[i]=max(0ll,tmp-1ll*(r[i]-l[i])*k);
	}
	reg int sum=k;
	reg ll ans=0;
	for(reg int i=1;i<=n;++i){
		if(sum<dp[i]){
			ans+=sum;
			sum=k;
		}
		ans+=a[i];
		sum=(sum-a[i]%k+k)%k;
	}
	printf("%lld\n",ans);
	return 0;
}