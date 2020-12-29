#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef unsigned int uint;
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

const int MAXN=1e5+5;
const int p=1e9+7;

inline int add(reg int a,reg int b){
	a+=b;
	return a>=p?a-p:a;
}

bool vis[MAXN];
int tot,prime[MAXN];
int mu[MAXN],phi[MAXN];

inline void Init(reg int n){
	mu[1]=phi[1]=1;
	for(reg int i=2;i<=n;++i){
		if(!vis[i]){
			prime[++tot]=i;
			mu[i]=p-1,phi[i]=i-1;
		}
		for(reg int j=1;j<=tot&&i*prime[j]<=n;++j){
			vis[i*prime[j]]=true;
			if(i%prime[j]==0){
				phi[i*prime[j]]=phi[i]*prime[j];
				break;
			}
			phi[i*prime[j]]=phi[i]*(prime[j]-1);
			mu[i*prime[j]]=p-mu[i];
		}
	}
	return;
}

int n;
int a[MAXN];
int f[MAXN];
vector<int> fac[MAXN];
int Q[MAXN];
int T[MAXN];

int main(void){
	n=read();
	for(reg int i=1;i<=n;++i)
		a[i]=read();
	Init(n);
	for(reg int i=1;i<=n;++i)
		for(reg int j=i;j<=n;j+=i)
			fac[j].push_back(i);
	for(reg int d=1;d<=n;++d){
		reg int head=0,tail=0;
		for(reg int i=d;i<=n;i+=d)
			for(reg int x:fac[a[i]])
				if(T[x])
					++T[x];
				else
					Q[tail++]=x,++T[x];
		while(head<tail){
			reg int v=Q[head++];
			f[d]=add(f[d],1ll*T[v]*T[v]%p*phi[v]%p),T[v]=0;
		}
	}
	reg int ans=0;
	for(reg int d=1;d<=n;++d)
		for(reg int x=1,dx=d;dx<=n;++x,dx+=d)
			ans=add(ans,1ll*d*mu[x]%p*f[dx]%p);
	printf("%d\n",ans);
	return 0;
}