#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

const int MAXN=1e6+5;
const int p=19930726;

int n;
ll k;
char str[MAXN];
int r[MAXN],T[MAXN];

inline void manacher(char str[],reg int n){
	reg int R=0,mid;
	for(reg int i=1;i<=n;++i){
		if(i<=R)
			r[i]=min(R-i,r[2*mid-i]);
		else
			r[i]=1;
		while(i+r[i]<=n&&i-r[i]>=0&&str[i+r[i]]==str[i-r[i]])
			++r[i];
		if(i+r[i]-1>R)
			R=i+r[i]-1,mid=i;
		++T[2*r[i]-1];
	}
	return;
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

int main(void){
	scanf("%d%lld%s",&n,&k,str+1);
	manacher(str,n);
	if(!(n&1))--n;
	reg int ans=1;
	reg int sum=0;
	for(reg int i=n;i>=1;i-=2){
		sum+=T[i];
		if(sum>k){
			ans=1ll*ans*pow(i,k,p)%p;
			break;
		}
		else{
			ans=1ll*ans*pow(i,sum,p)%p;
			k-=sum;
		}
	}
	if(sum<k)
		puts("-1");
	else
		printf("%d\n",ans);
	return 0;
}