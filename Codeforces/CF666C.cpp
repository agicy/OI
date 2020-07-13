#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define MOD 1000000007
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(ch<'0'||'9'<ch)ch=getchar();
	while('0'<=ch&&ch<='9')res=10*res+ch-'0',ch=getchar();
	return res;
}

const int MAXLEN=100000+5;
const int MAXN=100000+5;
const int MAXM=100000+5;

int fac[MAXN],finv[MAXN];
int pow25[MAXN],pow26[MAXN];
int invpow26[MAXN];

inline void Init(reg int n=1e5){
	fac[0]=finv[0]=pow25[0]=pow26[0]=invpow26[0]=1;
	finv[n]=716327852ll;
	for(reg int i=1;i<=n;++i){
		fac[i]=1ll*fac[i-1]*i%MOD;
		pow25[i]=25ll*pow25[i-1]%MOD;
		pow26[i]=26ll*pow26[i-1]%MOD;
		invpow26[i]=576923081ll*invpow26[i-1]%MOD;
	}
	for(reg int i=n-1;i>=1;--i)
		finv[i]=1ll*finv[i+1]*(i+1ll)%MOD;
	return;
}

inline int C(reg int n,reg int m){
	return 1ll*fac[n]*finv[m]%MOD*finv[n-m]%MOD;
}

const int Size=26;
const int invSize=576923081;

struct Node{
	int id,val;
	inline Node(reg int id=0,reg int val=0):id(id),val(val){
		return;
	}
	inline bool operator<(const Node& a)const{
		return val<a.val;
	}
};

char str[MAXLEN];
Node S[MAXM];
int top;
int ans[MAXM];

inline void Solve(void){
	sort(S+1,S+top+1);
	reg int l=strlen(str);
	reg int sum=0,ptr=l;
	for(reg int i=1;i<=top;++i){
		reg int r=S[i].val;
		for(;ptr<=r;++ptr)
			sum=(sum+1ll*pow25[ptr-l]*invpow26[ptr]%MOD*C(ptr-1,l-1)%MOD)%MOD;
		ans[S[i].id]=1ll*sum*pow26[r]%MOD;
	}
	for(reg int i=1;i<=top;++i)
		printf("%d\n",ans[i]);
	top=0;
	return;
}

int main(void){
	Init();
	reg int m=read();
	scanf("%s",str);
	while(m--){
		reg int t=read();
		switch(t){
			case 1:{
				Solve();
				scanf("%s",str);
				break;
			}
			case 2:{
				reg int n=read();
				++top;
				S[top]=Node(top,n);
				break;
			}
			default:break;
		}
	}
	Solve();
	return 0;
}