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
const int MAXM=1e5+5;

int n,m;
int a[MAXN],b[MAXN];

namespace Subtask1{
	const int MAXM=6e3+5;
	int f[MAXM];
	inline int add(reg int a,reg int b){
		a+=b;
		return a>=m?a-m:a;
	}
	inline int solve(reg int a,reg int b){
		f[0]=a%m,f[1]=b%m;
		if(!f[0])
			return 0;
		if(!f[1])
			return 1;
		for(reg int i=2;i<=6*m;++i){
			f[i]=add(f[i-1],f[i-2]);
			if(!f[i])
				return i;
		}
		return -1;
	}
	inline void Solve(void){
		for(reg int i=1;i<=n;++i){
			reg int ans=solve(a[i],b[i]);
			printf("%d\n",ans);
		}
		return;
	}
}

namespace Subtask2{
	const int MAXM=2e5+100;
	int f[MAXM];
	inline int add(reg int a,reg int b){
		a+=b;
		return a>=m?a-m:a;
	}
	inline int solve(reg int a,reg int b){
		f[0]=a%m,f[1]=b%m;
		if(!f[0])
			return 0;
		if(!f[1])
			return 1;
		for(reg int i=2;i<=2*m+10;++i){
			f[i]=add(f[i-1],f[i-2]);
			if(!f[i])
				return i;
		}
		return -1;
	}
	inline void Solve(void){
		for(reg int i=1;i<=n;++i){
			reg int ans=solve(a[i],b[i]);
			printf("%d\n",ans);
		}
		return;
	}
}

bool vis[MAXM];
int tot,prime[MAXM];
int from[MAXM];

inline void Init(reg int n){
	from[1]=1;
	for(reg int i=2;i<=n;++i){
		if(!vis[i]){
			prime[++tot]=i;
			from[i]=i;
		}
		for(reg int j=1;j<=tot&&i*prime[j]<=n;++j){
			vis[i*prime[j]]=true;
			from[i*prime[j]]=prime[j];
			if(!(i%prime[j]))
				break;
		}
	}
	return;
}

namespace Subtask3{
	const int inf=0x3f3f3f3f;
	int tot,fac[MAXM];
	int f[MAXM*6];
	map<pair<int,int>,int> M;
	inline pair<int,int> calc(reg int p,reg int a,reg int b){
		pair<int,int> res=make_pair(inf,0);
		f[0]=a%p,f[1]=b%p;
		if(!f[0])
			res.first=0;
		else if(!f[1])
			res.first=1;
		M.clear();
		M[make_pair(f[0],f[1])]=1;
		for(int i=2;i<=6*p;++i){
			f[i]=(f[i-1]+f[i-2])%p;
			if(!f[i]) res.first=min(res.first,i);
			pair<int,int> tmp=make_pair(f[i-1],f[i]);
			if(M.find(tmp)!=M.end()){
				res.second=i-M[tmp];
				return res;
			}
		}
		return make_pair(-1,-1);
	}
	ll x[MAXM],y[MAXM];
	namespace exCRT{
		inline ll exgcd(reg ll a,reg ll b,reg ll &x,reg ll &y){
			if(!b){
				x=1,y=0;
				return a;
			}
			reg ll res=exgcd(b,a%b,y,x);
			y-=(a/b)*x;
			return res;
		}
		inline ll excrt(reg int n,reg ll a[],reg ll r[]){
			if(n==1)
				return a[1];
			reg ll M=a[1],R=r[1];
			ll x,y;
			for(reg int i=2;i<=n;++i){
				reg ll d=exgcd(M,a[i],x,y);
				if((R-r[i])%d)
					return -1;
				x=(R-r[i])/d*x%a[i];
				R-=M*x;
				M=M/d*a[i];
				R%=M;
			}
			return (R%M+M)%M;
		}
	}
	inline int solve(reg int a,reg int b){
		reg bool flag=false;
		for(reg int i=1;i<=tot;++i){
			pair<int,int> tmp=calc(fac[i],a,b);
			x[i]=tmp.first,y[i]=tmp.second;
			if(fac[i]==2&&x[i]==0){
				flag=true;
				swap(fac[i],fac[tot]);
				--i,--tot;
				continue;
			}
			if(x[i]==-1||y[i]==0)
				return -1;
		}
		return exCRT::excrt(tot,x,y)*(flag?2:1);
	}
	inline void Solve(void){
		reg int tmp=m;
		while(tmp!=1){
			reg int p=from[tmp];
			while(tmp%p==0)
				tmp/=p;
			fac[++tot]=p;
		}
		for(reg int i=1;i<=n;++i){
			reg int ans=solve(a[i],b[i]);
			printf("%d\n",ans);
		}
		return;
	}
}

int main(void){
	freopen("fib.in","r",stdin);
	freopen("fib.out","w",stdout);

	Init(1e5);
	n=read(),m=read();
	for(reg int i=1;i<=n;++i)
		a[i]=read(),b[i]=read();
	if(n<=1e3&&m<=1e3)
		Subtask1::Solve();
	else if((!vis[m])&&1ll*m*n<=2e8)
		Subtask2::Solve();
	else
		Subtask3::Solve();

	fclose(stdin);
	fclose(stdout);
	return 0;
}