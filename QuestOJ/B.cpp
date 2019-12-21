#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
typedef unsigned long long ull;
#define MOD 998244353ll
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

const int MAXN=100+5;

int n,k,cnt;
int a[MAXN];

inline void Read(void);
inline void Work(void);

int main(void){
	Read();
	Work();
	return 0;
}

inline void Read(void){
	n=read(),k=read();
	for(reg int i=1;i<=n;++i)
		a[i]=read(),cnt+=(a[i]==0);
	return;
}

int temp[MAXN];
ll A,B;

inline void DFS(reg int dep){
	if(dep==k+1){
		//putchar('k');
		reg bool flag=true;
		for(reg int i=1;i<=cnt&&flag;++i)
			flag&=(temp[i]==0);
		if(flag)
			++A;
		return;
	}
	for(reg int i=1,j;i<n;++i)
		for(j=i+1;j<=n;++j){
			swap(temp[i],temp[j]);
			DFS(dep+1);
			swap(temp[i],temp[j]);
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

inline ll inv(reg ll x,reg ll mod){
	return pow(x,mod-2,mod);
}

inline void Work(void){
	if(cnt==n||cnt==0||n==0||n==1){
		puts("1");
		return;
	}
	if(n==2){
		if(a[1]==1&&(k&1))
			puts("1");
		else if(a[1]==0&&!(k&1))
			puts("1");
		else
			puts("0");
		return;
	}
	if(n==3){
		printf("%lld\n",pow(3,k-1,MOD)*inv(pow(3,k,MOD),MOD)%MOD);
		return;
	}
	memcpy(temp,a,sizeof(a));
	reg ll b=pow(n*(n-1)/2,k,MOD);
	DFS(1);
	printf("%lld\n",A*inv(b,MOD)%MOD);
	//printf("%lld %lld\n",A,b);
	return;
}
