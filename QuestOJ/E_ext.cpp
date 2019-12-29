#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
typedef unsigned long long ull;
#define MOD 998244353
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg bool f=false;
	reg char ch=getchar();
	reg int res=0;
	while(ch<'0'||'9'<ch)f|=(ch=='-'),ch=getchar();
	while('0'<=ch&&ch<='9')res=10*res+ch-'0',ch=getchar();
	return f?-res:res;
}

const int MAXN=400000+5;
const int MAXM=400000+5;

int n,m,k;
int a[MAXN];

inline void Read(void);
inline void Work(void);

int main(void){
	Read();
	Work();
	return 0;
}

inline void Read(void){
	n=read(),m=read(),k=read();
	for(reg int i=1;i<=n;++i)
		a[i]=read();
	return;
}

inline int gcd(reg int a,reg int b){
	return b==0?a:gcd(b,a%b);
}

int ans[MAXM];
int b[MAXN],gcdb[MAXN];

inline void DFS(reg int dep,reg int notsame){
	if(notsame<k)
		return;
	if(dep==n+1){
		if(notsame>=k){
			//for(reg int i=1;i<=n;++i)
			//	printf("%d%c",b[i],i==n?'\n':' ');
			//for(reg int i=1;i<=n;++i)
			//	printf("%d%c",gcdb[i],i==n?'\n':' ');
			//putchar('\n');
			++ans[gcdb[n]];
			ans[gcdb[n]]%=MOD;
		}
		return;
	}
	for(reg int i=1;i<=m;++i){
		b[dep]=i;
		gcdb[dep]=gcd(b[dep],gcdb[dep-1]);
		if(a[dep]==b[dep])
			DFS(dep+1,notsame-1);
		else
			DFS(dep+1,notsame);
	}
	return;
}

inline ll pow(reg ll x,reg ll exp,reg ll mod){
	reg ll res=1;
	while(exp){
		if(exp&1)
			res=res*x%mod;
		x=x*x%mod;
		exp>>=1;
	}
	return res;
}

inline ll fac(reg ll x,reg ll mod){
	reg ll res=1;
	for(reg ll i=2;i<=x;++i)
		res=res*i%mod;
	return res;
}

inline ll inv(reg ll x,reg ll mod){
	return pow(x,mod-2,mod);
}

inline ll Calc(void){
	static int T[MAXM];
	memset(T,0,sizeof(T));
	for(reg int i=1;i<=n;++i)
		++T[b[i]];
	reg ll res=fac(n,MOD);
	for(reg int i=1;i<=m;++i)
		res=res*inv(fac(T[i],MOD),MOD)%MOD;
	return res;
}

inline void DFSkn(reg int dep,reg int last){
	if(dep==n+1){
		ans[gcdb[n]]=(ans[gcdb[n]]+Calc())%MOD;
		return;
	}
	for(reg int i=last;i<=m;++i){
		if(a[dep]==i)
			continue;
		b[dep]=i;
		gcdb[dep]=gcd(b[dep],gcdb[dep-1]);
		DFSkn(dep+1,i);
	}
	return;
}

inline void DFSk0(reg int dep,reg int last){
	if(dep==n+1){
		ans[gcdb[n]]=(ans[gcdb[n]]+Calc())%MOD;
		return;
	}
	for(reg int i=last;i<=m;++i){
		b[dep]=i;
		gcdb[dep]=gcd(b[dep],gcdb[dep-1]);
		DFSk0(dep+1,i);
	}
	return;
}

inline void Work(void){
	if(k==n){
		//fac[0]=1;
		//for(reg ll)
		DFSkn(1,1);
	}
	else if(k==0){
		DFSk0(1,1);
	}
	else{
		DFS(1,n);
	}
	for(reg int i=1;i<=m;++i)
		printf("%d%c",ans[i],i==m?'\n':' ');
	return;
}
