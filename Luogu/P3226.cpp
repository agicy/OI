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

const int MAXN=1e5+5;
const int MAXLOG2N=17+1;
const int MAXLOG3N=11+1;
const int p=1000000001;

inline int add(reg int a,reg int b){
	reg int sum=a+b;
	return sum>=p?sum-p:sum;
}

inline int mul(reg int a,reg int b){
	return 1ll*a*b%p;
}

int n;
int g[1<<MAXLOG3N];
int f[MAXLOG2N][MAXLOG3N];
int len[MAXLOG2N];
int dp[MAXLOG2N][1<<MAXLOG3N];

inline int solve(reg int s){
	f[0][0]=s;
	reg int lasi=0;
	for(reg int i=0;i<MAXLOG2N;++i){
		if(i)
			f[i][0]=mul(2,f[i-1][0]);
		if(f[i][0]>n)
			break;
		lasi=i;
		reg int lasj=0;
		for(reg int j=1;j<MAXLOG3N;++j){
			f[i][j]=mul(3,f[i][j-1]);
			if(f[i][j]>n)
				break;
			lasj=j;
		}
		len[i]=lasj+1;
	}
	reg int L=lasi+1;
	memset(dp,0,sizeof(dp));
	for(reg int i=0;i<(1<<len[0]);++i)
		dp[0][i]=g[i];
	for(reg int i=1;i<L;++i){
		reg int U=(1<<len[i])-1;
		for(reg int S=0;S<=U;++S){
			if(!g[S])
				continue;
			reg int Uk=(1<<len[i-1])-1;
			for(reg int pre=0;pre<=Uk;++pre)
				if(g[pre]&&(!(S&pre)))
					dp[i][S]=add(dp[i][S],dp[i-1][pre]);
		}
	}
	reg int res=0;
	for(reg int i=0;i<(1<<len[L-1]);++i)
		res=add(res,dp[L-1][i]);
	return res;
}

int main(void){
	for(n=1;n<=1e5;++n){
		//n=read();
		reg int ans=1;
		for(reg int i=0;i<(1<<MAXLOG3N);++i)
			g[i]=(!((i<<1)&i));

		for(reg int i=1;i<=n;++i)
			if(i%2!=0&&i%3!=0)
				ans=mul(ans,solve(i));
		printf("%d,",ans);
		if(n%1000==0)
			cerr<<"n="<<n<<endl;
	}
	return 0;
}