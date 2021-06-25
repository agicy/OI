#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar()(p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[1<<21],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch)) ch=getchar();
	while(isdigit(ch)) res=10*res+(ch^'0'),ch=getchar();
	return res;
}

inline ll readll(void){
	reg char ch=getchar();
	reg ll res=0;
	while(!isdigit(ch)) ch=getchar();
	while(isdigit(ch)) res=10*res+(ch^'0'),ch=getchar();
	return res;
}

const int mod=1e9+7;

inline int add(reg int a,reg int b){
	a+=b;
	return a>=mod?a-mod:a;
}

inline int sub(reg int a,reg int b){
	a-=b;
	return a<0?a+mod:a;
}

const int inv[]={0,1,500000004,333333336,250000002,400000003,166666668,142857144,125000001,111111112,700000005,818181824,83333334,153846155,71428572,466666670,562500004,352941179,55555556,157894738,850000006,47619048,409090912,739130440,41666667,280000002,576923081,370370373,35714286,758620695,233333335,129032259,281250002,939393946,676470593,628571433,27777778,621621626,78947369,717948723,425000003,658536590,23809524,395348840,204545456,822222228,369565220,404255322,520833337,448979595,140000001,784313731,788461544,56603774,685185190,763636369,17857143,385964915,879310351,50847458,616666671,688524595,564516133,15873016};

ll n;
int k;
pair<int,int> fac[64];
int f[64];

int main(void){
	n=readll(),k=read();
	reg int tot=0;
	for(reg int i=2;1ll*i*i<=n;++i)
		if(!(n%i)){
			reg int cnt=0;
			while(!(n%i))
				n/=i,++cnt;
			fac[++tot]=make_pair(i,cnt);
		}
	if(n>1)
		fac[++tot]=make_pair(n%mod,1);
	reg int ans=1;
	for(reg int i=1;i<=tot;++i){
		memset(f,0,sizeof(f));
		f[fac[i].second]=1;
		for(reg int j=1;j<=k;++j)
			for(reg int k=fac[i].second;k>=0;--k)
				f[k]=add(f[k+1],1ll*f[k]*inv[k+1]%mod);
		reg int sum=0,pod=1;
		for(reg int j=0;j<=fac[i].second;++j){
			sum=add(sum,1ll*pod*f[j]%mod);
			pod=1ll*pod*fac[i].first%mod;
		}
		ans=1ll*ans*sum%mod;
	}
	printf("%d\n",ans);
	return 0;
}