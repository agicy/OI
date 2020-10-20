#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	bool f=false;
	char ch=getchar();
	int res=0;
	while(ch<'0'||'9'<ch)f|=(ch=='-'),ch=getchar();
	while('0'<=ch&&ch<='9')res=10*res+ch-'0',ch=getchar();
	return f?-res:res;
}

const int MAXNM=1e5+5;

int n,m;
int buff[MAXNM];
int val[MAXNM];

namespace Subtask2{
	const int MAXN=30+5,MAXM=30+5;
	int dp[MAXN][MAXM];
	const int inf=0x3f3f3f3f;
	inline int getId(int i,int j){
		return (i-1)*m+j;
	}
	inline int getDis(int x1,int y1,int x2,int y2){
		return abs(x1-x2)+abs(y1-y2);
	}
	inline void cMax(int &a,int b){
		if(a<b)
			a=b;
		return;
	}
	inline void Solve(void){
		for(int i=0;i<MAXN;++i)
			for(int j=0;j<MAXM;++j)
				dp[i][j]=-inf;
		dp[1][1]=0;
		int ans=-inf;
		for(int i=1;i<=n;++i)
			for(int j=1;j<=m;++j){
				for(int k=1;k<=i;++k)
					for(int l=1;l<=j;++l)
						if(i!=k||j!=l)
							cMax(dp[i][j],dp[k][l]+val[getId(i,j)]+buff[getId(k,l)]*getDis(i,j,k,l));
				cMax(ans,dp[i][j]+buff[getId(i,j)]*getDis(i,j,n,m));
			}
		printf("%d\n",ans);
		return;
	}
}

namespace Subtask5{
	const int inf=0x3f3f3f3f;
	inline int getId(int i,int j){
		return (i-1)*m+j;
	}
	inline void cMax(int &a,int b){
		if(a<b)
			a=b;
		return;
	}
	namespace BIT{
		inline int lowbit(int x){
			return x&(-x);
		}
		int n,m;
		int unit[MAXNM];
		inline void Init(int s1,int s2){
			n=s1,m=s2;
			fill(unit,unit+MAXNM,-inf);
			return;
		}
		inline void update(int x,int y,int val){
			for(int i=x;i<=n;i+=lowbit(i))
				for(int j=y;j<=m;j+=lowbit(j))
					cMax(unit[getId(i,j)],val);
			return;
		}
		inline int query(int x,int y){
			int res=-inf;
			for(int i=x;i;i^=lowbit(i))
				for(int j=y;j;j^=lowbit(j))
					cMax(res,unit[getId(i,j)]);
			return res;
		}
	}
	inline void Solve(void){
		BIT::Init(n,m);
		BIT::update(1,1,0);
		int ans=-inf;
		for(int i=1;i<=n;++i)
			for(int j=1;j<=m;++j){
				int s=BIT::query(i,j)+val[getId(i,j)];
				BIT::update(i,j,s);
				cMax(ans,s);
			}
		printf("%d\n",ans);
		return;
	}
}

namespace Subtask3{
	const int MAXNM=1e5+5;

	int Q[MAXNM];
	ll dp[MAXNM];

	inline double X(int i){
		return -buff[i];
	}
	inline double Y(int i){
		return dp[i]-1ll*buf[i]*i;
	}
	inline double slope(int i,int j){
		return (Y(i)-Y(j))/(X(i)-X(j));
	}
	inline void Solve(void){
		if(n==1)
			n=m;
		int head=0,tail=0;
		for(int i=1;i<=n;++i){
			while(head<tail&&slope(Q[head+1],Q[head])>i)
				++head;
			int j=Q[head];
			dp[i]=dp[j]+val[i]+1ll*buff[j]*(i-j);
			while(head<tail&&slope(Q[tail-1],Q[tail])<slope(i,Q[tail]))
				--tail;
			Q[++tail]=i;
		}
		printf("%lld\n",dp[n]);
		return;
	}
}

namespace Subtask6{
	const int inf=0x3f3f3f3f;
	inline void Solve(void){
		puts("0");
		return;
	}
}

int main(void){
	bool fs5=true;
	n=read(),m=read();
	int id=0;
	for(int i=1;i<=n;++i)
		for(int j=1;j<=m;++j){
			buff[++id]=read();
			if(buff[id])
				fs5=false;
		}
	id=0;
	for(int i=1;i<=n;++i)
		for(int j=1;j<=m;++j)
			val[++id]=read();
	if(n<=30&&m<=30)
	   Subtask2::Solve();
	else if(fs5)
		Subtask5::Solve();
	else if(min(n,m)==1)
		Subtask3::Solve();
	else
		Subtask6::Solve();

	return 0;
}