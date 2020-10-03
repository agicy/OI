#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline ll read(void){
	reg bool f=false;
	reg char ch=getchar();
	reg ll res=0;
	while(ch<'0'||'9'<ch)f|=(ch=='-'),ch=getchar();
	while('0'<=ch&&ch<='9')res=10*res+ch-'0',ch=getchar();
	return f?-res:res;
}

const int MAXN=200000+5;

int n;
ll x;
int d[MAXN<<1];
ll sum[MAXN<<1],sumH[MAXN<<1];

int main(void){
	n=read(),x=read();
	for(reg int i=1;i<=n;++i)
		d[i]=d[i+n]=read();
	for(reg int i=1;i<=(n<<1);++i){
		sum[i]=sum[i-1]+d[i];
		sumH[i]=sumH[i-1]+(((ll)d[i]*(d[i]+1))>>1);
	}
	ll ans=0;
	for(reg int i=1,j=0;i<=(n<<1);++i){
		while(sum[i]-sum[j]>x)
			++j;
		if(sum[i]>=x){
			reg ll temp=x-sum[i]+sum[j];
			ans=max(ans,sumH[i]-sumH[j]+(((((ll)d[j]<<1)+1-temp)*temp)>>1));
		}
	}
	printf("%lld\n",ans);
	return 0;
}