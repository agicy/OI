#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

inline int read(void){
	char ch=getchar();
	int res=0;
	while(!isdigit(ch))ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return res;
}

inline ll readll(void){
	char ch=getchar();
	ll res=0;
	while(!isdigit(ch))ch=getchar();
	while(isdigit(ch))res=10ll*res+(ch^'0'),ch=getchar();
	return res;
}

const int p=998244353;
const int MAXN=1e6+5;
const int MAXSIZE=100;

char s[MAXN];
int n,lim;
int nex[MAXN],val[MAXN],f[MAXSIZE],base10[MAXSIZE];
ll len[MAXSIZE];

inline int add(const int& a,const int& b){
	int sum=a+b;
	return sum>=p?sum-p:sum;
}

inline int mul(const int a,const int& b){
	return 1ll*a*b%p;
}

inline int fpow(int x,ll exp){
	int res=1;
	while(exp){
		if(exp&1)
			res=mul(res,x);
		x=mul(x,x);
		exp>>=1;
	}
	return res;
}

inline void getNex(const char* s){
	nex[0]=-1;
	for(int i=0,j=-1;i<n;nex[++i]=++j)
		while(j!=-1&&s[i]!=s[j])
			j=nex[j];
	return;
}

inline int getVal(const ll& pos){
	ll sum=0;
	int ans=0;
	for(int i=lim;i>=0;--i)
		if(sum+len[i]<=pos){
			ans=add(mul(ans,base10[i]),f[i]);
			sum+=len[i];
		}
	return add(mul(ans,fpow(10,pos-sum)),val[pos-sum]);
}

ll m;
int q;

int main(void){
	int T=read();
	while(T--){
		scanf("%s",s);
		n=strlen(s)/2;
		getNex(s);
		for(int i=1;i<=n;++i)
			val[i]=(10ll*val[i-1]+(s[i-1]^'0'))%p;
		m=readll(),q=read();
		len[0]=n-nex[n],f[0]=val[len[0]];
		len[1]=n,f[1]=val[n];
		lim=1;
		for(int i=2;i<MAXSIZE;++i){
			len[i]=len[i-1]+len[i-2];
			f[i]=(1ll*f[i-1]*fpow(10,len[i-2])+f[i-2])%p;
			if(len[i]>=m){
				lim=i;
				break;
			}
		}
		for(int i=0;i<=lim;++i)
			base10[i]=fpow(10,len[i]);
		while(q--){
			static ll l,r;
			l=readll(),r=readll();
			printf("%lld\n",(getVal(r)-1ll*getVal(l-1)*fpow(10,r-l+1)%p+p)%p);
		}
	}
	return 0;
}