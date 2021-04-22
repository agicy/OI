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

inline int lowbit(reg int x){
	return x&(-x);
}

inline ll gcd(reg ll a,reg ll b){
	return b?gcd(b,a%b):a;
}

inline ll min(reg ll a,reg ll b){
	return a<b?a:b;
}

const int prime[]={2,3,5,7,11,13,17,19,23,29,31,37,41,43,47};
const int tot=sizeof(prime)/sizeof(int);
const int MAXN=50+5;

int n;
int a[MAXN];
int lg[1<<tot];
ll pod[1<<tot];

int main(void){
	for(reg int i=0;i<tot;++i)
		lg[1<<i]=i;
	n=read();
	for(reg int i=1;i<=n;++i)
		a[i]=read();
	pod[0]=1;
	reg ll ans=2e18;
	for(reg int S=1;S<(1<<tot);++S){
		pod[S]=pod[S^lowbit(S)]*prime[lg[lowbit(S)]];
		reg bool flag=true;
		for(reg int i=1;i<=n;++i)
			if(gcd(pod[S],a[i])==1){
				flag=false;
				break;
			}
		if(flag)
			ans=min(ans,pod[S]);
	}
	printf("%lld\n",ans);
	return 0;
}