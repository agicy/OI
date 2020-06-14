#include<bits/stdc++.h>
using namespace std;
#define reg register
#define MOD 100000007
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg bool cnt=false;
	reg char ch=getchar();
	reg int res=0;
	while(ch<'0'||'9'<ch)cnt|=(ch=='-'),ch=getchar();
	while('0'<=ch&&ch<='9')res=10*res+ch-'0',ch=getchar();
	return cnt?-res:res;
}

const int MAXN=20;

int n;

struct Point{
	int x,y;
	inline void Read(void){
		x=read(),y=read();
		return;
	}
};

int R[MAXN][MAXN];
int dp[1<<MAXN][MAXN];
int cnt[1<<MAXN];
Point p[MAXN];

inline bool check(const Point& l,const Point& mid,const Point& r){
	return ((r.x-l.x)*(mid.y-l.y)==(r.y-l.y)*(mid.x-l.x))&&((mid.x-l.x)*(mid.x-r.x)<0||(mid.y-l.y)*(mid.y-r.y)<0);
}

int main(void){
	n=read();
	for(reg int i=0;i<n;++i)
		p[i].Read();
	for(reg int i=1;i<(1<<n);++i)
		cnt[i]=cnt[i>>1]+(i&1);
	for(reg int i=0;i<n;++i)
		for(reg int j=0;j<n;++j)
			if(i!=j)
				for(reg int k=0;k<n;++k)
					if(k!=i&&k!=j)
						if(check(p[i],p[k],p[j]))
							R[i][j]|=(1<<k);
	for(reg int i=0;i<n;++i)
		dp[1<<i][i]=1;
	reg int ans=0;
	for(reg int S=1;S<(1<<n);++S){
		for(reg int j=0;j<n;++j)
			if(dp[S][j]&&((S>>j)&1)){
				if(cnt[S]>=4)
					ans=(ans+dp[S][j])%MOD;
				for(reg int k=0;k<n;++k)
					if(((S>>k)&1)||(R[j][k]&S)!=R[j][k])
						continue;
					else
						dp[S|(1<<k)][k]=(dp[S|(1<<k)][k]+dp[S][j])%MOD;
			}
	}
	printf("%d\n",ans);
	return 0;
}