#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(ch<'0'||'9'<ch)ch=getchar();
	while('0'<=ch&&ch<='9')res=10*res+ch-'0',ch=getchar();
	return res;
}

const int MAXK=5000+5;
const int p=1000000007;
const int inv2=500000004;

inline int add(reg int a,reg int b){
	reg int sum=a+b;
	return sum>=p?sum-p:sum;
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

int n,k;
int S[MAXK][MAXK];

inline void Init(reg int n){
	S[0][0]=1;
	for(reg int i=1;i<=n;++i)
		for(reg int j=1;j<=i;++j)
			S[i][j]=add(S[i-1][j-1],1ll*j*S[i-1][j]%p);
	return;
}

int main(void){
	Init(5e3);
	scanf("%d%d",&n,&k);
	reg int ans=0,tag=1,p2=pow(2,n,p);
	for(reg int i=0;i<=k;++i){
		ans=add(ans,1ll*S[k][i]%p*tag%p*p2%p);
		tag=1ll*tag*(n-i)%p;
		p2=1ll*p2*inv2%p;
	}
	if(!k)
		ans=add(ans,p-1);
	printf("%d\n",ans);
	return 0;
}
