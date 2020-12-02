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

const int MAXN=200+5;
const int MAXK=200+5;

int n,l,k;
double dp[MAXN][MAXN][MAXN];

struct Node{
	double p;
	int val;
	inline bool operator<(const Node& a)const{
		return val>a.val;
	}
};

Node a[MAXN];

int main(void){
	n=read(),l=read(),k=read();
	for(reg int i=1;i<=n;++i){
		static int x;
		x=read();
		a[i].p=0.01*x;
	}
	for(reg int i=1;i<=n;++i)
		a[i].val=read();
	sort(a+1,a+n+1);
	dp[0][0][min(k,n)]=1;
	for(reg int i=0;i<n;++i)
		for(reg int j=0;j<=i;++j)
			for(reg int l=0;l<=n;++l){
				if(l+a[i+1].val>=0)
					dp[i+1][j+1][min(n,l+a[i+1].val)]+=dp[i][j][l]*a[i+1].p;
				dp[i+1][j][l]+=dp[i][j][l]*(1-a[i+1].p);
			}
	reg double ans=0;
	for(reg int i=l;i<=n;++i)
		for(reg int j=0;j<=n;++j)
			ans+=dp[n][i][j];
	printf("%.9lf\n",ans);
	return 0;
}