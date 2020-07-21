#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define int ll
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(ch<'0'||'9'<ch)ch=getchar();
	while('0'<=ch&&ch<='9')res=10*res+ch-'0',ch=getchar();
	return res;
}

inline int pow(reg int x,reg int exp,reg int mod){
	reg int res=1;
	while(exp){
		if(exp&1)
			res=1ll*res*x%mod;
		x=1ll*x*x%mod;
		exp>>=1;
	}
	return res;
}

inline int exgcd(reg int a,reg int b,reg int &x,reg int &y){
	if(!b){
		x=1,y=0;
		return a;
	}
	reg int gcd=exgcd(b,a%b,y,x);
	y-=(a/b)*x;
	return gcd;
}

map<int,int> M;

signed main(void){
	reg int T=read();
	reg int k=read();
	if(k==1)
		while(T--){
			reg int y=read(),z=read(),p=read();
			printf("%lld\n",pow(y,z,p));
		}
	else if(k==2)
		while(T--){
			reg int a=read(),b=read(),p=read();
			int x,y;
			reg int gcd=exgcd(a,p,x,y);
			if(b%gcd)
				puts("Orz, I cannot find x!");
			else{
				reg int temp=p/gcd;
				while(x<0)
					x+=temp;
				printf("%lld\n",((1ll*x*b/gcd)%temp+temp)%temp);
			}
		}
	else
		while(T--){
			reg int y=read(),z=read(),p=read();
			reg int m=ceil(sqrt(p));
			if(y%p==0&&z){
				puts("Orz, I cannot find x!");
				continue;
			}
			M.clear();
			int x=z%p,f=pow(y,m,p);
			M[x]=0;
			for(reg int i=1;i<=m;++i){
				x=(x*y)%p;
				M[x]=i;
			}
			x=1;
			reg bool flag=true;
			for(reg int i=1;i<=m;++i){
				x=1ll*x*f%p;
				if(M[x]){
					reg int ans=(i*m-M[x])%p;
					printf("%lld\n",(ans+p)%p);
					flag=false;
					break;
				}
			}
			if(flag)
				puts("Orz, I cannot find x!");
		}
	return 0;
}