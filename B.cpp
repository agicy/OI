#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar()(p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
#define flush() (fwrite(wbuf,1,wp1,stdout),wp1=0)
#define putchar(c) (wp1==wp2&&(flush(),0),wbuf[wp1++]=c)
static char wbuf[1<<21];int wp1;const int wp2=1<<21;
inline int read(void){
	reg bool f=false;
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))f|=(ch=='-'),ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return f?-res:res;
}

inline ll readll(void){
	reg char ch=getchar();
	reg ll res=0;
	while(!isdigit(ch))ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return res;
}

inline void writeln(reg int x){
	static char buf[32];
	reg int p=-1;
	if(x==0) putchar('0');
	else while(x) buf[++p]=(x%10)^'0',x/=10;
	while(~p) putchar(buf[p--]);
	putchar('\n');
	return;
}

const int mod=998244353;

inline int add(reg int a,reg int b){
	a+=b;
	return a>=mod?a-mod:a;
}

inline int sub(reg int a,reg int b){
	a-=b;
	return a<0?a+mod:a;
}

ll n;
int a,b;

namespace Subtask1{
	inline void Solve(void){
		priority_queue<ll,vector<ll>,greater<ll>/**/> Q;
		Q.push(0);
		while(Q.size()<n){
			reg ll val=Q.top();
			Q.pop();
			Q.push(val+a),Q.push(val+b);
		}
		reg ll cnt=0,ans=0;
		while(!Q.empty()){
			ans=add(ans,Q.top()%mod);
			Q.pop();
			++cnt;
			if(cnt==n)
				break;
		}
		printf("%lld\n",ans);
		return;
	}
}

namespace Subtask2{/*
	const int MAXLOG2N=60+1;
	bool flag;
	int binom[MAXLOG2N][MAXLOG2N];
	inline void Init(void){
		binom[0][0]=1;
		for(reg int i=1;i<MAXLOG2N;++i){
			binom[i][0]=1;
			for(reg int j=1;j<=i;++j)
				binom[i][j]=add(binom[i-1][j-1],binom[i-1][j]);
		}
		return;
	}*/
	inline void Solve(void){
		reg int limit=1,le=0;
		while(limit<n)
			limit<<=1,++le;
		reg int delta=limit>>1;
		reg int l=1,r=limit,mid;
		while(l<r){
			mid=(l+r)>>1;
			if(mid+delta-(mid+1)/2>=n)
				r=mid;
			else
				l=mid+1;
		}
		printf("%d\n",add(1ll*a*l%mod*le%mod,1ll*(le-1)*a%mod*(n-l)%mod));
		return;
	}
}

int main(void){
	reg int T=read();
	while(T--){
		n=readll(),a=read(),b=read();
		if(n<=1e6)
			//printf("S1="),
			Subtask1::Solve();
		else if(a==b)
			//printf("S2="),
			Subtask2::Solve();

	}
	return 0;
}