#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline ll read(void){
	reg char ch=getchar();
	reg ll res=0;
	while(ch<'0'||'9'<ch)ch=getchar();
	while('0'<=ch&&ch<='9')res=10*res+ch-'0',ch=getchar();
	return res;
}

const int MAXN=300000+5;

int n;
int sum[MAXN];
int cnt[MAXN];
int T[2]={1};

int main(void){
	n=read();
	reg ll ans=0;
	for(reg int i=1;i<=n;++i){
		static ll x;
		x=read();
		while(x){
			cnt[i]+=(x&1);
			x>>=1;
		}
		sum[i]=sum[i-1]+cnt[i];
		ans+=T[sum[i]&1];
		int Max=0;
		for(reg int j=i,k=i+1;j>=1&&j>=i-64;--j){
			while(k>j)
				Max=max(Max,cnt[--k]);
			if((Max<<1)>sum[i]-sum[j-1]&&(sum[i]&1)==(sum[j-1]&1))
				--ans;
		}
		++T[sum[i]&1];
	}
	printf("%lld\n",ans);
	return 0;
}