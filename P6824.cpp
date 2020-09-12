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

const int MAXN=1e6+5;
const int MAXLOG2K=20+1;

int n,k;
int dp[MAXN<<2];

inline void solve(reg int x){
	reg int res=0;
	for(reg int i=MAXLOG2K-1;i>=0;--i){
		if(((k&x)>>i)&1)
			++dp[res+(1<<i)],--dp[res+(1<<(i+1))];
		else if((k>>i)&1){
			++dp[res],--dp[res+(1<<i)];
			res+=(1<<i);
		}
		else if((x>>i)&1)
			res+=(1<<i);
	}
	return;
}

int main(void){
	n=read(),k=read();
	for(reg int i=1;i<=n;++i){
		static int x;
		x=read();
		solve(x);
	}
	int ans=0;
	for(reg int i=0;i<=(1<<20);++i){
		if(i)
			dp[i]+=dp[i-1];
		ans=max(ans,dp[i]);
	}
	printf("%d\n",ans);
	return 0;
}