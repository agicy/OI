#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
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

const int MAXN=200000+5;

inline void Read(void);
inline void Work(void);

int main(void){
	//freopen("ring.in","r",stdin);
	//freopen("ring.out","w",stdout);
	Read();
	Work();
	//fclose(stdin);
	//fclose(stdout);
	return 0;
}

int n,m;
ll a[MAXN],f[MAXN];

inline void Read(void){
	n=read(),m=read();
	for(reg int i=1;i<=n;++i)
		a[i]=read();
	return;
}

inline int gcd(reg int a,reg int b){
	return b==0?a:gcd(b,a%b);
}

inline ll Solve(reg int K){
	if(K==0||n==1){
		reg ll res=0;
		for(reg int i=1;i<=n;++i)
			res+=a[i]*a[i];
		return res;
	}
	reg int p=n/gcd(n,K);
	if(f[p])
		return f[p];
	else{
		reg ll res=0;
		for(reg int i=1;i<=n;i+=p){
			for(reg int j=0;j<p-2;++j)
				res+=a[i+j]*a[i+j+2];
			res+=a[i]*a[i+1]+a[i+p-1]*a[i+p-2];
		}
		return f[p]=res;
	}
}

inline void Work(void){
	sort(a+1,a+n+1);
	while(m--){
		static int K;
		K=read();
		printf("%lld\n",Solve(K));
	}
	return;
}
