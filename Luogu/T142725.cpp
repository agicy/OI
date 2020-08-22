#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline ll read(void){
	reg char ch=getchar();
	reg ll res=0;
	while(ch<'0'||'9'<ch)ch=getchar();
	while('0'<=ch&&ch<='9')res=10*res+ch-'0',ch=getchar();
	return res;
}

ll t;
int p;

inline int add(reg int a,reg int b){
	reg int sum=a+b;
	return sum>=p?sum-p:sum;
}

inline int sqr(reg int x){
	return 1ll*x*x%p;
}

inline int pow(reg int x,reg int exp){
	reg int res=1;
	while(exp){
		if(exp&1)
			res=1ll*res*x%p;
		x=1ll*x*x%p;
		exp>>=1;
	}
	return res;
}

const int MAXSIZE=2e6+5;

bool vis[MAXSIZE];
int tot,prime[MAXSIZE];
int c[MAXSIZE],d[MAXSIZE];

inline void Initd(reg int n){
	d[1]=1;
	for(reg int i=2;i<=n;++i){
		if(!vis[i]){
			d[i]=2;
			prime[++tot]=i;
			c[i]=1;
		}
		for(reg int j=1;j<=tot&&i*prime[j]<=n;++j){
			vis[i*prime[j]]=true;
			if(i%prime[j]==0){
				c[i*prime[j]]=c[i]+1;
				d[i*prime[j]]=d[i]/(c[i]+1)*(c[i*prime[j]]+1);
				break;
			}
			d[i*prime[j]]=d[i]*2;
			c[i*prime[j]]=1;
		}
	}
	return;
}

inline int Calcz(reg int z){
	return sqr(add(z,1));
}

int fy[MAXSIZE];

inline int Calcy(reg int y){
	if(fy[y])
		return fy[y];
	reg int res=1;
	for(reg int i=1;1ll*i*i<=y;++i)
		if(y%i==0){
			res=1ll*res*Calcz(i)%p;
			if(y/i!=i)
				res=1ll*res*Calcz(y/i)%p;
		}
	return fy[y]=pow(res,p-2)%p;
}

int fx[MAXSIZE];

inline int Calcx(reg int x){
	if(fx[x])
		return fx[x];
	reg int res=1;
	for(reg int i=1;1ll*i*i<=x;++i)
		if(x%i==0){
			res=1ll*res*pow(i,d[i])%p*Calcy(i)%p;
			if(x/i!=i)
				res=1ll*res*pow(x/i,d[x/i])%p*Calcy(x/i)%p;
		}
	return fx[x]=res;
}

int main(void){
	Initd(2e6);
	t=read(),p=read();
	reg int res=1;
	for(reg int i=1;i<=t;++i)
		res=1ll*res*Calcx(i)%p;
	printf("%d\n",res);
	return 0;
}