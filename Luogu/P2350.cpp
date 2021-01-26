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

const int MAXN=1e5+5;

bool vis[MAXN];
int tot,prime[MAXN];
int f[MAXN];

inline void Init(reg int n){
	f[1]=1;
	for(reg int i=2;i<=n;++i){
		if(!vis[i]){
			prime[++tot]=i;
			f[i]=f[i-1];
		}
		for(reg int j=1;j<=tot&&i*prime[j]<=n;++j){
			vis[i*prime[j]]=true;
			f[i*prime[j]]=f[i]+f[prime[j]];
			if(!(i%prime[j]))
				break;
		}
	}
	return;
}

int main(void){
	Init(1e5);
	reg int T=read();
	while(T--){
		reg int n=read();
		reg ll ans=0;
		reg bool flag=false;
		for(reg int i=1;i<=n;++i){
			static int p,q;
			p=read(),q=read();
			if(p==2)
				flag=true;
			ans+=1ll*f[p]*q;
		}
		if(!flag)
			++ans;
		printf("%lld\n",ans);
	}
	return 0;
}