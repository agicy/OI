#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

bool st;

#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
static char buf[1<<21],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch)) ch=getchar();
	while(isdigit(ch)) res=10*res+(ch^'0'),ch=getchar();
	return res;
}

const int MAXN=1e7+5;
const int mod=1e9+7;

inline int add(reg int a,reg int b){
	a+=b;
	return a>=mod?a-mod:a;
}

inline int sub(reg int a,reg int b){
	a-=b;
	return a<0?a+mod:a;
}

inline int fpow(reg int x,reg int exp){
	reg int res=1;
	while(exp){
		if(exp&1)
			res=1ll*res*x%mod;
		x=1ll*x*x%mod,exp>>=1;
	}
	return res;
}

int n,k;
bool vis[MAXN];
int tot,prime[MAXN];
int bas[MAXN];

inline void init(reg int n){
	bas[1]=1;
	for(reg int i=2;i<=n;++i){
		if(!vis[i]){
			prime[++tot]=i;
			bas[i]=fpow(i,k);
		}
		for(reg int j=1;j<=tot&&i*prime[j]<=n;++j){
			vis[i*prime[j]]=true;
			bas[i*prime[j]]=1ll*bas[i]*bas[prime[j]]%mod;
			if(!(i%prime[j]))
				break;
		}
	}
	return;
}

bool ed;

int main(void){
	scanf("%d%d",&n,&k);
	init(n);
	reg int ans=0;
	for(reg int i=1;i<=n;++i)
		ans=add(ans,1ll*(n/i)*bas[i]%mod);
	printf("%d\n",ans);
	fprintf(stderr,"%.3lf s\n",1.0*clock()/CLOCKS_PER_SEC);
	fprintf(stderr,"%.3lf MiB\n",(&ed-&st)/1048576.0);
	return 0;
}