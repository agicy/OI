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

const int MAXN=10+5;

inline int gcd(reg int a,reg int b){
	return b==0?a:gcd(b,a%b);
}

int n;
int a[MAXN];
int d[MAXN][MAXN];
int ans=0x3f3f3f3f;
int cnt[MAXN],T[MAXN][MAXN];

inline void dfs(reg int dep,int m){
	if(m>ans)
		return;
	if(dep>n){
		ans=min(ans,m);
		return;
	}
	for(reg int i=1;i<=m;++i){
		reg bool flag=true;
		for(reg int j=1;j<=cnt[i];++j)
			if(d[dep][T[i][j]]!=1){
				flag=false;
				break;
			}
		if(flag){
			T[i][++cnt[i]]=dep;
			dfs(dep+1,m);
			--cnt[i];
		}
	}
	T[m+1][++cnt[m+1]]=dep;
	dfs(dep+1,m+1);
	--cnt[m+1];
	return;
}

int main(void){
	n=read();
	for(reg int i=1;i<=n;++i)
		a[i]=read();
	for(reg int i=1;i<=n;++i)
		for(reg int j=1;j<=n;++j)
			d[i][j]=gcd(a[i],a[j]);
	dfs(1,0);
	printf("%d\n",ans);
	return 0;
}