#include<bits/stdc++.h>
using namespace std;
#define reg register
#define INF 0X3F3F3F3F
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

const int MAXSQRTA=45000+5;
const int MAXCNT=10+5;

int prime[MAXSQRTA],totp;
bool vis[MAXSQRTA];

inline void Init(reg int n){
	for(reg int i=2;i<=n;++i){
		if(!vis[i])
			prime[totp++]=i;
		for(reg int j=0;j<totp&&i*prime[j]<=n;++j){
			vis[prime[j]*i]=true;
			if(i%prime[j]==0)
				break;
		}
	}
	return;
}

inline int gcd(reg int a,reg int b){
	return b==0?a:gcd(b,a%b);
}

int cnt;
pair<int,int> fac[MAXCNT];

int tot,divi[MAXSQRTA];

inline void dfs(reg int u,reg int p){
	if(u>cnt){
		divi[++tot]=p;
		return;
	}
	for(reg int i=0;i<=fac[u].second;++i){
		dfs(u+1,p);
		p*=fac[u].first;
	}
	return;
}

inline void Div(int d){
	cnt=0;
	for(reg int i=0;prime[i]<=d/prime[i];++i){
		int num=prime[i];
		if(d%num==0){
			int pow=0;
			while(d%num==0){
				++pow;
				d/=num;
			}
			fac[++cnt]=make_pair(num,pow);
		}
	}
	if(d>1)
		fac[++cnt]=make_pair(d,1);
	return;
}

int main(void){
	Init(45000);
	reg int n=read();
	while(n--){
		static int a0,a1,b0,b1;
		a0=read(),a1=read(),b0=read(),b1=read();
		reg int d=b1;
		Div(d);
		tot=0;
		dfs(1,1);
		reg int ans= 0;
		for(reg int i=1;i<=tot;++i){
			reg int x=divi[i];
			if(gcd(x,a0)==a1&&(ll)x*b0/gcd(x,b0)==b1)
				++ans;
		}
		printf("%d\n",ans);
	}
	return 0;
}