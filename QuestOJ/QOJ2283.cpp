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
	while(isdigit(ch))res=10*res+ch-'0',ch=getchar();
	return f?-res:res;
}

inline ll max(reg ll a,reg ll b){
	return a<b?b:a;
}

inline ll min(reg ll a,reg ll b){
	return a<b?a:b;
}

const int MAXN=1e5+5;
const ll inf=0x3f3f3f3f3f3f3f3fll;

int n,m;
int a[MAXN];
ll dp[MAXN];
deque<int> Q;

int main(void){
	n=read(),m=read();
	for(reg int i=1;i<=n;++i)
		a[i]=read();
	for(int i=n;i>=1;--i){
		dp[i]=a[i];
		while(!Q.empty()&&Q.front()>i+m)Q.pop_front();
		if(!Q.empty())
			dp[i]-=dp[Q.front()];
		while(!Q.empty()&&dp[i]>=dp[Q.back()])
			Q.pop_back();
		Q.push_back(i);
	}
	reg ll ans=-inf;
	for(reg int i=1;i<=min(n,m);++i)
		ans=max(ans,dp[i]);
	printf("%lld\n%lld\n",ans,-ans);
	return 0;
}