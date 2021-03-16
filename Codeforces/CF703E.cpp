#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar()(p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return res;
}

inline ll readll(void){
	reg char ch=getchar();
	reg ll res=0;
	while(!isdigit(ch))ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return res;
}

const int MAXN=1e3+5;
const int MAXS=1e4+5;
const ll inf=0x3f3f3f3f3f3f3f3f;

int n;
ll k;
ll a[MAXN],b[MAXN];
ll f[MAXS];
map<ll,int> M;
pair<int,ll> dp[MAXN][MAXS];

inline ll gcd(reg ll a,reg ll b){
	return b?gcd(b,a%b):a;
}

int main(void){
	n=read(),k=readll();
	reg ll tmp=k;
	for(reg int i=1;i<=n;++i){
		a[i]=readll();
		b[i]=gcd(a[i],k);
		tmp/=gcd(a[i],tmp);
	}
	if(tmp!=1)
		puts("-1");
	else if(k==1){
		reg int ans=-1;
		for(reg int i=1;i<=n;++i)
			if(ans==-1||a[i]<a[ans])
				ans=i;
		printf("1\n%d\n",ans);
	}
	else{
		reg int tot=0;
		for(reg int i=1;1ll*i*i<=k;++i)
			if(!(k%i)){
				f[tot++]=i;
				if(1ll*i*i!=k)
					f[tot++]=k/i;
			}
		sort(f,f+tot);
		for(reg int i=0;i<tot;++i)
			M[f[i]]=i;
		for(reg int i=1;i<tot;++i)
			dp[0][i]=make_pair(n+1,0);
		dp[0][0]=make_pair(0,0);
		for(reg int i=1;i<=n;++i)
			for(reg int j=0;j<tot;++j){
				dp[i][j]=dp[i-1][j];
				reg ll id=M[f[j]/gcd(f[j],b[i])];
				if(dp[i][j]>make_pair(dp[i-1][id].first+1,dp[i-1][id].second+a[i]))
					dp[i][j]=make_pair(dp[i-1][id].first+1,dp[i-1][id].second+a[i]);
			}
		printf("%d\n",dp[n][tot-1].first);
		ll tmp=k;
		for(reg int i=n;i>=1;--i)
			if(dp[i][M[tmp]]!=dp[i-1][M[tmp]]){
				printf("%d ",i);
				tmp/=gcd(tmp,b[i]);
			}
		putchar('\n');
	}
	return 0;
}