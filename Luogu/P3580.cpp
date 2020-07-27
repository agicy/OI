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

const int MAXN=1e6+5;

int n;
ll s;
ll t[MAXN];
ll dp[MAXN];

inline void Min(reg ll& x,reg ll y){
	if(x==-1||x>y)
		x=y;
	return;
}

int main(void){
	n=read(),s=read();
	t[0]=-1;
	for(reg int i=1;i<=n;++i){
		t[i]=read();
		if(t[i]<=t[i-1])
			t[i]=t[i-1]+1;
	}
	memset(dp,-1,sizeof(dp));
	dp[0]=0;
	for(reg int i=1,j=0;i<=n;++i){
		while(j<i&&dp[j]+i-j-1<=t[i])
			++j;
		Min(dp[i],t[i]+i-j+2ll*s);
		if(dp[j]!=-1&&dp[j]+i-j-1>=t[i])
			Min(dp[i],dp[j]+2ll*(i-j-1+s));
	}
	printf("%lld\n",dp[n]);
	return 0;
}
