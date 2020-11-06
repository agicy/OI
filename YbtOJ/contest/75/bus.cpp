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

const int MAXN=1e6+5;

int n,maxc;
int c[MAXN],v[MAXN];

namespace Subtask1{
	const int MAXN=5e3+5;
	const int inf=0x3f3f3f3f;
	int dp[MAXN];
	inline void cMin(reg int &a,reg int b){
		if(a>b)
			a=b;
		return;
	}
	inline void Solve(void){
		memset(dp,0x3f,sizeof(dp));
		dp[0]=0;
		for(reg int i=1;i<=n;++i)
			for(reg int j=0;j<i;++j)
				if(!((i-j)%c[j]))
					cMin(dp[i],dp[j]+(i-j)/c[j]*v[j]);
		for(reg int i=1;i<=n;++i)
			printf("%d%c",dp[i]==inf?-1:dp[i],i==n?'\n':' ');
		return;
	}
}

namespace Subtask3{
	const int MAXN=1e6+5;
	const int inf=0x3f3f3f3f;
	int dp[MAXN];
	inline void Solve(void){
		int Minv=v[0],ptr=0;
		for(reg int i=1;i<=n;++i){
			dp[i]=(i-ptr)*Minv+dp[ptr];
			if(v[i]<=Minv)
				Minv=v[i],ptr=i;
		}
		for(reg int i=1;i<=n;++i)
			printf("%d%c",dp[i],i==n?'\n':' ');
		return;
	}
}

namespace Subtask4{
	const int MAXC=10+1;
	const int MAXN=1e6+5;
	const int inf=0x3f3f3f3f;
	vector<int> S[MAXC][MAXC];
	int dp[MAXN];
	inline void cMin(reg int &a,reg int b){
		if(a>b)
			a=b;
		return;
	}
	inline void Solve(void){
		for(int i=0;i<n;++i)
			S[c[i]][i%c[i]].push_back(i);
		memset(dp,0x3f,sizeof(dp));
		dp[0]=0;
		for(reg int i=1;i<=n;++i)
			for(reg int p=1;p<=maxc;++p)
				for(auto x:S[p][i%p])
					if(x<i)
						cMin(dp[i],dp[x]+(i-x)/p*v[x]);
					else
						break;
		for(reg int i=1;i<=n;++i)
			printf("%d%c",dp[i]==inf?-1:dp[i],i==n?'\n':' ');
		return;
	}
}

int main(void){
	freopen("bus.in","r",stdin);
	freopen("bus.out","w",stdout);

	n=read(),maxc=read();
	for(reg int i=0;i<n;++i)
		c[i]=read(),v[i]=read();
	if(n<=5e3)
		Subtask1::Solve();
	else if(maxc==1)
		Subtask3::Solve();
	else
		Subtask4::Solve();

	fclose(stdin);
	fclose(stdout);
	return 0;
}