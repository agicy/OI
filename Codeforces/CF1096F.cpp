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
	while(!isdigit(ch))f|=(ch=='-'),ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return f?-res:res;
}

const int MAXN=2e5+5;
const int mod=998244353;

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
		x=1ll*x*x%mod;
		exp>>=1;
	}
	return res;
}

namespace BIT{
	inline int lowbit(reg int x){
		return x&(-x);
	}
	int n,unit[MAXN];
	inline void Init(reg int s){
		n=s;
		return;
	}
	inline void update(reg int id,reg int val){
		for(reg int i=id;i<=n;i+=lowbit(i))
			unit[i]+=val;
		return;
	}
	inline int query(reg int id){
		reg int res=0;
		for(reg int i=id;i;i^=lowbit(i))
			res+=unit[i];
		return res;
	}
}

int n;
int a[MAXN];
int cnt[MAXN];
int l[MAXN],r[MAXN];

int main(void){
	n=read();
	for(reg int i=1;i<=n;++i){
		a[i]=read();
		if(a[i]!=-1)
			++cnt[a[i]];
		l[i]=l[i-1]+(a[i]==-1);
	}
	for(reg int i=1;i<=n;++i)
		cnt[i]+=cnt[i-1];
	reg int tot=l[n];
	reg int ans1=0,ans2=1ll*tot*(tot-1)%mod*fpow(4,mod-2)%mod,ans3=0,ans4=0;
	BIT::Init(n);
	for(reg int i=n;i>=1;--i){
		r[i]=r[i+1]+(a[i]==-1);
		if(a[i]!=-1){
			ans1=add(ans1,BIT::query(a[i]));
			BIT::update(a[i],1);
			ans3=add(ans3,1ll*r[i]*(a[i]-cnt[a[i]])%mod);
			ans4=add(ans4,1ll*l[i]*(tot-a[i]+cnt[a[i]])%mod);
		}
	}
	printf("%d\n",add(add(ans1,ans2),1ll*fpow(tot,mod-2)*add(ans3,ans4)%mod));
	return 0;
}