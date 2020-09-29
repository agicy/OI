#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

const int MAXN=15+5;
const int MAXS=50+5;
const int p=1000003;

inline int add(reg int a,reg int b){
	reg int sum=a+b;
	return sum>=p?sum-p:sum;
}

inline int sub(reg int a,reg int b){
	reg int sum=a-b;
	return sum<0?sum+p:sum;
}

inline int mul(reg int a,reg int b){
	return 1ll*a*b%p;
}

inline int fpow(reg int x,reg int exp){
	reg int res=1;
	while(exp){
		if(exp&1)
			res=mul(res,x);
		x=mul(x,x);
		exp>>=1;
	}
	return res;
}

inline int lowbit(reg int x){
	return x&(-x);
}

inline int getCnt(reg int x){
	reg int res=0;
	while(x)
		++res,x^=lowbit(x);
	return res;
}

int n,k;
char str[MAXN][MAXS];
int cal[MAXN];
int fac[MAXN],invfac[MAXN];
int basep[MAXS];

inline int binom(reg int n,reg int m){
	return mul(fac[n],mul(invfac[m],invfac[n-m]));
}

inline void Init(void){
	fac[0]=basep[0]=1;
	for(reg int i=1;i<MAXN;++i)
		fac[i]=mul(fac[i-1],i);
	invfac[MAXN-1]=fpow(fac[MAXN-1],p-2);
	for(reg int i=MAXN-2;i>=0;--i)
		invfac[i]=mul(invfac[i+1],i+1);
	for(reg int i=1;i<MAXS;++i)
		basep[i]=mul(basep[i-1],26);
	return;
}

int main(void){
	Init();
	int T;
	scanf("%d",&T);
	while(T--){
		scanf("%d%d",&n,&k);
		for(reg int i=0;i<n;++i)
			scanf("%s",str[i]+1);
		reg int len=strlen(str[0]+1);
		memset(cal,0,sizeof(cal));
		reg int U=(1<<n)-1;
		for(reg int S=0;S<=U;++S){
			reg int x=getCnt(S);
			if(x<k)
				continue;
			static char tmp[MAXS];
			memset(tmp,-1,sizeof(tmp));
			reg bool flag=false;
			reg int cnt=len;
			for(reg int i=0;i<n;++i)
				if((S>>i)&1)
					for(reg int j=1;j<=len;++j)
						if(str[i][j]!='?'&&str[i][j]!=tmp[j]){
							if(tmp[j]==-1){
								--cnt;
								tmp[j]=str[i][j];
							}
							else{
								flag=true;
								break;
							}
						}
			if(!flag)
				cal[x]=add(cal[x],basep[cnt]);
		}
		reg int ans=0;
		for(reg int i=k;i<=n;++i)
			if((i-k)&1)
				ans=sub(ans,mul(binom(i,k),cal[i]));
			else
				ans=add(ans,mul(binom(i,k),cal[i]));
		printf("%d\n",ans);
	}
	return 0;
}