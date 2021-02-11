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

const int MAXN=500+5;

bool vis[MAXN];
int tot,prime[MAXN];
int phi[MAXN];
ll ans[MAXN];

inline void Init(reg int n){
	phi[1]=0;
	for(reg int i=2;i<=n;++i){
		if(!vis[i]){
			prime[++tot]=i;
			phi[i]=i-1;
		}
		for(reg int j=1;j<=tot&&i*prime[j]<=n;++j){
			vis[i*prime[j]]=true;
			if(!(i%prime[j])){
				phi[i*prime[j]]=phi[i]*prime[j];
				break;
			}
			phi[i*prime[j]]=phi[i]*(prime[j]-1);
		}
	}
	for(reg int i=1;i<=n;++i)
		ans[i]=phi[i];
	for(reg int i=2;i*i<=n;++i){
		ans[i*i]+=phi[i]*i;
		for(reg int j=i+1;j*i<=n;++j)
			ans[j*i]+=1ll*phi[i]*j+1ll*phi[j]*i;
	}
	ans[1]=0;
	for(reg int i=2;i<=n;++i)
		ans[i]+=ans[i-1];
	return;
}

int n;

int main(void){
	Init(501);
	while(scanf("%d",&n)!=EOF&&n)
		printf("%lld\n",ans[n]);
	return 0;
}