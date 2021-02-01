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

const int MAXN=12+5;
const int mod=998244353;

int n,m;
int s[MAXN],kmp[MAXN];
int a[MAXN],ans;

inline void dfs(reg int dep,reg int cnt){
	if(dep==n){
		reg int res=1;
		for(reg int i=1,j=-1;i<=n;++i){
			while(j!=-1&&s[j]!=s[i-1])
				j=kmp[j];
			kmp[i]=++j;
			res=1ll*res*(i-j)%mod;
		}
		ans=(ans+1ll*res*a[cnt]%mod)%mod;
		return;
	}
	for(reg int i=1;i<=cnt;++i){
		s[dep]=i;
		dfs(dep+1,cnt);
	}
	if(cnt+1<=m){
		s[dep]=cnt+1;
		dfs(dep+1,cnt+1);
	}
	return;
}

int main(void){
	n=read(),m=read();
	a[0]=1;
	for(reg int i=1;i<=n&&i<=m;++i)
		a[i]=1ll*a[i-1]*(m-i+1)%mod;
	kmp[0]=-1;
	dfs(0,0);
	printf("%d\n",ans);
	return 0;
}