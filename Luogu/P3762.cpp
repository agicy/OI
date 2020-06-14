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

const int MAXN=20+5;
const int MAXM=10000+5;

int n,m,K;
ll b[MAXM];
ll a[MAXN][MAXM];

inline ll add(reg ll a,reg ll b,reg ll mod){
	reg ll sum=a+b;
	return sum>=mod?sum-mod:sum;
}

inline ll mul(reg ll a,reg ll b,reg ll mod){
	reg ll res=0;
	while(b){
		if(b&1)
			res=add(res,a,mod);
		a=add(a,a,mod);
		b>>=1;
	}
	return res;
}

inline ll pow(reg ll x,reg ll exp,reg ll mod){
	reg ll res=1;
	while(exp){
		if(exp&1)
			res=mul(res,x,mod);
		x=mul(x,x,mod);
		exp>>=1;
	}
	return res;
}


const int MAXSIZE=10000+5;

inline bool Miller_Rabin(reg ll n){
	if(n==2)
		return true;
	const int TEST_TIME=10;
	for(reg int i=TEST_TIME;i;--i){
		reg ll a=rand()%(n-2)+1;
		reg ll p=n-1;
		if(pow(a,n-1,n)!=1)
			return false;
		while(!(p&1)){
			p>>=1;
			reg ll temp=pow(a,p,n);
			if(mul(temp,temp,n)==1&&temp!=1&&temp!=n-1)
				return false;
		}
	}
	return true;
}

inline ll gcd(reg ll a,reg ll b){
	return b==0?a:gcd(b,a%b);
}

inline ll Pollard_Rho(reg ll n){
	reg ll i=0,k=2,x=rand()%(n-1)+1,y=x;
	reg int c=rand();
	while(true){
		++i;x=(mul(x,x,n)+c)%n;
		reg ll Gcd=gcd((y-x+n)%n,n);
		if(Gcd!=1&&Gcd!=n)
			return Gcd;
		if(x==y)
			return n;
		if(i==k)
			k<<=1,y=x;
	}
	return n;
}

int tot;
ll fac[MAXSIZE],T[MAXSIZE];

inline void Div(reg ll n){
	if(n==1)
		return;
	if(Miller_Rabin(n)){
		fac[++tot]=n;
		return;
	}
	reg ll p=n;
	while(p>=n)
		p=Pollard_Rho(n);
	Div(p),Div(n/p);
	return;
}

ll ta[MAXM];
ll tb[MAXM];

inline void Solve(reg int id,reg ll M){
	tot=0;
	memset(T,0,sizeof(T));

	Div(M);
	sort(fac+1,fac+tot+1);
	tot=unique(fac+1,fac+tot+1)-(fac+1);

	reg ll phi=M;
	for(reg int i=1;i<=tot;++i)
		phi=phi/fac[i]*(fac[i]-1);

	for(reg int i=1;i<=m;++i){
		tb[i]=b[i];
		for(reg int j=1;j<=tot;++j)
			if(tb[i]%fac[j]==0)
				while(tb[i]%fac[j]==0){
					++T[j];
					tb[i]/=fac[j];
				}
	}
	for(reg int i=1;i<=m;++i){
		ta[i]=a[id][i];
		for(reg int j=1;j<=tot;++j)
			if(ta[i]%fac[j]==0)
				while(ta[i]%fac[j]==0){
					--T[j];
					ta[i]/=fac[j];
				}
	}
	reg ll ans1=1,ans2=1;
	for(reg int i=1;i<=tot;++i)
		if(T[i]<0){
			puts("-1");
			return;
		}
		else if(T[i])
			ans1=mul(ans1,pow(fac[i],T[i],M),M);
	for(reg int i=1;i<=m;++i)
		ans1=mul(ans1,tb[i],M),ans2=mul(ans2,ta[i],M);
	printf("%lld\n",mul(ans1,pow(ans2,phi-1,M),M));
	return;
}

int main(void){
	srand(time(0));
	n=read(),m=read(),K=read();
	for(reg int i=1;i<=m;++i)
		b[i]=read();
	for(reg int i=1;i<=n;++i)
		for(reg int j=1;j<=m;++j)
			a[i][j]=read();
	for(reg int i=1;i<=K;++i){
		static ll x,M;
		x=read(),M=read();
		Solve(x,M);
	}
	return 0;
}